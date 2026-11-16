#include <stdio.h>

int queue[4];
int max=4;
int front=-1;
int rear=-1;
//We don't need to provide the queue as argument for the following functions because we declared queue here so it is a global variable and can be accessed by any function.

void enqueue(int item){                     
    if (rear==max-1){
        printf("Stack overflow \n");
        
    }
    else{
        queue[++rear]=item;
        if (front==-1)
            front=front+1;}
}

void dequeue(){
    if (front>rear || front==-1){
        printf("Stack underflow \n");
        front=-1;
        rear=-1;
    }
    else{
        printf("Dequeued element is %d \n",queue[front++]);
    }
}

void display(){
    if (front!=-1 && front<=rear){
        printf("Queue currently contains \n");
        int temp;
        for (temp=front;temp<=rear;temp++)
        printf("%d ",queue[temp]);
    }
    else{
        printf("Queue is empty");
    }
    printf("\n");
}


int main(){
    do{
        printf("1. Enqueue an element \n");
        printf("2. Dequeue an element \n");
        printf("3. Display an element \n");
        printf("4. Exit \n");
        printf("Enter choice: ");
        int choice;
        scanf("%d",&choice);    // The reason why we don't do return 1 for the cases other than the exit case is because returning any value (doesn't have to be 1) will kill the main function because return is what signals the end of a function 
        switch(choice){ 
            case 1:
                printf("Enter element: ");
                int element;
                scanf("%d",&element);
                enqueue(element);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                display();
                break;
            case 4:
                printf("Program has been terminated \n");
                return 0;
            default:
                printf("Invalid choice \n");
                break;
        }
     }
     while(1); //You could just do a while instead of doing a do-while but I personally am a fan of this design.
}