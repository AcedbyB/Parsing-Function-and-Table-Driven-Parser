#include<stdlib.h>

typedef struct Node* Node;

struct Node {
    char type;
    int terminal;
    Node child[5];
};

Node new_Node(char type, int terminal) {
    Node this = (struct Node*)malloc(sizeof(struct Node));
    if (this == NULL) {
        return NULL; // Out of memory...
    }
    this -> type = type;
    this -> terminal = terminal;
    for(int i = 0; i < 5; i++) this -> child[i] =  NULL;
    return this;
}