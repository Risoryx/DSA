#include <stdio.h>


int queue[4];
int max=4;
int front=-1;
int rear=-1;

void enqueue(int item){
    if ((rear+1)%max==front){     // Front is index of next element to be deleted and rear is index of last inserted element. So next element will be inserted at rear+1. Therefore if rear+1== front , that means there is no space for element to be inserted.
        printf("Queue is full \n");

    }
    else{
        rear=(rear+1)%max;
        queue[rear]=item;
        if(front==-1)
            front+=1;
    }
}

void dequeue(){
     if (front==-1) {            //In a circular queue, front can be greater than rear, so comparisons like front > rear or front > (rear+1)%max aren't reliable for checking emptiness.
        printf("Queue empty \n");
        front=-1;
        rear=-1;
     }
     else if (front==rear){
        printf("Deleted element was %d \n",queue[front]);
        front=-1;
        rear=-1;
    }
     else{
        printf("Deleted element was %d \n",queue[front]);
        front=(front+1)%max;
        }
}

void display(){
    if (front==-1){
        printf("Queue is empty \n");
    }
    else{
    int temp=front;
    while(temp!=rear){
        printf("%d",queue[temp]);
        temp=(temp+1)%max;
    }
    printf("%d",queue[temp]);   // Because we need to separately print the element at rear because while loop stops when temp becomes rear.
    printf("\n");
    }
}


int main(){
    do{
        printf("1. Enqueue \n");
        printf("2. Dequeue \n");
        printf("3. Display \n");
        printf("4. Exit \n");
        printf("Enter choice: ");
        int choice;
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("Enter item you want to enqueue: ");
                int item;
                scanf("%d",&item);
                enqueue(item);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                display();
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice \n");
                break;
        }
    }
    while (1);
}



/* Sample output
1. Enqueue 
2. Dequeue 
3. Display 
4. Exit 
Enter choice: 1
Enter item you want to enqueue: 1
1. Enqueue 
2. Dequeue 
3. Display 
4. Exit 
Enter choice: 1
Enter item you want to enqueue: 2
1. Enqueue 
2. Dequeue 
3. Display 
4. Exit 
Enter choice: 1
Enter item you want to enqueue: 3
1. Enqueue 
2. Dequeue 
3. Display 
4. Exit 
Enter choice: 1
Enter item you want to enqueue: 4
1. Enqueue 
2. Dequeue 
3. Display 
4. Exit 
Enter choice: 3
1234
1. Enqueue 
2. Dequeue 
3. Display 
4. Exit 
Enter choice: 2
Deleted element was 1 
1. Enqueue 
2. Dequeue 
3. Display 
4. Exit 
Enter choice: 2
Deleted element was 2 
1. Enqueue 
2. Dequeue 
3. Display 
4. Exit 
Enter choice: 3
34
1. Enqueue 
2. Dequeue 
3. Display 
4. Exit 
Enter choice: 1
Enter item you want to enqueue: 1
1. Enqueue 
2. Dequeue 
3. Display 
4. Exit 
Enter choice: 1
Enter item you want to enqueue: 2
1. Enqueue 
2. Dequeue 
3. Display 
4. Exit 
Enter choice: 3
3412
1. Enqueue 
2. Dequeue 
3. Display 
4. Exit 
Enter choice: 2
Deleted element was 3 
1. Enqueue 
2. Dequeue 
3. Display 
4. Exit 
Enter choice: 1
Enter item you want to enqueue: 3
1. Enqueue 
2. Dequeue 
3. Display 
4. Exit 
Enter choice: 3
4123
1. Enqueue 
2. Dequeue 
3. Display 
4. Exit 
Enter choice: 4


*/