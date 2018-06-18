#pragma once

#include <Types.h>

struct LLNode {
    void *prev_node;
    void *data;
    u64 length;
    void *next;
};

struct LLStruct {
    LLNode *head;
    
};

typedef struct LinkedListStruct LinkedList;