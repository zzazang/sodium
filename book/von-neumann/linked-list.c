#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node {
    struct Node* next;
    unsigned value;
} Node;

void shuffle(Node** nodes, unsigned n)
{
    unsigned i;
    for (i = 0; i < n; i++) {
        unsigned j = (unsigned)(((long long)random() * n) / ((long long)RAND_MAX + 1));
        if (i != j) {
            Node* node = nodes[i];
            nodes[i] = nodes[j];
            nodes[j] = node;
        }
    }
}

int main(int argc, char* argv[])
{
    const unsigned n = 1000000;
    const unsigned iterations = 1000;
    Node* head;
    {
        Node** nodes = malloc(sizeof(Node*) * n);
        unsigned i;
        for (i = 0; i < n; i++) {
            nodes[i] = malloc(sizeof(Node));
            nodes[i]->value = i;
        }
        if (argc == 2 && strcmp(argv[1], "--no-shuffle") == 0)
            ;
        else
            shuffle(nodes, n);
        for (i = 0; i < n; i++)
            nodes[i]->next = (i+1) < n ? nodes[i+1] : NULL;
        head = nodes[0];
        free(nodes);
    }
    {
        Node* node;
        unsigned iter;
        for (iter = 0; iter < iterations; iter++) {
            unsigned long long sum = 0;
            for (node = head; node != NULL; node = node->next)
                sum += node->value;
            assert(sum == (unsigned long long)(n - 1) * n / 2);
        }
    }
}
