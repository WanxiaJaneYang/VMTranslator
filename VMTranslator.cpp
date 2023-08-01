#include <string>

#include "VMTranslator.h"

using namespace std;
/*
* labels and symbols
* labels EQUAL, END_EQ, GREATER_THAN, END_GT, LESS_THAN, END_LT used in eq, gt, lt functions
* R13, R14 used in pop function
* R15 used in return function
* label generating rule:"_"+label
* function label:"F_"+function_name;
* function return label:"RETURN_"+returnAddress
*/
/**
 * VMTranslator constructor
 */
int VMTranslator::function_count = 0;
int VMTranslator::returnAddress = 0;
int VMTranslator::eqAddress = 0;
int VMTranslator::gtAddress = 0;
int VMTranslator::ltAddress = 0;

VMTranslator::VMTranslator() {
    // Your code here
}

/**
 * VMTranslator destructor
 */
VMTranslator::~VMTranslator() {
    // Your code here
}

/** Generate Hack Assembly code for a VM push operation
segments: constant, local, argument, static, temp, this, that, pointer
*/
string VMTranslator::vm_push(string segment, int offset) {
    string result;
    //case that push constant
    if (segment == "constant") {
        string num = to_string(offset);
        return vm_push_number(num);
    }
    else if (segment == "argument" || segment == "local" || segment == "this" || segment == "that") {
        if (segment == "local") {
            result += "@LCL\n";
        }
        else if (segment == "argument") {
            result += "@ARG\n";
        }
        else if (segment == "this") {
            result += "@THIS\n";
        }
        else if (segment == "that") {
            result += "@THAT\n";
        }
        //find the number first
        result += "D=M\n";
        result = result + "@" + to_string(offset) + "\n"; //@offset
        result += "A=D+A\n";
        result += "D=M\n";  //D stores the number we need to push now
    }
    else if (segment == "static" || segment == "temp") {
        if (segment == "static") {
            result += "@16\n";
        }
        else if (segment == "temp") {
            result += "@5\n";
        }
        result += "D=A\n";
        result = result + "@" + to_string(offset) + "\n"; //@offset
        result += "A=D+A\n";
        result += "D=M\n";  //D stores the number we need to push now
    }
    else {
        //case segment=="pointer"
        //D stores the number we need to push
        if (offset == 0) {
            result += "@3\n";
            result += "D=M\n";
        }
        else if (offset == 1) {
            result += "@4\n";
            result += "D=M\n";
        }
    }
    result += "@SP\n";
    result += "AM=M+1\n";
    result += "A=A-1\n";
    result += "M=D\n";
    return result;
}

/** Generate Hack Assembly code for a VM pop operation
* segments: constant, local, argument, static, temp, this, that, pointer
* use R13 to store number and R14 to store address
* use pop_number_num and pop_address_num to store
*/
string VMTranslator::vm_pop(string segment, int offset) {
    string result;
    //get the data and reduce the sp
    //number stores the number we need to store into sector 
    result += "@SP\n";
    result += "AM=M-1\n";
    result += "D=M\n";

    //store the number first in RAM[1000]
    result += "@1000\n";
    result += "M=D\n";

    //D holds the address to be stored
    if (segment == "local" || segment == "argument" || segment == "this" || segment == "that") {
        if (segment == "local") {
            result += "@LCL\n";
        }
        else if (segment == "argument") {
            result += "@ARG\n";
        }
        else if (segment == "this") {
            result += "@THIS\n";
        }
        else if (segment == "that") {
            result += "@THAT\n";
        }
        result += "D=M\n";
    }
    else if (segment == "static" || segment == "temp" || segment == "pointer") {
        if (segment == "static") {
            result += "@16\n";
        }
        else if (segment == "temp") {
            result += "@5\n";
        }
        else if (segment == "pointer") {
            result += "@3\n";
        }
        result += "D=A\n";
    }
    result = result + "@" + to_string(offset) + "\n"; //@offset
    result += "D=D+A\n";

    //store the target address in RAM[1001]
    result += "@1001\n";
    result += "M=D\n";

    //put the number in correspondent address
    result += "@1000\n";
    result += "D=M\n";
    result += "@1001\n";
    result += "A=M\n";
    result += "M=D\n";
    return result;
}

/** Generate Hack Assembly code for a VM add operation
 @SP
AM=M-1
D=M
A=A-1
M=D+M */
string VMTranslator::vm_add() {
    return "@SP\nAM=M-1\nD=M\nA=A-1\nM=D+M\n";
}

/** Generate Hack Assembly code for a VM sub operation
* @SP
* AM=M-1
* D=M
* A=A-1
* M=M-D
*/
string VMTranslator::vm_sub() {
    return "@SP\nAM=M-1\nD=M\nA=A-1\nM=M-D\n";
}

/** Generate Hack Assembly code for a VM neg operation
* @SP
* A=M-1
* M=-M
*/
string VMTranslator::vm_neg() {
    return "@SP\nA=M-1\nM=-M\n";
}

/** Generate Hack Assembly code for a VM eq operation
* @SP
* AM=M-1
* D=M
* A=A-1
* D=D-M
* @EQUAL_NUMBER
* D;JEQ
* @SP
* A=M-1
* M=0
* @END_EQ_NUMBER
* 0;JMP
* (EQUAL_NUMBER)
* @SP
* A=M-1
* M=-1
* (END_EQ_NUMBER)
*/
string VMTranslator::vm_eq() {
    string eqLabel = "EQUAL" + to_string(eqAddress);
    string endEQLabel = "END_EQ" + to_string(eqAddress);
    eqAddress++;
    string result = "";
    result += "@SP\n";
    result += "AM=M-1\n";
    result += "D=M\n";
    result += "A=A-1\n";
    result += "D=D- M\n";
    result = result + "@" + eqLabel + "\n";
    result += "D;JEQ\n";
    result += "@SP\n";
    result += "A=M-1\n";
    result += "M=0\n";
    result = result + "@" + endEQLabel + "\n";
    result += "0;JMP\n";
    result = result + "(" + eqLabel + ")" + "\n";
    result += "@SP\n";
    result += "A=M-1\n";
    result += "M=-1\n";
    result = result + "(" + endEQLabel + ")\n";
    return result;
}

/** Generate Hack Assembly code for a VM gt operation
* @SP
* AM=M-1
* D=M
* A=A-1
* D=M-D
* @GREATER_THAN
* D;JGT
* @SP
* A=M-1
* M=0
* @END_GT
* 0;JMP
* (GREATER_THAN)
* @SP
* A=M-1
* M=-1
* (END_GT)
*/
string VMTranslator::vm_gt() {
    string gtLabel = "GREATER_THAN" + to_string(gtAddress);
    string endGTLabel = "END_GT" + to_string(gtAddress);
    gtAddress++;
    string result = "";
    result += "@SP\n";
    result += "AM=M-1\n";
    result += "D=M\n";
    result += "A=A-1\n";
    result += "D=M-D\n";
    result = result + "@" + gtLabel + "\n";
    result += "D;JGT\n";
    result += "@SP\n";
    result += "A=M-1\n";
    result += "M=0\n";
    result = result + "@" + endGTLabel + "\n";
    result += "0;JMP\n";
    result = result + "(" + gtLabel + ")" + "\n";
    result += "@SP\n";
    result += "A=M-1\n";
    result += "M=-1\n";
    result = result + "(" + endGTLabel + ")\n";

    return result;
}

/** Generate Hack Assembly code for a VM lt operation
* @SP
* AM=M-1
* D=M
* A=A-1
* D=M-D
* @LESS_THAN
* D;JLT
* @SP
* A=M-1
* M=0
* @END_LT
* 0;JMP
* (LESS_THAN)
* @SP
* A=M-1
* M=-1
* (END_LT)*/
string VMTranslator::vm_lt() {
    string ltLabel = "LESS_THAN" + to_string(ltAddress);
    string endLTLabel = "END_LT" + to_string(ltAddress);
    ltAddress++;
    string result = "";
    result += "@SP\n";
    result += "AM=M-1\n";
    result += "D=M\n";
    result += "A=A-1\n";
    result += "D=M-D\n";
    result = result + "@" + ltLabel + "\n";
    result += "D;JLT\n";
    result += "@SP\n";
    result += "A=M-1\n";
    result += "M=0\n";
    result = result + "@" + endLTLabel + "\n";
    result += "0;JMP\n";
    result = result + "(" + ltLabel + ")" + "\n";
    result += "@SP\n";
    result += "A=M-1\n";
    result += "M=-1\n";
    result = result + "(" + endLTLabel + ")\n";

    return result;
}

/** Generate Hack Assembly code for a VM and operation
* @SP
* AM=M-1
* D=M
* A=A-1
* M=M&D
*/
string VMTranslator::vm_and() {
    return "@SP\nAM=M-1\nD=M\nA=A-1\nM=M&D\n";
}

/** Generate Hack Assembly code for a VM or operation
*  @SP
* AM=M-1
* D=M
* A=A-1
* M=M|D
*/
string VMTranslator::vm_or() {
    return "@SP\nAM=M-1\nD=M\nA=A-1\nM=M|D\n";
}

/** Generate Hack Assembly code for a VM not operation
* @SP
* A=M-1
* M=!M
*/
string VMTranslator::vm_not() {
    return "@SP\nA=M-1\nM=!M\n";
}

/** Generate Hack Assembly code for a VM label operation */
string VMTranslator::vm_label(string label) {
    return "(_" + label + ")";
}

/** Generate Hack Assembly code for a non-user VM label operation */
string VMTranslator::vm_non_user_label(string label)
{
    return "(" + label + ")";
}

/** Generate Hack Assembly code for a VM goto operation */
string VMTranslator::vm_goto(string label) {
    return "@_" + label + "\n0;JMP\n";
}

/** Generate Hack Assembly code for a VM non-user goto operation */
string VMTranslator::vm_goto_non_user(string label)
{
    return "@" + label + "\n0;JMP\n";
}

/** Generate Hack Assembly code for a VM if-goto operation
* @SP
* AM=M-1
* D=M
* @_label
* D+1;JEQ
*/
string VMTranslator::vm_if(string label) {
    return "@SP\nAM=M-1\nD=M\n@_" + label + "\nD;JNE\n";
}

/** Generate Hack Assembly code for a VM function operation */
string VMTranslator::vm_function(string function_name, int n_vars) {
    //label declaration
    string result = "(f_" + function_name + ")\n";

    //push zeros
    for (int i = 0; i < n_vars; i++) {
        result += vm_push_number("0");
    }
    return result;
}

/** Generate Hack Assembly code for a VM call operation */
string VMTranslator::vm_call(string function_name, int n_args) {
    returnAddress++;
    string result = "";

    //push the return address, which is return label
    //push label "return_" + to_string(returnAddress)
    result += "@RETURN_" + to_string(returnAddress) + "\n";
    result += "D=A\n";
    result += "@SP\n";
    result += "A=M\n";
    result += "M=D\n";
    result += "@SP\n";
    result += "M=M+1\n";

    //store current pointer of lcl, arg, this, that
    //store local
    result += "@LCL\n";
    result += "D=M\n";
    result += "@SP\n";
    result += "A=M\n";
    result += "M=D\n";
    result += "@SP\n";
    result += "M=M+1\n";

    //store argument 
    result += "@ARG\n";
    result += "D=M\n";
    result += "@SP\n";
    result += "A=M\n";
    result += "M=D\n";
    result += "@SP\n";
    result += "M=M+1\n";

    //store this, that
    result += vm_push("pointer", 0);
    result += vm_push("pointer", 1);

    //reset args, which is sp-5-n_args
    result += "@SP\n";
    result += "D=M\n";
    result += "@" + to_string(n_args) + "\n";
    result += "D=D-A\n";
    result += "@5\n";
    result += "D=D-A\n";
    result += "@ARG\n";
    result += "M=D\n";

    //reset lcl, which is the current sp
    result += "@SP\n";
    result += "D=M\n";
    result += "@LCL\n";
    result += "M=D\n";

    //jump to the callee's function
    result += vm_goto_non_user("f_" + function_name);

    //initialize a return label
    result += vm_non_user_label("RETURN_" + to_string(returnAddress));
    return result;
}

/** Generate Hack Assembly code for a VM return operation
* Use R15 to store sp_return_address R14 to store return address
*/
string VMTranslator::vm_return() {
    string result = "";
    function_count++;
    string return_base="return_base"+to_string(function_count);
    string return_address="return_address"+to_string(function_count);

    //get the return frame base and save it
    result += "@LCL\n";
    result += "D=M\n";
    result += "@" + return_base + "\n"; 
    result += "M=D\n";

    //get the return address and save it
    result += "@5\n";
    result += "A=D-A\n";
    result += "D=M\n";
    result += "@" + return_address + "\n";
    result += "M=D\n";

    //set the return value into arg 0
    result += vm_pop("argument", 0) + "\n";

    //reset sp
    result += "@ARG\n";
    result += "D=M+1\n";
    result += "@SP\n";
    result += "M=D\n";

    //restore that 
    result += "@" + return_base + "\n";
    result += "A=M-1\n";
    result += "D=M\n";
    result += "@THAT\n";
    result+= "M=D\n";

    //restore this
    result += "@" + return_base + "\n";
    result += "D=M\n";
    result += "@2\n";
    result += "A=D-A\n";
    result += "D=M\n";
    result += "@THIS\n";
    result += "M=D\n";

    //restore arg
    result += "@" + return_base + "\n";
    result += "D=M\n";
    result += "@3\n";
    result += "A=D-A\n";
    result += "D=M\n";
    result += "@ARG\n";
    result += "M=D\n";

    //restore lcl
    result += "@" + return_base + "\n";
    result += "D=M\n";
    result += "@4\n";
    result += "A=D-A\n";
    result += "D=M\n";
    result += "@LCL\n";
    result += "M=D\n";

    //jump to return address
    result += "@" + return_address + "\n";
    result+= "A=M;JMP";
    
   /*
   //get the return address(arg 1) and save
    result += "@LCL\n";
    result += "D=M\n";
    result += "@5\n";
    result += "A=D-A\n";
    result += "D=M \n";
    result = result + "@returnAddress" + to_string(function_count) + "\n";
    result += "M=D\n";

    //get the topmost element and pop to argument 0
    result += vm_pop("argument", 0);

    //get the return sp address(arg 0+1) and save it in sp_return_num
    result += "@ARG\n";
    result += "D=M+1\n";
    result = result + "@sp_return" + to_string(function_count) + "\n";
    result += "M=D \n";

    //reset sp as current local
    result += "@LCL\n";
    result += "D=M\n";
    result += "@SP\n";
    result += "M=D\n";

    //pop that 0, pop this 0
    result += vm_pop("pointer", 1);
    result += vm_pop("pointer", 0);

    //pop argument , pop local 
    result += "@SP\n";
    result += "AM=M-1\n";
    result += "D=M\n";
    result += "@ARG\n";
    result += "M=D\n";
    result += "@SP\n";
    result += "AM=M-1\n";
    result += "D=M\n";
    result += "@LCL\n";
    result += "M=D\n";

    //reset sp as return_sp
    result = result + "@sp_return" + to_string(function_count) + "\n";
    result += "D=M\n";
    result += "@SP\n";
    result += "M=D\n";

    //go to the caller's return label
    result = result + "@returnAddress" + to_string(function_count) + "\n";
    result += "A=M\n";
    result += "0;JMP\n"; 
    */
    return result;
}

/*Generate Hack Assembly code for push a constant number */
string VMTranslator::vm_push_number(string number)
{
    string result = "";
    result += "@" + number + "\n";
    result += "D=A\n";
    result += "@SP\n";
    result += "AM=M+1\n";
    result += "A=A-1\n";
    result += "M=D\n";
    return result;
}
