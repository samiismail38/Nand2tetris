// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen
// by writing 'black' in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen by writing
// 'white' in every pixel;
// the screen should remain fully clear as long as no key is pressed.

@i
M=0

(CONT)
    @i
    M=0
    @LOOPY
    KBD;JEQ
    
    @LOOPT
    0;JEQ

(LOOPY)
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
 