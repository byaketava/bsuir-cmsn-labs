#pragma once

#include "ipc.h"

void create_consumer(void);

void remove_consumer(void);

void consume_msg(msg_t *msg);