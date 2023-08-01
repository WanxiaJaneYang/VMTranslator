@3
D=A
@SP
A=M
M=D
@SP
M=M+1

@5
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
D=M-D
@GREATER_THAN0
D;JGT
@SP
A=M-1
M=0
@END_GT0
0;JMP
(GREATER_THAN0)
@SP
A=M-1
M=-1
(END_GT0)

@SP
AM=M-1
D=M
@_CASE_GT
D+1;JEQ

@12
D=A
@SP
A=M
M=D
@SP
M=M+1

@11
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
D=M-D
@LESS_THAN0
D;JLT
@SP
A=M-1
M=0
@END_LT0
0;JMP
(LESS_THAN0)
@SP
A=M-1
M=-1
(END_LT0)

@SP
AM=M-1
D=M
@_CASE_LT
D+1;JEQ

@55
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

@_END
0;JMP

(_CASE_GT)
@11
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

(_CASE_LT)
@30
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
@2
D=D+A
@R14
M=D
@R13
D=M
@R14
A=M
M=D

@_END
0;JMP