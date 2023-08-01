@2
D=A
@SP
A=M
M=D
@SP
M=M+1

@3
D=A
@SP
A=M
M=D
@SP
M=M+1

@SP
AM=M-1
D=M
A=A-1
M=D+M

@SP
AM=M-1
D=M
@R13
M=D
@LCL
D=M
@0
D=D+A
@R14
M=D
@R13
D=M
@R14
A=M
M=D

(_END)
@_END
0;JMP

@0
D=A
@SP
A=M
M=D
@SP
M=M+1

@SP
AM=M-1
D=M
@R13
M=D
@LCL
D=M
@0
D=D+A
@R14
M=D
@R13
D=M
@R14
A=M
M=D