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

// 1. Crea e inicializa una lista vacía
List * createList() {
    List * list = (List *)malloc(sizeof(List));
    assert(list != NULL);
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    return list;
}

// 2. firstList: retorna el dato del primer nodo y actualiza current al head
//    nextList: retorna el dato del nodo siguiente al current y avanza current

void * firstList(List * list) {
    if (list->head == NULL) return NULL;
    list->current = list->head;
    return list->current->data;
}

void * nextList(List * list) {
    if (list->current == NULL) return NULL;
    if (list->current->next == NULL) return NULL;
    list->current = list->current->next;
    return list->current->data;
}

// 3. lastList: retorna el dato del último nodo y actualiza current al tail
//    prevList: retorna el dato del nodo anterior al current y retrocede current

void * lastList(List * list) {
    if (list->tail == NULL) return NULL;
    list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if (list->current == NULL) return NULL;
    if (list->current->prev == NULL) return NULL;
    list->current = list->current->prev;
    return list->current->data;
}

// 4. pushFront: agrega un dato al comienzo de la lista

void pushFront(List * list, void * data) {
    Node * new = createNode(data);
    if (list->head == NULL) {
        list->head = new;
        list->tail = new;
    } else {
        new->next = list->head;
        list->head->prev = new;
        list->head = new;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list, data);
}

// 5. pushCurrent: agrega un dato a continuación del nodo apuntado por current

void pushCurrent(List * list, void * data) {
    Node * new = createNode(data);
    if (list->current == NULL) {
        list->head = new;
        list->tail = new;
    } else {
        new->next = list->current->next;
        new->prev = list->current;
        if (list->current->next != NULL) {
            list->current->next->prev = new;
        } else {
            list->tail = new;
        }
        list->current->next = new;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

// 6. popCurrent: elimina el nodo en la posición current y retorna su dato
//    El current queda apuntando al nodo siguiente del eliminado

void * popCurrent(List * list) {
    if (list->current == NULL) return NULL;

    Node * toRemove = list->current;
    void * data = toRemove->data;

    if (toRemove->prev != NULL) {
        toRemove->prev->next = toRemove->next;
    } else {
        list->head = toRemove->next;
    }

    if (toRemove->next != NULL) {
        toRemove->next->prev = toRemove->prev;
    } else {
        list->tail = toRemove->prev;
    }

    list->current = toRemove->next;

    free(toRemove);
    return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}
