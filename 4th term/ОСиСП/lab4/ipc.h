#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <inttypes.h>

#define DATA_MAX (((256 + 3) / 4) * 4)
#define MSG_MAX 400
#define CHILD_MAX 100

#define SHM_OBJECT "/queue"
#define MUTEX "mutex"
#define FREE_SPACE "free_space"
#define ITEMS "items"

typedef struct
{
    int8_t type;
    uint16_t hash;
    uint8_t size;
    char data[DATA_MAX];
} msg_t;

typedef struct
{
    size_t add_count;
    size_t extract_count;
    size_t msg_amount;
    size_t head;
    size_t tail;
    msg_t buffer[MSG_MAX];
} msg_queue;

uint16_t hash(msg_t *msg);

void msg_queue_init(void);

size_t put_msg(msg_t *msg);// Return add_count
size_t get_msg(msg_t *msg);// Return extract_count