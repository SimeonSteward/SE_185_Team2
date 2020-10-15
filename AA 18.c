#include <stdio.h>

#include <stdlib.h>

 

int main(){

    int x = 0;

    int num;

    int *p;

 

    printf("How many integers are you going to input?\n");

    scanf(" %d", &num);

    

     p = (int*)malloc(num * sizeof(int));

    

    for(int i = 0; i < num; i++){

            int temp;

            printf("Enter an integer\n");

            scanf(" %d", &temp);

            *(p + i) = temp;

    }

 

    for(int i = 0; i < num; i++){

            x += *(p + i);

    }

 

    free(p);

    printf("%d", x);

    return 0;

}