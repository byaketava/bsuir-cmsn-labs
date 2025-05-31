#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "record.h"

void lock(int fd, int id)
{
    struct flock lock_str = {
            .l_type = F_WRLCK,
            .l_whence = SEEK_SET,
            .l_start = id * sizeof(record),
            .l_len = sizeof(record)};
    fcntl(fd, F_SETLKW, &lock_str);
}

void unlock(int fd, int id)
{
    struct flock unlock_str = {
            .l_type = F_UNLCK,
            .l_whence = SEEK_SET,
            .l_start = id * sizeof(record),
            .l_len = sizeof(record)};
    fcntl(fd, F_SETLKW, &unlock_str);
}

int get_count(int fd)
{
    off_t end = lseek(fd, 0, SEEK_END);
    return end / sizeof(record);
}

record get_record(int fd, int id)
{
    record temp;
    lseek(fd, id * sizeof(record), SEEK_SET);
    read(fd, &temp, sizeof(record));
    return temp;
}

void output_record(record r, int id)
{
    printf("\n[%d]\nName: %s\nAddres: %s\nSemester: %d\n",
           id, r.name, r.address, r.semester);
}

void output_all_records(int fd)
{
    record temp;
    int num = get_count(fd);
    lseek(fd, 0, SEEK_SET);
    for (int i = 0; i < num; i++)
    {
        read(fd, &temp, sizeof(record));
        output_record(temp, i);
    }
}

void put_record(int fd, int id, record r)
{
    lseek(fd, id * sizeof(record), SEEK_SET);
    write(fd, &r, sizeof(record));
}

void change_record(int fd, int id)
{
    lock(fd, id);
    record temp = get_record(fd, id);
    output_record(temp, id);
    char str[80];
    printf("New name: ");
    scanf("%79s", temp.name);
    printf("New address: ");
    scanf("%79s", temp.address);
    printf("New semester: ");
    scanf("%hhu", &temp.semester);
    put_record(fd, id, temp);
    printf("Record changed!\n");
    unlock(fd, id);
}

void add_record(int fd)
{
    record temp;
    printf("New record:\n");
    printf("Name: ");
    scanf("%79s", temp.name);
    printf("Address: ");
    scanf("%79s", temp.address);
    printf("Semester: ");
    scanf("%hhu", &temp.semester);
    put_record(fd, get_count(fd), temp);
    printf("Record saved!\n");
}

void add_random_record(int fd)
{
    record temp = random_record();
    put_record(fd, get_count(fd), temp);
    printf("New record:\n");
    output_record(get_record(fd, get_count(fd) - 1), get_count(fd) - 1);
}

int main()
{
    int fd = open("file", O_RDWR);
    if (fd == -1)
    {
        printf("Opening error: %s\n", strerror(errno));
        return 0;
    }
    printf("\nMenu:\n"
            "[list] - get all records\n"
            "[rec<N>] - get record with N id\n"
            "[ch<N>] - change record with N id\n"
            "[new] - add new record\n"
            "[newrand] - add new random record\n"
            "[q] - quit\n");
    char opt[255];
    int id;
    while (scanf("%s", opt))
    {
        if (!strcmp(opt, "list"))
            output_all_records(fd);
        if (!strcmp(opt, "new"))
            add_record(fd);
        if (!strcmp(opt, "newrand"))
            add_random_record(fd);
        if (!strcmp(opt, "q"))
            break;
        if (sscanf(opt, "rec%d", &id))
        {
            if (id >= get_count(fd) || id < 0)
                printf("There is no record with id=%d\n", id);
            else
                output_record(get_record(fd, id), id);
        }
        if (sscanf(opt, "ch%d", &id))
        {
            if (id >= get_count(fd) || id < 0)
                printf("There is no record with id=%d\n", id);
            else
                change_record(fd, id);
        }
    }
    close(fd);
    return 0;
}