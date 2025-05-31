#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <stdbool.h>
#include <math.h>

#define MAX_THREADS 128

enum block_state
{
    FREE,
    IN_USE,
    SORTED
};
struct sort_block
{
    uint64_t num;
    void *start;
    uint64_t size;
    enum block_state state;
};
struct index_s
{
    double time_mark;
    uint64_t recno;
};
struct index_hdr_s
{
    uint64_t records;
    struct index_s idx[];
};

uint64_t granul;
pthread_mutex_t mutex;
pthread_t tid[MAX_THREADS];
struct sort_block *blocks;

int cmp_index(const void *a, const void *b)
{
    const struct index_s *indexA = (const struct index_s *) a;
    const struct index_s *indexB = (const struct index_s *) b;
    if (indexA->time_mark < indexB->time_mark)
    {
        return -1;
    } else if (indexA->time_mark > indexB->time_mark)
    {
        return 1;
    } else
    {
        return 0;
    }
}

bool is_s_sorted(struct index_s *arr, uint64_t size)
{
    for (uint64_t i = 1; i < size; i++)
    {
        if (cmp_index(&arr[i - 1], &arr[i]) > 0)
        {
            return false;
        }
    }
    return true;
}

void *sort_thread(void *arg)
{
    uint64_t num = *(int *) arg;
    struct sort_block *block = &blocks[num];
    block->state = IN_USE;
    uint64_t n = block->size / sizeof(struct index_s);

    qsort(block->start, n, sizeof(struct index_s), (int (*)(const void *, const void *)) cmp_index);
    bool sort_res = is_s_sorted(block->start, n - 1);
    block->state = sort_res ? SORTED : FREE;
    bool all = false;

    while (true)
    {
        pthread_mutex_lock(&mutex);
        all = true;
        for (uint64_t i = 0; i < granul; i++)
        {
            if (blocks[i].state == FREE)
            {
                all = false;
                block = &blocks[i];
                block->state = IN_USE;
                break;
            }
        }
        pthread_mutex_unlock(&mutex);
        if (all)
            pthread_exit(NULL);
        qsort(block->start, n, sizeof(struct index_s), (int (*)(const void *, const void *)) cmp_index);
        sort_res = is_s_sorted(block->start, n);
        block->state = sort_res ? SORTED : FREE;
        if (!sort_res)
        {
            printf("S Thread [%ld] sorted [%ld] block: %d\n", num, block->num, sort_res);
        }
    }
}

void *merge_thread(void *arg)
{
    uint64_t num = *(int *) arg;
    struct sort_block *block;
    bool all = false;
    while (true)
    {
        pthread_mutex_lock(&mutex);
        all = true;
        for (uint64_t i = 0; i < granul; i++)
        {
            if (blocks[i].state == FREE)
            {
                all = false;
                block = &blocks[i];
                block->state = IN_USE;
                break;
            }
        }
        pthread_mutex_unlock(&mutex);
        if (all)
            pthread_exit(NULL);
        uint64_t n = block->size / sizeof(struct index_s);
        qsort(block->start, n, sizeof(struct index_s), (int (*)(const void *, const void *)) cmp_index);
        bool sort_res = is_s_sorted(block->start, n);
        if (!sort_res)
        {
            printf("M Thread [%ld] sorted [%ld] block: %d\n", num, block->num, sort_res);
        }
        block->state = sort_res ? SORTED : FREE;
    }
}

void merge_blocks()
{
    granul = granul / 2;
    struct sort_block *new_blocks = (struct sort_block *) malloc(sizeof(struct sort_block) * granul);
    for (uint64_t i = 0; i < granul; i++)
    {
        new_blocks[i].num = i;
        new_blocks[i].start = blocks[2 * i].start;
        new_blocks[i].size = blocks[2 * i].size * 2;
        new_blocks[i].state = FREE;
    }
    free(blocks);
    blocks = new_blocks;
}

void merge_sort(uint64_t threads)
{
    uint64_t mergeTimes = log2(granul);
    for (uint64_t i = 0; i < mergeTimes; i++)
    {
        if (granul == 1)
        {
            break;
        }
        printf("Block size(mg): %ld\n", blocks[0].size);
        merge_blocks();

        uint64_t threadsNumber = threads > granul ? granul : threads;
        for (uint64_t i = 0; i < threadsNumber; i++)
        {
            uint64_t *arg = malloc(sizeof(int));
            *arg = i;
            pthread_create(&tid[i], NULL, merge_thread, arg);
        }
        for (uint64_t i = 0; i < threadsNumber; i++)
        {
            pthread_join(tid[i], NULL);
        }
        printf("%ld merge done\n", i);
    }
}

void sort_index(uint64_t threads)
{
    uint64_t threadsNum = threads > granul ? granul : threads;
    for (uint64_t i = 0; i < threadsNum; i++)
    {
        uint64_t *arg = malloc(sizeof(int));
        *arg = i;
        pthread_create(&tid[i], NULL, sort_thread, arg);
    }
    for (uint64_t i = 0; i < threadsNum; i++)
    {
        pthread_join(tid[i], NULL);
    }
    merge_sort(threads);
}

void init(uint64_t memsize, void *file_data)
{
    uint64_t res = pthread_mutex_init(&mutex, NULL);
    if (res)
    {
        fprintf(stderr, "Failed mutex init \n");
        exit(1);
    }
    uint64_t block_size = memsize / granul;
    blocks = (struct sort_block *) malloc(sizeof(struct sort_block) * granul);
    struct index_hdr_s *header = (struct index_hdr_s *) file_data;
    printf("\nCount of records: %ld\n", header->records);
    struct index_s *data = header->idx;
    for (uint64_t i = 0; i < granul; i++)
    {
        blocks[i].start = data + (i * block_size) / sizeof(struct index_s);
        blocks[i].size = block_size;
        blocks[i].state = FREE;
        blocks[i].num = i;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: sort_index granul threads filename\n");
        exit(1);
    }

    uint64_t memsize;
    granul = atoi(argv[1]);
    uint64_t threads = atoi(argv[2]);
    char *filename = argv[3];
    int fd = open(filename, O_RDWR);
    if (fd < 0)
    {
        perror("Error opening file");
        exit(1);
    }
    uint64_t file_size = lseek(fd, 0, SEEK_END);

    memsize = file_size;
    void *file_data = mmap(NULL, memsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    init(memsize, file_data);
    if (file_data == MAP_FAILED)
    {
        perror("Error mapping file");
        close(fd);
        exit(1);
    }

    sort_index(threads);
    struct index_hdr_s *header = (struct index_hdr_s *) file_data;
    printf("Sorted: %s\n", is_s_sorted(header->idx, header->records) ? "YES" : "NO");

    if (munmap(file_data, memsize) < 0)
    {
        perror("Error unmapping file");
    }
    close(fd);

    return 0;
}