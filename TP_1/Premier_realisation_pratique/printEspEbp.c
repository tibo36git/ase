#include <stdio.h>

int main() {
    int x = 0;
    int y = 0;

    asm ("movl %%esp , %0" : "=r" (x));

    asm ("movl %%ebp , %0" : "=r" (y));    
    
    printf("%d %d\n", x , y);

    return 0;
}