#include <stdio.h>
#include <stdlib.h>



struct Node{
    int coeff;
    int expo;
    struct Node* next;
};

struct Node* createNode(int co,int ex){
    struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
    newNode->coeff=co;
    newNode->expo=ex;
    newNode->next=NULL;
    return newNode;
}

struct Node* insertNode(struct Node* root,int co,int ex){
    struct Node* ptr=createNode(co,ex);
    if (root==NULL || ex>(root->expo)){
        ptr->next=root;
        root=ptr;
        return root;
    }
    else {
        struct Node* temp=root;
        while (temp->next!=NULL && (temp->next->expo>ex)){            // We are inserting before lower exponent term 
            temp=temp->next;
        }
        ptr->next=temp->next;                          // So this way what happens is it gets updated regardless. So if exponent of inputted value is greater than exponent before end, it will add it in between. If it is to be added at end, it will be added at end.
        temp->next=ptr;
    }
    return root;
}


void display(struct Node* root){
    struct Node* temp=root;
    while (temp!=NULL){
        printf("%dx^%d ",temp->coeff,temp->expo);
        if (temp->next!=NULL){
            printf("+ ");

        }
        temp=temp->next;
    }
    printf("\n");
}


struct Node* multiplication(struct Node* poly1,struct Node* poly2,struct Node* result){
    struct Node* ptr1=poly1;
    struct Node* ptr2=poly2;
    while (ptr1!=NULL){
        ptr2=poly2;
        while (ptr2!=NULL){
            int co=ptr1->coeff * ptr2->coeff;
            int ex=ptr1->expo + ptr2->expo;
            result=insertNode(result,co,ex);
            ptr2=ptr2->next;
         }
         ptr1=ptr1->next;
    }
    printf("Unorganised multiplication result \n");
    display(result);
    struct Node* ptr3=result;
    while (ptr3->next!=NULL){
        if (ptr3->expo==ptr3->next->expo){
            ptr3->coeff=ptr3->coeff + ptr3->next->coeff;
            ptr3->next=ptr3->next->next;
        }
        else{                                              // The reason we do else is because we can't immediately move our pointer because there is a chance that ptr->next s coefficient has same exponent and therefore we risk having two nodes with same exponents not being simplified.
            ptr3=ptr3->next; 
        }
    }
    printf("Final result \n");
    display(result);
}


int main(){
    printf("Enter no of terms in polynomial 1: ");
    int n1;
    scanf("%d",&n1);
    struct Node* poly1=NULL;
    for (int i=0;i<n1;i++){
        printf("Enter coefficient: ");
        int co;
        int ex;
        scanf("%d",&co);
        printf("Enter exponent: ");
        scanf("%d",&ex);
        poly1=insertNode(poly1,co,ex);
    }
    printf("Polynomial 1 \n");
    printf("_____________\n");
    display(poly1);
    printf("Enter no of terms in polynomial 2: ");
    int n2;
    scanf("%d",&n2);
    struct Node* poly2=NULL;
    for (int i=0;i<n2;i++){
        printf("Enter coefficient: ");
        int co;
        int ex;
        scanf("%d",&co);
        printf("Enter exponent: ");
        scanf("%d",&ex);
        poly2=insertNode(poly2,co,ex);
    }
    printf("Polynomial 2 \n");
    printf("____________\n");
    display(poly2);

    struct Node* result=NULL;
    multiplication(poly1,poly2,result);


}