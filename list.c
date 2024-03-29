#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList()
{
     List* lista = (List*)malloc(sizeof(List));
     lista->head = NULL;
     lista->tail = NULL;
     lista->current = NULL;
     return lista;
}

void * firstList(List * list) 
{
    list->current = list->head;
    if(list->current) return list->current->data;
    return NULL;
}

void * nextList(List * list) 
{
    if(list->current != NULL)
      list->current = list->current->next;
    if(list->current != NULL) return list->current->data;
    return NULL;
}

void * lastList(List * list) 
{
  list->current = list->head;
  while(list->current->next != NULL) nextList(list);
  return list->current->data;
}

void * prevList(List * list)
{
    if(list->current != NULL)
      if(list->current->prev != NULL)
      {
        list->current = list->current->prev;
        return list->current->data;
      }
    return NULL;
}

void pushFront(List * list, void * data) 
{ 
    Node* new = createNode(data);
    new->next = list->head;
    if(list->head) list->head->prev = new;
    list->head = new;
  
    list->tail = list->head;
    while(list->tail->next != NULL) list->tail = list->tail->next;
}

void pushBack(List * list, void * data) 
{
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) 
{
    Node* new = createNode(data);
    new->prev = list->current;
    new->next = list->current->next;
    new->prev->next = new;
    if(new->next == NULL) list->tail = new;
    else new->next->prev = new;
}

void * popFront(List * list) 
{
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list)
{
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) 
{
    if(list->current == NULL) return NULL;
    Node* izq = list->current->prev;
    Node* der = list->current->next;
    if(izq == NULL)
    {
      list->head = der;
      list->head->prev = NULL;
    }
    else if(der == NULL)
    {
      list->tail = izq;
      list->head->next = NULL;
    }
    else
    {
      izq->next = der;
      der->prev = izq;
    }
    free(list->current);
    list->current = NULL;
    return 0;
}

void cleanList(List * list) 
{
    while (list->head != NULL) 
    {
        popFront(list);
    }
}