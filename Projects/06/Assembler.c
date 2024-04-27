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
    unsigned int symbol_count=0; 

    

    while(asm_current!=NULL){
        
        if(asm_current->assembly[0]=='@'){
            
            if(isdigit(asm_current->assembly[1])){
                    address=find_symbol(asm_current->assembly[1]);

                    if(address==NULL){
                        add_sym(asm_current->assembly[1], 16+symbol_count, asm_current);
                        address=16+symbol_count;
                    }
                    string=realloc(asm_current->assembly[0], strlen(address)+1);
                    strcpy('@', string);
                    strcat(address, string);

                    
            }
            a_instruction(asm_current->assembly);
        }else{
            c_instuction(asm_current->assembly);
        }
    asm_current=asm_current->next;
    }

}


unsigned int a_instruction(char *assembly){
    // removes the @ symbol and converts string to int

    if(assembly[0]=='@'){
        assembly++;
    }
    unsigned int output=(unsigned int)strtol(assembly, NULL, 10);

    // generate binary
   
    return  output;
}

unsigned int c_instruction(char *assembly){
    // 111 a cccccc ddd jjj
    unsigned int prefix = 111;
    char *command; 
    char *destination;
    char *_jump;

    unsigned int comp;
    unsigned int dest;
    unsigned int jump;
    unsigned int a; 

    
    if(strchr(assembly, '=')!=NULL){
        jump=0b000;
        destination=strtok(assembly, '=');
        command=strtok(NULL, '=');
    }else{
        dest=0b000;
        command=strtok(assembly, ';');
        _jump=strtok(NULL, ';');
    }
    char *m_position=strchr(command, 'M');
    if(m_position!=NULL){
        a=0b1;
        *m_position='A';
    }else{
        a=0b0; 
    }
    // determine comp
    if(strcmp(command, '0')){
        comp=0b101010;
    }else if(strcmp(command, '1')){
        comp=0b111111;
    }else if(strcmp(command, '-1')){
        comp=0b111010;
    }else if(strcmp(command, 'D')){
        comp=0b001100;
    }else if(strcmp(command, 'A')){
        comp=0b110000;
    }else if(strcmp(command, '!D')){
        comp=0b001101;
    }else if(strcmp(command, '!A')){
        comp=0b110001;
    }else if(strcmp(command, '-D')){
        comp=0b001111;
    }else if(strcmp(command, '-A')){
        comp=0b110011;
    }else if(strcmp(command, 'D+1')){
        comp=0b011111;
    }else if(strcmp(command, 'A+1')){
        comp=0b110111;
    }else if(strcmp(command, 'D-1')){
        comp=0b001110;
    }else if(strcmp(command, 'A-1')){
        comp=0b110010;
    }else if(strcmp(command, 'D+A')){
        comp=0b000010;
    }else if(strcmp(command, 'D-A')){
        comp=0b010011;
    }else if(strcmp(command, 'A-D')){
        comp=0b000111;
    }else if(strcmp(command, 'D&A')){
        comp=0b000000;
    }else if(strcmp(command, 'D|A')){
        comp=0b010101;
    }

    // determine jump
    if(dest==0){
        if(strcmp(_jump, 'JGT')){
            jump=0b001;
        }else if(strcmp(_jump, 'JEQ')){
            jump=0b0101;
        }else if(strcmp(_jump, 'JGE')){
            jump=0b011;
        }else if(strcmp(_jump, 'JLT')){
            jump=0b100;
        }else if(strcmp(_jump, 'JNE')){
            jump=0b101;
        }else if(strcmp(_jump, 'JLE')){
            jump=0b110;
        }else if(strcmp(_jump, 'JMP')){
            jump=0b111;
        }
    }

    //determine dest

    /* 
    if(jump==0){
        if(strcmp(destination, 'M')){
            dest=0b001;
        }else if(strcmp(destination, 'D')){
            dest=0b010;
        }else if(strcmp(destination, 'MD')){
            dest=0b011;
        }else if(strcmp(destination, 'A')){
            dest=0b100; 
        }else if(strcmp(destination, 'AM')){
            dest=0b101;
        }else if(strcmp(destination, 'AD')){
            dest=0b110;
        }else if(strcmp(destination, 'AMD')){
            dest=0b111;
        }

    }
*/
    
    if(strchr(destination, 'A')!=NULL){
        dest|=1<<2;
    }
    if(strchr(destination, 'D')!=NULL){
        dest|=1<<1;
    }
    if(strchr(destination, 'M')!=NULL){
        dest|=1;
    }

// generate output 111 a cccccc ddd jjj
unsigned int output = 0b0;
output |= 111 << 13;
output |= a << 12;
output |= comp << 6;
output |= dest << 3;
output |= jump;

}

void add_defaults(sym_t *sym_head){ 

add_sym("R0", 0, sym_head);
add_sym("R1", 1, sym_head);
add_sym("R2", 2, sym_head);
add_sym("R3", 3, sym_head);
add_sym("R4", 4, sym_head);
add_sym("R5", 5, sym_head);
add_sym("R6", 6, sym_head);
add_sym("R7", 7, sym_head);
add_sym("R8", 8, sym_head);
add_sym("R9", 9, sym_head);
add_sym("R10", 10, sym_head);
add_sym("R11", 11, sym_head);
add_sym("R12", 12, sym_head);
add_sym("R13", 13, sym_head);
add_sym("R14", 14, sym_head);
add_sym("R15", 15, sym_head);

add_sym("SP", 0, sym_head);
add_sym("LCL", 1, sym_head);
add_sym("ARG", 2, sym_head);
add_sym("THIS", 3, sym_head);
add_sym("THAT", 4, sym_head);

add_sym("SCREEN", 16384, sym_head);
add_sym("KBD", 24576, sym_head);


}