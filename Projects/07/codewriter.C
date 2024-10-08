#include<stdio.h>
#include<stdlib.h>
#include<vm_translator.C>

/*
* Generates assembly for push/pop and arithmetic/logic commands using codewriter function.
* Parsing is handled by the build_list function in __main__
*
* @author Sami Ismail
* @param node pointer of the cmd linked list
* @return char pointer representing the translated vm code
*/


void codewriter(cmd *current, char *filename){
    FILE *fp=fopen("output.asm","w");
    
    char *command_type=current->command_type;
    char *arg1=current->arg1;
    unsigned int arg2=current->arg2;
    
    void codewriter(cmd *current, char *filename);
    unsigned int find_sp(char *memory_segment);

   
    // constructor
    // writePushPop
    
    if(!strcmp(command_type, "C_ARITHMETIC")){ 
        /*
        SP--
        @SP
        D=M
        A=A-1
        M=M {any valid operation} D    
        */
        if(!strcmp(arg1, "add") || !strcmp(arg1, "sub") || !strcmp(arg1, "eq") || !strcmp(arg1, "gt") || !strcmp(arg1, "lt") || !strcmp(arg1, "and") || !strcmp(arg1, "or")){ 
            fprintf("output.asm", "%s", "SP--\n");
            fprintf("output.asm", "%s", "@SP\n");
            fprintf("output.asm", "%s", "D=M\n");
            fprintf("output.asm", "%s", "A=A-1\n");
        }else{
            fprintf("output.asm", "%s", "@SP\n");
            fprintf("output.asm", "%s", "D=M\n");
            fprintf("output.asm", "%s", "A=A-1\n");
        }
        if(!strcmp(arg1, "add")){
            fprintf("output.asm", "%s", "M=M+D\n");
        }else if(!strcmp(arg1, "sub")){
            fprintf("output.asm", "%s", "M=M-D\n");
        }else if(!strcmp(arg1, "neg")){
            fprintf("output.asm", "%s", "M=-M\n");
        }else if(!strcmp(arg1, "eq")){
            
        }else if(!strcmp(arg1, "gt")){

        }else if(!strcmp(arg1, "lt")){

        }else if(!strcmp(arg1, "and")){
            fprintf("output.asm", "%s", "M=M&D\n");
        }else if(!strcmp(arg1, "or")){
            fprintf("output.asm", "%s", "M=M|D\n");
        }else if(!strcmp(arg1, "not")){
            fprintf("output.asm", "%s", "M=!M\n");
        }
        
    }else if(!strcmp(command_type, "C_PUSH") || !strcmp(command_type, "C_POP")){
        if(!strcmp(command_type, "C_PUSH")){
            if(!strcmp(arg1, "local") || !strcmp(arg1, "argument") || !strcmp(arg1, "this") || !strcmp(arg1, "that") || !strcmp(arg1, "temp")){ 
                if(!strcmp(arg1, "local")){
                    push_template("LCL", arg2);
                }else if(!strcmp(arg1, "argument")){
                    push_template("ARG", arg2);
                }else if(!strcmp(arg1, "this")){
                    push_template("THIS", arg2);
                }else if(!strcmp(arg1, "that")){
                    push_template("THAT", arg2);
                }else if(!strcmp(arg1, "temp")){
                    push_template("TEMP", arg2);
                }
            }else if(!strcmp(arg1, "static")){
                // goes to [filnemae].i and puts its value in D. Addr=D=*[filename].i.
                fprintf("output.asm", "%s %s %s %d %s", "@", filename, ".", arg2, "\n");
                fprintf("output.asm", "%s", "D=M\n");

                // *SP=D
                fprintf("output.asm", "%s", "@SP\n");
                fprintf("output.asm", "%s", "M=D\n");

                //SP++
                fprintf("output.asm", "%s", "@R0\n");
                fprintf("output.asm", "%s", "M=M+1\n");
            }else  if(!strcmp(arg1, "pointer")){
                if(arg2==0){
                    arg1="THIS";
                }else{
                    arg1="THAT";
                }
                fprintf("output.asm", "%s %s %s", "@", arg1, "\n");
                fprintf("output.asm", "%s", "D=M\n");

                fprintf("output.asm", "%s", "@SP\n");
                fprintf("output.asm", "%s", "M=D\n");
                
                fprintf("output.asm", "%s", "@R0\n");
                fprintf("output.asm", "%s", "M=M+1\n");

            }

        }else if(!strcmp(command_type, "C_POP")){
            // local, argument, this, that
            /*
            addr=segmentPointer+i
            SP--
            RAM[addr] = RAM[SP]
            */
            if(!strcmp(arg1, "local") || !strcmp(arg1, "argument") || !strcmp(arg1, "this") || !strcmp(arg1, "that") || !strcmp(arg1, "temp")){
                if(!strcmp(arg1, "local")){
                    pop_template("LCL", arg2);
                }else if(!strcmp(arg1, "argument")){
                    pop_template("ARG", arg2);
                }else if(!strcmp(arg1, "THIS")){
                    pop_template("THIS", arg2);
                }else if(!strcmp(arg1, "that")){
                    pop_template("THAT", arg2);
                }else if(!strcmp(arg1, "temp")){
                    // temp
                    /*
                    addr=5+i
                    SP--
                    RAM[addr]=RAM[SP]
                    */
                    pop_template("TEMP", arg2);
                }
            }else if(!strcmp(arg1, "static")){
                // satic
                /*
                addr={filename}.i
                SP--
                RAM[addr]=RAM[SP]
                */
            
                fprintf("output.asm", "%s", "@R0\n");
                fprintf("output.asm", "%s", "M=M-1\n");

                fprintf("output.asm", "%s", "@SP\n");
                fprintf("output.asm", "%s", "D=M\n");

                fprintf("output.asm", "%s %s %s %d %s", "@", filename, ".", arg2, "\n");
                fprintf("output.asm", "%s", "M=D\n");
            }else if(!strcmp(arg1, "pointer")){
                    
                // pointer 
                /*
                pop pointer 0 -> pop THIS
                pop pointer 1 -> pop THAT
                */

                fprintf("output.asm", "%s", "@R0\n");
                fprintf("output.asm", "%s", "@M=M-1\n"); 
                fprintf("output.asm", "%s", "@SP\n");
                fprintf("output.asm", "%s", "@D=M\n");
                     
                if(arg2==0){ 
                    fprintf("output.asm", "%s", "@THIS\n");
                }else{
                    fprintf("output.asm", "%s", "@THAT\n");
                }
                fprintf("output.asm", "%s", "@M=D\n");
            } 
        }
    }
    fclose(fp);
}




// push template that works for push commands of the form push {local/argument/this/that/temp} i.
void push_template(char *memory_segment, unsigned int arg2){
    
    if(!strcmp(memory_segment, "constant")){
        fprintf("output.asm", "%s %d %s", "@", arg2, "\n");
        fprintf("output.asm", "%s", "D=A\n");

    }else{ 
        // D = Memory_segment + arg2    
        if(!strcmp(memory_segment, "temp")){
            fprintf("output.asm", "%s %d %s", "@", 5, "\n");
        }else{ 
            fprintf("output.asm", "%s %s %s", "@", memory_segment, "\n");
        }
        fprintf("output.asm", "%s", "D=A\n");
        fprintf("output.asm", "%s %d %s", "@", arg2, "\n");
        fprintf("output.asm", "%s", "D=D+A\n");

        // D =  RAM[ Memory_segment + arg2 ]   
        fprintf("output.asm", "%s", "A=D\n");
        fprintf("output.asm", "%s", "D=M\n");
    }

    // assigns value pointed by SP to D=*Addr.
    fprintf("output.asm", "%s", "@SP\n");
    fprintf("output.asm", "%s", "M=D\n");

    // SP++
    fprintf("output.asm", "%s", "@0\n");
    fprintf("output.asm", "%s", "M=M+1\n");


}

void pop_template(char *memory_segment, unsigned int arg2){

    // Assigns memory_segment+i to an address variable Addr 
    if(!strcmp(memory_segment, "TEMP")){
        fprintf("output.asm", "%s %d %s", "@", 5, "\n");
    }else{
        fprintf("output.asm", "%s %s %s", "@", memory_segment, "\n");
    }
    

    fprintf("output.asm", "%s", "@D=A\n");
    fprintf("output.asm", "%s %s %s", "@", arg2, "\n");
    fprintf("output.asm", "%s", "D=D+A\n");
    fprintf("output.asm", "%s", "@Addr\n");
    fprintf("output.asm", "%s", "M=D\n");

    // SP--
    fprintf("output.asm", "%s", "@R0\n");
    fprintf("output.asm", "%s", "M=M-1\n");

    // *Addr = *SP
    fprintf("output.asm", "%s", "@SP\n");
    fprintf("output.asm", "%s", "D=M\n");
    
    fprintf("output.asm", "%s", "@Addr\n");
    fprintf("output.asm", "%s", "A=M\n");
    fprintf("output.asm", "%s", "M=D\n");
}

