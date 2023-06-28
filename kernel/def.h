#pragma once

#define NULL ((void *)0)

typedef struct {
        unsigned int initrd_location;
        unsigned int initrd_end;
} mapped_memory_t;
