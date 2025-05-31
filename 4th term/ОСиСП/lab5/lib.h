#pragma once
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    void *data;
    struct node *next;
} Node;

typedef struct queue
{
    int size;
    int added_cnt;
    int extracted_cnt;
    Node *head;
    Node *tail;
} Queue;

void push(Queue *queue, void *data)
{
    if (queue->size == 0)
    {
        Node *node = (Node *)malloc(sizeof(Node));
        node->data = data;
        node->next = NULL;
        queue->head = node;
        queue->tail = node;
    }
    else
    {
        Node *node = (Node *)malloc(sizeof(Node));
        node->data = data;
        node->next = NULL;
        queue->tail->next = node;
        queue->tail = node;
    }
    queue->size++;
    queue->added_cnt++;
}

void *pop(Queue *queue)
{
    if (queue->size == 0)
    {
        return NULL;
    }
    void *data = queue->head->data;
    Node *node = queue->head;
    queue->head = queue->head->next;
    queue->size--;
    queue->extracted_cnt++;
    free(node);
    return data;
}

int qsize(Queue *queue)
{
    return queue->size;
}

void qfree(Queue *queue)
{
    void *data;
    while ((data = pop(queue)) != NULL)
    {
        free(data);
    }
}