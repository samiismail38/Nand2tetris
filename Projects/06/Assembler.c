#include<stdio.h>
#include<stdlib.h>


typedef struct asm_n{
    char *asssembly;
    int machine_code;
    struct asm_n * next;
}asm_n; 


typedef struct sym_t{
    int *memory_location;
    char *symbol;
    struct sym_t *next;

}sym_t


int main(){

// intialize the assembly linked list with first element head.
asm_n head;
FILE file_pointer=

// build a linked list for the assembly instructions and symbol table to handle jumps.
build_sym_table(asm_n *head, FILE *source);


}



build_lists(asm_n *head, sym){


    
}