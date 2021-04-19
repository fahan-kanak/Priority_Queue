/* 
 * File:   p_q.c
 * Author: farhan
 *
 * Created on April 19, 2021, 7:27 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HELP printf("\nTo enqueue: type 'enq'<space>*name* and then hit Enter\nTo dequeue: type 'deq' and then hit Enter\n");
#define HELP_2 printf("To see max node: type 'max' and then hit Enter\nTo know Queue size: type 'size' and then hit Enter\n");
#define HELP_3 printf("To print Queue: type 'print' and then hit Enter\nTo see help: type 'help' and then hit Enter\nTo Quit: type 'quit' and then hit Enter\n");

struct Node {
    char name[20];
    int priority;
    struct Node *next;
};

typedef struct Node Queue;

void setPriority(Queue *node) {
    node->priority = (int) node->name[0];
}

void nameInput(char *str, Queue* node) {
    int i = 0;
    int len = strlen(str);
    while(i < len) {
        node->name[i] = str[i];
        i++;
    }
    node->name[i] = '\0';
}

Queue* getMaximumPriorityNode(Queue* front) {
    Queue *var = front;
    front = front->next;
    while(front) {
        if (front->priority < var->priority) var = front;
        front = front->next;
    }
    
    return var;
}

void enqueue(Queue* node, Queue* front) {
    if (front->next == NULL) {
        front->next = node;
        return;
    }
    enqueue(node, front->next);
}

int getSize(Queue* front) {
    int count = 0;
    while(front) {
        count++;
        front = front->next;
    }
    
    return count;
}

void printQueue(Queue *front) {
    if (!front) return;
    printf("%s ", front->name);
    printQueue(front->next);
}

Queue* dequeue(Queue* max_Node, Queue* front) {
    if (front->next == max_Node) {
        Queue* tmp = max_Node;
        front->next = max_Node->next;
        return tmp;
    }
    return dequeue(max_Node, front->next);
}

int main(int argc, char** argv) {
    Queue* front = NULL, *node; 
    char cmd[30];
    char *token;
    printf("Welcome to priority queue command prompt\n");
    while (1) {       
        printf("\n> ");
        scanf("%[^\n]", cmd);
        getchar();
        token = strtok(cmd, " ");                                       
            if (!strcmp(token, "enq")) {
                if (!front) {
                    front = (Queue *)malloc(sizeof(Queue));
                    token = strtok(NULL, " ");
                    nameInput(token, front);
                    setPriority(front);
                    front->next = NULL;
                } 
                else {
                    node = (Queue *)malloc(sizeof(Queue));
                    token = strtok(NULL, " ");
                    nameInput(token, node);
                    setPriority(node);
                    node->next = NULL;
                    enqueue(node, front);
                } 
                printf("\nInsert Success!\n");
            }
            else if (!strcmp(token, "deq")) {
                if (!front) {
                    printf("\nEmpty Queue Exception!!!\n");
                    continue;
                }
                node = getMaximumPriorityNode(front);
                if (node == front) front = front->next;                                    
                else node = dequeue(node, front);                    
                printf("\n%s is retrieved\n", node->name);
                free(node);                
            }
            else if (!strcmp(token, "max")) {
                if (!front) {
                    printf("\nEmpty Queue Exception!!!\n");
                    continue;
                }
                Queue *node = getMaximumPriorityNode(front);
                printf("\n%s is max node\n", node->name);                
            }
            else if (!strcmp(token, "size")) printf("\nQueue size => %d\n", getSize(front));                           
            else if (!strcmp(token, "print")) {
                if (!front) printf("\nEmpty Queue Exception!!!\n");
                else {
                    printf("\nQueue -> ");
                    printQueue(front);
                    printf("\n");                    
                }                
            }
            else if (!strcmp(token, "help")) {
                HELP
                HELP_2
                HELP_3
            }
            else if (!strcmp(token, "quit")) {
                printf("\nBye!!!\n");
                goto exit;
            }
            else printf("\ncommand not recognized!\n");                                    
    }

    exit: return 0;
}

