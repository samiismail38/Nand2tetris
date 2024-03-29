// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// Assumes that R0 >= 0, R1 >= 0, and R0 * R1 < 32768.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// pseudo
//
//LOOP:
//sum=0;
// for(i=1; i<=R0; ++i)
//      sum+=R1;
// R2=sum;


  
	@i
	M=0

(CONT)
    @i
    M=0
	@KBD
	D=A
    @LOOPY
    D;JEQ
    
    @LOOPT
    0;JEQ

(LOOPY)
    @8191
    D=A
    @i
    D=D-M
    @CONT
    D;JEQ


    @16384
    D=A
    @i 
    D=D+M
    @D
    M=-1

    @i 
    M=M+1

    @LOOPY
    0;JEQ

(LOOPT)
    @8191
    D=A
    @i
    D=D-A
    @CONT
    D;JEQ

    @16384
    D=A
    @i 
    D=D+M
    @D
    M=0
     
    @i 
    M=M+1

    @LOOPT
    0;JEQ
  

