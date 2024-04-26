#include<stdio.h>
#include<stdlib.h>


typedef struct asm_n{
    char *assembly;
    int machine_code;
    struct asm_n * next;
}asm_n; 


typedef struct sym_t{
    int *memory_location;
    char *symbol;
    struct sym_t *next;

}sym_t;


int main(){

// intialize the assembly linked list with first element head.
asm_n *asm_head=malloc(sizeof(asm_n));
sym_t *sym_head=malloc(sizeof(sym_t));
FILE file_pointer;
int ml=16;

void build_tables(asm_n *asm_head, sym_t *sym_head, FILE *source);
void add_sym(char *label, int line, sym_t *sym_head);
void output(sym_t *sym_head, asm_n *asm_head);
unsigned int a_instruction(sym_t *sym_head, asm_n *asm_head);
unsigned int c_instruction(sym_t *sym_head, asm_n *asm_head);
int find_symbol(char *symbol);


output(sym_t *sym_head, asm_n *asm_head);


return 0; 
}


// build a linked list for the assembly instructions and symbol table to handle jumps.
void build_tables(asm_n *asm_head, sym_t *sym_head, FILE *source){
    int line=0; 
    char *string=read_line(line); 
    char *buffer;
    

    while(read_line(line)!=NULL){
        
        char *string=read_line(line);

        strip_comments(string);
        trim_spaces(string);
        
        // check for labels
        if(string[0]=='('){
            buffer=malloc(strlen(string));
            strcpy(buffer, string+1);

            if(buffer[strlen(buffer)-1]==')'){
                buffer[strlen(buffer)-1]='\0';
            }
            add_sym(buffer, line);

            //create a new node in the symbol table
            
        }else{
            if(head_n==NULL){ 
                head_n->assembly=string;
            }

        }
        
        


        free(buffer);
        // next line
        line++;
    }
   
}






void add_sym(char *label, int line, sym_t *current){
    
    // find the last node
    while(current->next!=NULL){
        current=current->next;
    }
    // create a new node for label
    if(current->symbol==NULL){
        sym_t *head=malloc(sizeof(sym_t));
        current->next=head;
        current=head;
    }
    current->symbol=label;
    current->memory_location=line;
}


void output(sym_t *sym_head, asm_n *asm_head){
    asm_n *asm_current=asm_head;
    add_defaults(sym_t *sym_current);
    char *string; 
    char *address;

    

    while(asm_current!=NULL){
        if(asm_current->assembly[0]=='@'){
            if(isdigit(asm_current->assembly[1])){
                    address=find_symbol(asm_current->assembly[1]);
                    if(address==NULL){
                        add_sym(asm_current->assembly[1], *address, asm_current);
                    }
                    string=realloc(asm_current->assembly[0], strlen(*address)+1);
                    strcpy('@', string);
                    strcat(*address, string);
            }
            a_instruction(sym_head, asm_current);
        }else{
            c_instuction(sym_head, asm_current);
        }
    asm_current=asm_current->next;
    }





}


unsigned int a_instruction(sym_t *sym_head, asm_n *asm_head){

}

unsigned int c_instruction(sym_t *sym_head, asm_n *asm_head){

}

void add_defaults(sym_t *sym_head){ 

}