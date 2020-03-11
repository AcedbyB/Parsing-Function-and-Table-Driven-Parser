#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "node.c"

typedef struct Stack* Stack;
int here = 0;
int flag = 0;
char input[50];
int table[50][50];

struct Stack {
    char array[50];
    int pointer;
};

Stack new_Stack() {
    Stack this = (struct Stack*)malloc(sizeof(struct Stack));
    if (this == NULL) {
        return NULL; // Out of memory...
    }
    this->pointer = 0;
    return this;
}

void add_to_Stack(Stack s, char c) {
    s->array[s->pointer] = c;
    s -> pointer++;
}

void pop_from_Stack(Stack s) {
    s -> pointer--;
}

Stack my_stack;

int get_Num(char e) {
    if(e == 'E') return 1;
    if(e == 'e') return 2;
    if(e == 'C') return 3;
    if(e == 'c') return 4;
    if(e == 'S') return 5; 
    if(e == 's') return 6;
    if(e == 'A') return 7;
    if(e == 'X') return 8;
}

int get_Index(char next) {
    if(next == '|') return 1;
    else if(next == '*') return 2;
    else if(next == '.') return 3;
    else if(next == '(') return 4; 
    else return 4;
}

void get_Production(char e, char next, Node cur) {
    int e_num = get_Num(e);
    int next_num = get_Index(next);
    if(e == 'A'  && next_num == 4) 
        next_num = 2;
    int next_production_num = table[e_num][next_num];
    
    push_to_Stack(next_production_num, cur);
}

void setup_Table() {
    for(int i = 1; i <= 4; i++) table[1][i] = 1;
    table[2][1] = 2;
    for(int i = 2; i <= 4; i++) table[2][i] = 3;
    for(int i = 1; i <= 4; i++) table[3][i] = 4;
    table[4][1] = table[4][2] = table[4][4] = 6;
    table[4][3] = 5;
    for(int i =1; i<=4;i++) table[5][i] = 7;
    table[6][1] = table[6][3] = table[6][4] = 9;
    table[6][2] = 8;
    for(int i = 1; i<=3;i++) table[7][i] = 11;
    table[7][4] = 10;
    for(int i = 1; i<=4;i++) table[8][i] = 12;

}

void push_to_Stack(int num, Node cur) {
    // printf("%c\n", cur -> type);
    if(num == 1) {
        cur -> child[0] = new_Node('C', 0);
        cur -> child[1] = new_Node('e', 0);
        add_to_Stack(my_stack, 'e');
        add_to_Stack(my_stack, 'C');
    }
    if(num == 2) {
        cur -> child[0] = new_Node('|', 1);
        cur -> child[1] = new_Node('E', 0);
        add_to_Stack(my_stack, 'E');
        add_to_Stack(my_stack, '|');
    }
    if(num == 3) {
        cur -> child[0] = new_Node('N', 1);
        add_to_Stack(my_stack, 'N');
    }
    if(num == 4) {
        cur -> child[0] = new_Node('S', 0);
        cur -> child[1] = new_Node('c', 0);
        add_to_Stack(my_stack, 'c');
        add_to_Stack(my_stack, 'S');
    }
    if(num == 5) {
        cur -> child[0] = new_Node('.', 1);
        cur -> child[1] = new_Node('C', 0);
        add_to_Stack(my_stack, 'C');
        add_to_Stack(my_stack, '.');
    }
    if(num == 6) {
        cur -> child[0] = new_Node('N', 1);
        add_to_Stack(my_stack, 'N');
    }
    if(num == 7) {
        cur -> child[0] = new_Node('A', 0);
        cur -> child[1] = new_Node('s', 0);
        add_to_Stack(my_stack, 's');
        add_to_Stack(my_stack, 'A');
    }
    if(num == 8) {
        cur -> child[0] = new_Node('*', 1);
        cur -> child[1] = new_Node('s', 0);
        add_to_Stack(my_stack, 's');
        add_to_Stack(my_stack, '*');
    }
    if(num == 9) {
        cur -> child[0] = new_Node('N', 1);
        add_to_Stack(my_stack, 'N');
    }
    if(num == 10) {
        cur -> child[0] = new_Node('(',1);
        cur -> child[1] = new_Node('E', 0);
        cur -> child[2] = new_Node(')', 1);
        add_to_Stack(my_stack, ')');
        add_to_Stack(my_stack, 'E');
        add_to_Stack(my_stack, '(');
    }
    if(num == 11) {
        cur -> child[0] = new_Node('X', 0);
        add_to_Stack(my_stack, 'X');
    }
    if(num == 12) {
        cur -> child[0] = new_Node('x', 1);
        add_to_Stack(my_stack, 'x');
    }
}

//1 = e
//2 = c
//3 = s
void Process(Node cur) {
    // printf("%c\n", cur -> type);
    if(flag == 1) return;
    char c;
    if(here >= strlen(input)) c = 'N';
    else c = input[here];
    if(cur -> terminal != 1)
        get_Production(cur -> type, c, cur);
    if(cur -> terminal == 1) {
        if(cur -> type == 'x') {
            // printf("%c %c\n", cur ->type, input[here]);
            if('a' <= c && c <= 'z') {
                cur -> type = c;
                here++;
            }  
            else 
                flag = 1;
        }
        else if (cur -> type != c) {
            if(cur -> type != 'N') flag = 1;   
        }
        else 
            here++;
        pop_from_Stack(my_stack);
        return;
    }
    int cnt = 0;
    while(cnt < 5 && cur -> child[cnt] != NULL) {
        Process(cur -> child[cnt]);
        cnt++;
    }
    pop_from_Stack(my_stack);
}

void printTree(Node cur, int indent_num) {
    if(flag == 1) {
        printf("This is not legit!\n");
        return;
    }
    int cnt = 0;
    char p = cur -> type;
    for(int i = 1; i <= indent_num; i++) printf("  ");
    if(p!= 'N')
        printf("%c\n", p);
    else 
        printf("eps\n");
    while(cnt < 5 && cur -> child[cnt] != NULL) {
        printTree(cur -> child[cnt], indent_num + 1);
        cnt++;
    }
}


int main() {
    setup_Table();
    scanf("%s", input);
    my_stack = new_Stack();
    Node root = new_Node('E', 0);
    Process(root);
    printTree(root, 0);
}

