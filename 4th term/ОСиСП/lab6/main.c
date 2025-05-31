#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

struct index_s
{
    double time;
    uint64_t recno;
};

struct index_hdr_s
{
    uint64_t records;
    struct index_s idx[];
};

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s filename size_in_MB\n", argv[0]);
        return 1;
    }
    int INDEX_RECORD_SIZE = sizeof(struct index_s);
    int HEADER_SIZE = sizeof(struct index_hdr_s);

    char *filename = argv[1];
    uint64_t size = atoi(argv[2]);
    uint64_t num_records = (size * 1024 * 1024) / INDEX_RECORD_SIZE;
    uint64_t header_size = HEADER_SIZE + (size * 1024 * 1024);

    struct index_hdr_s *header = (struct index_hdr_s *) malloc(header_size);
    if (header == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    header->records = num_records;

    srand(time(NULL));
    for (uint64_t i = 0; i < num_records; i++)
    {
        struct index_s *record = &(header->idx[i]);
        double days_since_1900 = (double) (rand() % (365 * 123)) + 15020.0;
        double fraction_of_day = (double) rand() / RAND_MAX / 2.0;
        record->time = days_since_1900 + fraction_of_day;
        record->recno = i;
    }

    FILE *fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        printf("Failed to open file %s\n", filename);
        return 1;
    }

    fwrite(header, header_size, 1, fp);
    fclose(fp);
    printf("Generated %ld index records in file %s\n", num_records, filename);
    return 0;
}