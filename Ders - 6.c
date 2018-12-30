#include <stdio.h>
#include <stdlib.h>

#define SENTINEL -1000000

struct stack {
    int *array;
    int up;
    int size;
};

struct stack *create_stack(int size) {
    if (size <= 0) {
        printf("Please select a valid size.");
        exit(1);
    }
    struct stack *ptr = (struct stack *) malloc(sizeof(struct stack));
    ptr->array = (int *) malloc(sizeof(int) * size);
    ptr->up = -1;
    ptr->size = size;
    return ptr;
}

void create_stack_with_parameter(int size, struct stack **y) {
    if (size <= 0) {
        printf("Please select a valid size.");
        exit(1);
    }
    *y = (struct stack *) malloc(sizeof(struct stack));
    (*y)->array = (int *) malloc(sizeof(int) * size);
    (*y)->up = -1;
    (*y)->size = size;
}

int is_stack_empty(struct stack *y) {
    if (y->up == -1) {
        return 1;
    } else {
        return 0;
    }
}

int is_stack_full(struct stack *y) {
    if (y->up == y->size - 1) {
        return 1;
    } else {
        return 0;
    }
}

void add_to_stack(int number, struct stack *y) {
    if (is_stack_full(y)) {
        printf("Stack is full, exiting.");
        exit(1);
    } else {
        y->array[++y->up] = number;
    }
}

void print_stack(struct stack *y) {
    printf("Stack size: %d \n", y->size);
    printf("Number of elements: %d \n", y->up + 1);
    for (int i = y->up; i >= 0; i--) {
        printf("%4d", y->array[i]);
    }
    printf("\n");
}

int delete_on_stack(struct stack *y) {
    if (is_stack_empty(y)) {
        return SENTINEL;
    } else {
        return y->array[y->up--];
    }
}

void erase_stack(struct stack **y) {
    free((*y)->array);
    free((*y));
    *y = NULL;
}

void increase_stack_size(struct stack **ptr, int multiply) {
    struct stack *new;
    new = create_stack(multiply * ((*ptr)->size));
    for (int i = 0; i <= (*ptr)->up; i++) {
        new->array[i] = (*ptr)->array[i];
    }
    new->up = (*ptr)->up;
    erase_stack(ptr);
    *ptr = new;
}

int main() {
    struct stack *A = NULL;
    struct stack *B = NULL;
    A = create_stack(10);
    /* Parametre ile yığın oluştuma:
     * create_stack_with_parameter(10, &A); */
    add_to_stack(12, A);
    add_to_stack(56, A);
    add_to_stack(-20, A);
    print_stack(A);

    int deleted = delete_on_stack(A);
    printf("Deleted: %d \n", deleted);
    print_stack(A);

    increase_stack_size(&A, 3);
    print_stack(A);
}
