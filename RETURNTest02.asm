@16
D=A
@1
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1

@RETURN_1
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
@3
D=M
@SP
A=M
M=D
@SP
M=M+1
@4
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@1
D=D-A
@5
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@f_RETURNTest02.fib
0;JMP
(RETURN_1)
@SP
AM=M-1
D=M
@R13
M=D
@16
D=A
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

(f_RETURNTest02.fib)

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
@_BASE_CASE
D+1;JEQ

@_RECURSION
0;JMP

(_BASE_CASE)
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

@SP
A=M-1
D=M
@ARG
A=M
M=D
D=A+1
@R15
M=D
@LCL
D=M
@SP
M=D
@SP
AM=M-1
D=M
@R13
M=D
@3
D=A
@1
D=D+A
@R14
M=D
@R13
D=M
@R14
A=M
M=D
@SP
AM=M-1
D=M
@R13
M=D
@3
D=A
@0
D=D+A
@R14
M=D
@R13
D=M
@R14
A=M
M=D
@SP
AM=M-1
D=M
@ARG
M=D
@SP
AM=M-1
D=M
@LCL
M=D
@SP
AM=M-1
D=M
@R13
M=D
@R15
D=M
@SP
M=D
@R13
A=M
0;JMP

(_RECURSION)
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
AM=M-1
D=M
A=A-1
M=M-D

@RETURN_2
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
@3
D=M
@SP
A=M
M=D
@SP
M=M+1
@4
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@1
D=D-A
@5
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@f_RETURNTest02.fib
0;JMP
(RETURN_2)
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
AM=M-1
D=M
A=A-1
M=M-D

@RETURN_3
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
@3
D=M
@SP
A=M
M=D
@SP
M=M+1
@4
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@1
D=D-A
@5
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@f_RETURNTest02.fib
0;JMP
(RETURN_3)
@SP
AM=M-1
D=M
A=A-1
M=D+M

@SP
A=M-1
D=M
@ARG
A=M
M=D
D=A+1
@R15
M=D
@LCL
D=M
@SP
M=D
@SP
AM=M-1
D=M
@R13
M=D
@3
D=A
@1
D=D+A
@R14
M=D
@R13
D=M
@R14
A=M
M=D
@SP
AM=M-1
D=M
@R13
M=D
@3
D=A
@0
D=D+A
@R14
M=D
@R13
D=M
@R14
A=M
M=D
@SP
AM=M-1
D=M
@ARG
M=D
@SP
AM=M-1
D=M
@LCL
M=D
@SP
AM=M-1
D=M
@R13
M=D
@R15
D=M
@SP
M=D
@R13
A=M
0;JMP