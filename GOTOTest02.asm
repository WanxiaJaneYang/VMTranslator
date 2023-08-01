@1
D=A
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

@3
D=A
@SP
A=M
M=D
@SP
M=M+1

@_ADD
0;JMP

@SP
AM=M-1
D=M
A=A-1
M=M-D

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

(_ADD)
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
@1
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