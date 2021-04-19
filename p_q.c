/* 
 * File:   p_q.c
 * Author: farhan
 *
 * Created on April 19, 2021, 7:27 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char name[20];
    int priority;
    struct Node *next;
};

typedef struct Node Queue;

void setPriority(Queue *node) {
    node->priority = (int) node->name[0];
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
    int choice;    
    while (1) {
        printf("\n1 -> Enqueue\n2 -> Dequeue\n3 -> get Max Node\n4 -> Print Size\n5 -> Print Queue\nAny other num -> Quit\n");
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                if (!front) {
                    front = (Queue *)malloc(sizeof(Queue));
                    printf("\nEnter name: ");
                    scanf("%s", front->name);
                    setPriority(front);
                    front->next = NULL;
                } else {
                    node = (Queue *)malloc(sizeof(Queue));
                    printf("\nEnter name: ");
                    scanf("%s", node->name);
                    setPriority(node);
                    node->next = NULL;
                    enqueue(node, front);
                }
                break;
            case 2:
                if (!front) {
                    printf("\nEmpty Queue Exception!!!\n");
                    goto label;
                }
                node = getMaximumPriorityNode(front);
                if (node == front) front = front->next;                                    
                else node = dequeue(node, front);                    
                printf("\n%s is retrieved\n", node->name);
                free(node);
                label: break;
            case 3:
                if (!front) {
                    printf("\nEmpty Queue Exception!!!\n");
                    goto label_2;
                }
                Queue *node = getMaximumPriorityNode(front);
                printf("\n%s is max node\n", node->name);
                label_2: break;
            case 4:
                printf("\nQueue size => %d\n", getSize(front));
                break;
            case 5:
                if (!front) printf("\nEmpty Queue Exception!!!\n");
                else {
                    printf("\nQueue -> ");
                    printQueue(front);
                    printf("\n");                    
                }
                break;
            default:
                printf("\nBye!!!\n");
                goto exit;
        }
    }

    exit: return 0;
}

