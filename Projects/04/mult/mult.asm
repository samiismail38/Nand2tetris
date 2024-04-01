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


   
	@7
	D=A
	@R0
	M=D

	@6
	D=A
	@R1
	M=D


(LOOP)
    @R0
    D=M
    @i
    D=D-M
    @CONT
    D;JEQ

    @R1
    D=M
    @sum
    D=D+M
    M=D

    @i
    M=M+1
    @LOOP
    0;JEQ


(CONT)
    @sum
    D=M
    @R2
    M=D
    @END
    0;JEQ

(END)
    @END
    0;JEQ


  

