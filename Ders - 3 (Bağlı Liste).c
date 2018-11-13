#include <stdio.h>
#include <stdlib.h>

struct node {
    int number;
    struct node *next;
};

struct node *create_node(int number) {
    struct node *a;
    a = (struct node *) malloc(sizeof(struct node));
    if (a == NULL) {
        printf("We can't allocate space in heap for node.\n");
        exit(1);
    }
    a->number = number;
    a->next = NULL;
};

void add_front(int number, struct node **node_start) {
    struct node *a = create_node(number);
    a->next = *node_start;
    *node_start = a;
}

void add_back(int number, struct node **node_start) {
    struct node *a = create_node(number);
    if (*node_start == NULL) {
        *node_start = a;
    } else {
        struct node *temp = *node_start;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = a;
    }
}

void print_list(struct node *node_start) {
    while (node_start != NULL) {
        printf("%d   ", (node_start)->number);
        node_start = node_start->next;
    }
}

void print_list_recursive(struct node *node_start) {
    if (node_start != NULL) {
        printf("%d   ", (node_start)->number);
        print_list_recursive(node_start->next);
    }
}

void add_ordered(int number, struct node **node_start) {
    struct node *a = create_node(number);
    struct node *temp = *node_start;
    struct node *back = temp;

    while (temp != NULL && temp->number <= number) {
        back = temp;
        temp = temp->next;
    }
    if (temp == *node_start) {
        a->next = *node_start;
        *node_start = a;
    } else {
        back->next = a;
        a->next = temp;
    }
}

void delete_element(int number, struct node **node_start) {
    struct node *temp = *node_start;
    struct node *back = temp;
    while (temp != NULL && temp->number != number) {
        back = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("We can't found the number.\n");
        return;
    } else if (temp == *node_start) {                   //İlk eleman silinen elemandır.
        *node_start = (*node_start)->next;
    } else {
        back->next = temp->next;
    }
    free(temp);
}

void print_list_recursive_backward(struct node *node_start) {
    if (node_start != NULL) {
        print_list_recursive_backward(node_start->next);
        printf("%d   ", (node_start)->number);
    }
}

void erase_list(struct node **node_start) {
    struct node *now;
    while (*node_start != NULL) {
        now = *node_start;
        *node_start = (*node_start)->next;
        free(now);
    }
    printf("List was erased free.\n");
}

void order_list(struct node **node_start) {
    if (*node_start == NULL || (*node_start)->next == NULL) {
        printf("No.\n");                                //Sıralanacak bir eleman yok.
        return;
    }
    struct node *a = NULL;
    struct node *b;
    struct node *c;
    struct node *d = (*node_start)->next;
    (*node_start)->next = NULL;
    while (d != NULL) {
        c = d;
        d = d->next;
        b = *node_start;
        while (b != NULL && b->number <= c->number) {
            a = b;
            b = b->next;
        }
        if (b == *node_start) {                         //İlk elemanda değişiklik varsa.
            c->next = *node_start;
            *node_start = c;
        } else {
            a->next = c;
            c->next = b;
        }
    }
}

void list_backward(struct node **node_start) {
    struct node *temp = *node_start;
    struct node *new_node = temp;
    while (*node_start != NULL) {
        temp = *node_start;
        *node_start = (*node_start)->next;
        new_node->next = temp;
        temp = new_node;
    }
    *node_start = temp;
}

struct node **list_backward_recursive(struct node **node_start) {
    struct node *temporary;
    if (*node_start == NULL) {
        return node_start;
    } else if ((*node_start)->next == NULL) {
        return &((*node_start)->next);
    } else {
        temporary = *node_start;
        *node_start = (*node_start)->next;
        *list_backward_recursive(node_start) = temporary;
        temporary->next = NULL;
        return &(temporary->next);
    }

}

int main() {
    struct node *list = NULL;
    add_back(17, &list);
    add_back(3, &list);
    add_back(11, &list);
    add_back(2, &list);
    add_back(13, &list);
    add_ordered(5, &list);
    add_front(1, &list);
    order_list(&list);
    print_list_recursive_backward(list);
}
