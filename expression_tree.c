#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"node.c"

//M = merge =  concat
//U = union
//Q = closure
//A = atomic

Node translate_to_expression_tree(Node cur) {
    if(cur -> terminal == 1) {
        if(cur -> type == 'N') return new_Node('0',1);
        else {
            Node cak = new_Node(cur -> type, 1);
            return cak;
        }
    }
    if(cur -> type == 'E') {
        Node C = translate_to_expression_tree(cur -> child[0]);
        Node ET = translate_to_expression_tree(cur -> child[1]);
        if(ET->type == '0') return C;
        else {
            Node uni = new_Node('U', 0);
            uni -> child[0] = C;
            uni -> child[1] = ET;
            return uni;
        }
    }
    else if(cur -> type == 'e') {
        if(cur -> child[1] == NULL) return new_Node('0', 1);
        else {
            Node cak = translate_to_expression_tree(cur -> child[1]);
            return cak;
        }
    }
    else if(cur -> type == 'C') {
        Node S = translate_to_expression_tree(cur -> child[0]);
        Node CT = translate_to_expression_tree(cur -> child[1]);
        if(CT -> type == '0') {
            // exit(0);
            return S;
        }
        else {
            Node concat = new_Node('M', 0);
            concat -> child[0] = S;
            concat -> child[1] = CT;
            return concat;
        }
    }
    else if(cur -> type == 'c') {
        if(cur -> child[1] == NULL) {
            Node cak = new_Node('0',1);
            return cak;
        }
        else {
            Node cak = translate_to_expression_tree(cur -> child[1]);
            return cak;
        }
    }
    else if(cur -> type == 'S') {
        Node A = translate_to_expression_tree(cur -> child[0]);
        Node ST = translate_to_expression_tree(cur -> child[1]);
        if(ST -> type == '0') {
            //printf("lon %d", 1);
            return A;
        }
        else {
            Node cak = ST;
            while(cak -> child[0] != NULL && cak -> child[0] -> type != '0') cak = cak -> child[0];
            cak -> child[0] = A;
            return ST;
        }
    }
    else if(cur -> type == 's') {
        if(cur -> child[1] == NULL) return new_Node('0',1);
        else {
            Node cak = new_Node('Q', 0);
            cak -> child[0] = translate_to_expression_tree(cur -> child[1]);
            return cak;
        }
    }
    else if(cur -> type == 'A') {
        if(cur -> child[1] == NULL) return translate_to_expression_tree(cur -> child[0]);
        else {
            Node atomic = new_Node('A', 0);
            Node cak = translate_to_expression_tree(cur -> child[1]);
            atomic -> child[0] = cak;
            return atomic;
        }
    }
    else if(cur -> type == 'X') {
        return translate_to_expression_tree(cur -> child[0]);
    }
    return NULL;
}

