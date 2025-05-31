#pragma once

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char name[80];
    char address[80];
    uint8_t semester;
} record;

record random_record()
{
    record res;
    sprintf(res.name, "Student_%d", rand() % 100);
    sprintf(res.address, "Street %d, building %d", rand() % 100, rand() % 100);
    res.semester = rand() % 6 + 1;
    return res;
}