#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node { 
    char *data;
    struct Node* next; 
    struct Node* prev;  
};
struct Node *head;
struct Node *tail;

struct Node* new(char *x) {
    struct Node* new = (struct Node*)malloc(sizeof(struct Node));
     new->data = x;
     new->prev = NULL;
     new->next = NULL;
     return new;
}

//creates new head to linked list
void push(char *data){ 
    struct Node* curr = new(data);
    if(head == NULL){
        head == curr;
        return;
    }
    head -> prev = curr;
    curr -> next = head;
    head = curr;
}

//creates new tail to linked list
void append(char *data){
    struct Node* temp = head;
    struct Node* curr = new(data); 
    if (head == NULL) { 
        head = curr; 
        return; 
    } 
    while(temp -> next != NULL)
        temp = temp -> next;
    temp -> next = curr;
    curr -> prev = temp;
  
    return; 
} 
struct matrix{
    int numStates;
    char startState;
    char endState;
    char currState;
};

struct instructions{
    char write;
    char direction;
    char newState;
};

void printNodes(struct Node* node){
    while (node != NULL) { 
        printf("%c", node->data);
        node = node->next; 
    }
}

int main() {
    struct matrix *myMatrix;
    char *temp;
    head = NULL;
    tail = NULL;
    struct Node *tempNode;
    int tempInt = 0;
    char endState;
    struct instructions instruct;
    char *empty = "B";
    temp = malloc(sizeof(char));
    myMatrix = malloc(sizeof(struct matrix));
    
    printf("input file: text.txt  \n");
    char filename[] = "text.txt";
    FILE *file = fopen ( filename, "r" );
    
    printf("Initial tape contents: ");
    while(*temp != '\n'){
        fscanf(file, "%c", temp);
        append(*temp);
    }
    printNodes(head);
    
    printf("\n");
    
    fscanf(file, "%c", temp);
    if(*temp == '\n')
        fscanf(file, "%c", temp);
    tempInt = atoi(temp);
    myMatrix->numStates = tempInt;
    fscanf(file, "%c", temp);
    if(*temp == '\n')
        fscanf(file, "%c", temp);
    myMatrix->startState = *temp;
    fscanf(file, "%c", temp);
    if(*temp == '\n')
        fscanf(file, "%c", temp);
    myMatrix->endState = *temp;
    endState = myMatrix->endState;

    myMatrix->currState = myMatrix->startState;
    struct instructions **instruction;
    
    instruction = malloc(myMatrix -> numStates * sizeof(struct instructions*));
    for(int i=0; i <(5*sizeof(struct instructions)); i++){
        instruction[i] = malloc(255 * sizeof(struct instructions));
    }
    int row;
    char col;
    printf("Reading table and rewriting tape\n ");
    fscanf(file, "%c", temp);
    while(!feof(file)){
        fscanf(file, "%c", temp);
        tempInt = atoi(temp);
        row = tempInt;
        fscanf(file, "%c", temp);
        fscanf(file, "%c", temp);
        col = *temp;
        fscanf(file, "%c", temp);
        fscanf(file, "%c", temp);
        instruct.write = *temp;
        fscanf(file, "%c", temp);
        fscanf(file, "%c", temp);
        instruct.direction = *temp;
        fscanf(file, "%c", temp);
        fscanf(file, "%c", temp);
        instruct.newState = *temp;
        instruction[row][col] = instruct;
        fscanf(file, "%c", temp);
    }
    tempNode = head;
    while(myMatrix ->currState != endState){
        *temp = myMatrix -> currState;
        tempInt = atoi(temp);
        *temp = tempNode -> data;
        instruct = instruction[tempInt][*temp];
        tempNode -> data = instruct.write;
        myMatrix -> currState = instruct.newState;
        if(instruct.direction == 'R'){
            tempNode = tempNode -> next;
            if(tempNode -> next == NULL){
                append(*empty);
                tempNode = tempNode -> next;
            }
        } else {
            tempNode = tempNode -> prev;
            if(tempNode -> prev == NULL){
                push(*empty);
            }
            tempNode = tempNode ->prev;
        }
    }
    printf("\nFinal Tape Contents: ");
    printNodes(head);
    printf("\n");
    
    return (EXIT_SUCCESS);
}