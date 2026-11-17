#include <stdio.h>


struct Node{
    int row;
    int col;
    int value;
};

int main(){
    printf("Enter number of rows: ");
    int rows;
    int cols;
    scanf("%d",&rows);
    printf("Enter number of columns: ");
    scanf("%d",&cols);
    int matrix[rows][cols];
    int count=0;
    for (int i=0;i<rows;i++){
        for (int j=0;j<cols;j++){
            printf("Enter value you wish to enter: ");
            int val;
            scanf("%d",&val);
            if(val!=0){
                count=count+1;
            }
            matrix[i][j]=val;
        }
    }
    printf("Original matrix \n");
    for (int i=0;i<rows;i++){
        for (int j=0;j<cols;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
    count=count+1;                     // We increment count by 1 because we need count+1 elements in structure array because we have metadata row
    struct Node sparse[count];     
    sparse[0].row=rows;
    sparse[0].col=cols;
    sparse[0].value=count-1;          // Here we do count-1 because we had previously incremented count by 1 to accommodate for meta data row. We decrement it by 1 now to account for the addition of 1 previously.
    int k=1;                          // This is for traversing sparse and we start with 1 and not 0 because sparse[0] is the metadata row and we don't want to accidentally overwrite that.
    for (int i=0;i<rows;i++){
        for (int j=0;j<cols;j++){
            if (matrix[i][j]!=0){
                sparse[k].row=i;
                sparse[k].col=j;
                sparse[k].value=matrix[i][j];
                k++;
            }
        }
    }
    printf("Sparse matrix of this will be \n");
    for (int i=0;i<count;i++){
        printf("%d %d %d \n",sparse[i].row,sparse[i].col,sparse[i].value);
    }
    struct Node transpose[count];
    transpose[0].row=cols;
    transpose[0].col=rows;
    transpose[0].value=count-1;                      
    int k1=1;                            // For traversing through transpose matrix. We start at k1=1 because transpose[0] is the metadata row and we don't want to accidentally overwrite that.
    for (int i=0;i<cols;i++){
        for (int j=1;j<count;j++){
            if (sparse[j].col==i){
                transpose[k1].row=sparse[j].col;
                transpose[k1].col=sparse[j].row;
                transpose[k1].value=sparse[j].value;
                k1++;
            }
        }
    
    }
     printf("Transpose matrix of this will be \n");
    for (int i=0;i<count;i++){
        printf("%d %d %d \n",transpose[i].row,transpose[i].col,transpose[i].value);
    }


}



/*    for (int i=0; i<cols; i++)
We are visiting every column of the original matrix.
Why columns?

Because when we transpose a matrix, each column of the original matrix becomes a row of the transposed matrix.

So we process column 0 first, then column 1, then column 2.

for (int j=1; j<count; j++)
Remember our sparse representation:
- sparse[0] contains metadata.
- sparse[1] onwards contains actual non-zero elements.
We don't want to compare the metadata row with anything.

Therefore, we start at j = 1.

We examine every actual non-zero element to see whether its column matches i.

Just to sum it up 
i decides which original column we are currently processing.
j searches all non-zero elements to find elements belonging to that column.
j starts at 1 because index 0 contains metadata.
Swapping row and column gives us the transposed coordinates.



*/