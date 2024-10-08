#include<stdio.h>
#include<stdlib.h>

/*
* This version of the vm translator implements the translation of push/pop and arithmetic/logical commands.
* The second version of this translator which will be built in project 8, adds functionality for translating branching and function commands.
* 
* @author Sami Ismail
* @param vm file
* @return hack assembly file
*/

typedef struct cmd{
    char *command_type;
    char *arg1;
    char *arg2;
    struct cmd *next;
}cmd; 

// linked list to find the locations of segment poiners. e.g. SP - 0. 
typedef struct mp{ 
    char *segment_pointer;
    unsigned int value; 
    unsigned int memory_location; 
    struct mp *next;
}mp;


int main(){

    cmd *head=malloc(sizeof(cmd));
    char *filename;
    void build_list(cmd *head, FILE *fp, char *filename);
    void add_defaults(mp *head);

    mp *head=malloc(sizeof(mp));
    add_defaults(head);


    return 0;
}

void build_list(cmd *head, FILE *fp, char *filename){

    cmd *current=head;
    char *vm;
    unsigned int lp=0;
    char *string;
    while(read_line(lp)!=NULL){
        vm=read_line(lp);
        
        
        strip_comments(vm);
        // leave spaces for parsing

        string=strtok(vm, ' ');
        if(!strcmp(string, "push")){
            current->command_type="C_PUSH";
            current->arg1=strtok(NULL, ' ');
            current->arg2=strtok(NULL, ' ');
        }else if(!strcmp(string, "pop")){
            current->command_type="C_POP";
            current->arg1=strtok(NULL, ' ');
            current->arg2=strtok(NULL, ' ');
        }else{
            current->command_type="C_ARITHMETIC";
            current->arg1=strtok(NULL, ' ');
            current->arg2=NULL;
        }

        codewriter(current, filename);
        
        /*  
        current->command=strtok(vm, ' ');
        current->arg1=strtok(NULL, ' ');
        if(strtok(NULL, ' ')!=NULL){
            current->arg2=strtok(NULL, ' ');
            codewriter(current, 0);
        }else{
            current->arg2=NULL;
            codewriter(current, 1);
        }
        */

        lp++;
    }
}



/*
typedef struct mp{ 
    char *segment_pointer;
    unsigned int value; 
    unsigned int memory_location; 
    struct mp *next;
}mp;
*/



void add_defaults(mp *head){
    mp *current=head;

    add_sym(current, "SP", 0, 256);
    add_sym(current, "LCL", 1, 1015);
    add_sym(current, "ARG", 2, );
    add_sym(current, "THIS", 3, );
    add_sym(current, "THAT", 5,);

}


void add_sym(mp *current, char *segment_name, unsigned int location, unsigned int value){

    current->segment_pointer=segment_name;
    current->value=value;
    current->memory_location=location;

    if(current->next==NULL){
        current->next=malloc(sizeof(mp));
        current=current->next;
    }

} 
