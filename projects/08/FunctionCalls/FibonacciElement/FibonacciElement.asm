@261
D=A
@SP
M=D
@Sys.init
0;JMP
(Main.fibonacci)
@ARG
D=M
@0
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
@2
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
A=A-1
D=M-D
M=-1
@LT2
D;JLT
@SP
A=M-1
M=0
(LT2)
@SP
AM=M-1
D=M
@IF_TRUE
D;JNE
@IF_FALSE
0;JMP
(IF_TRUE)
@ARG
D=M
@0
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@13
M=D
@5
A=D-A
D=M
@14
M=D
@SP
A=M-1
D=M
@ARG
A=M
M=D
D=A+1
@SP
M=D
@13
AM=M-1
D=M
@THAT
M=D
@13
AM=M-1
D=M
@THIS
M=D
@13
AM=M-1
D=M
@ARG
M=D
@13
AM=M-1
D=M
@LCL
M=D
@14
A=M
0;JMP
(IF_FALSE)
@ARG
D=M
@0
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
@2
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
A=A-1
M=M-D
@Main.fibonacci4
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@6
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Main.fibonacci
0;JMP
(Main.fibonacci4)
@ARG
D=M
@0
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
@1
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
A=A-1
M=M-D
@Main.fibonacci6
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@6
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Main.fibonacci
0;JMP
(Main.fibonacci6)
@SP
M=M-1
A=M
D=M
A=A-1
M=M+D
@LCL
D=M
@13
M=D
@5
A=D-A
D=M
@14
M=D
@SP
A=M-1
D=M
@ARG
A=M
M=D
D=A+1
@SP
M=D
@13
AM=M-1
D=M
@THAT
M=D
@13
AM=M-1
D=M
@THIS
M=D
@13
AM=M-1
D=M
@ARG
M=D
@13
AM=M-1
D=M
@LCL
M=D
@14
A=M
0;JMP
(Sys.init)
@4
D=A
@SP
A=M
M=D
@SP
M=M+1
@Main.fibonacci8
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@6
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Main.fibonacci
0;JMP
(Main.fibonacci8)
(WHILE)
@WHILE
0;JMP