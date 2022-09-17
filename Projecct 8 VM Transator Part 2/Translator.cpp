#include <bits/stdc++.h>

using namespace std;

//MISC
string END = "(END)\n@END\n0;JMP\n";

//ARITHMETIC
string ADD() {return "@SP\nM=M-1\nA=M\nD=M\nA=A-1\nM=M+D\n";}
string SUB() {return "@SP\nM=M-1\nA=M\nD=M\nA=A-1\nM=M-D\n";}
string NEG() {return "@SP\nA=M-1\nM=-M\n";}
string EQ(int i) {return "@SP\nM=M-1\nA=M\nD=M\nA=A-1\nD=M-D\nM=-1\n@EQ"+to_string(i)+"\nD;JEQ\n@SP\nA=M-1\nM=0\n(EQ"+to_string(i)+")\n";}
string GT(int i) {return"@SP\nM=M-1\nA=M\nD=M\nA=A-1\nD=M-D\nM=-1\n@GT"+to_string(i)+"\nD;JGT\n@SP\nA=M-1\nM=0\n(GT"+to_string(i)+")\n";} 
string LT(int i) {return"@SP\nM=M-1\nA=M\nD=M\nA=A-1\nD=M-D\nM=-1\n@LT"+to_string(i)+"\nD;JLT\n@SP\nA=M-1\nM=0\n(LT"+to_string(i)+")\n";} 
string AND() {return "@SP\nM=M-1\nA=M\nD=M\nA=A-1\nM=M&D\n";}
string OR() {return "@SP\nM=M-1\nA=M\nD=M\nA=A-1\nM=M|D\n";}
string NOT() {return "@SP\nA=M-1\nM=!M\n";}

//MEMORY
string push(int i){return "\n@"+to_string(i)+"\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";}
string PUSH(string argument, int i){return "@"+argument+"\nD=M" + push(i);} //LCL, ARG, THIS, THAT
string PUSH_TEMP(int i){return "@R5\nD=A"+push(i);} //TEMP
string PUSH_POINTER(int i){return "@R3\nD=A"+push(i);} //POINTER
string PUSH_CONSTANT(int i){return "@"+to_string(i)+"\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";}//CONSTANT
string PUSH_STATIC(int i, string fileName){return "@"+fileName +"."+ to_string(i)+"\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";}//STATIC
string PUSH_LABEL(string s){return "@"+s+"\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";}
string PUSH_ADDRESS(string s){return "@"+s+"\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";}

string pop(string argument, int i, char c){return "@"+argument+"\nD="+c+"\n@"+to_string(i)+"\nD=D+A\n@R13\nM=D\n@SP\nM=M-1\nA=M\nD=M\n@R13\nA=M\nM=D\n";}
string POP(string argument, int i) {return pop(argument, i,'M');}
string POP_TEMP(int i) {return pop("R5", i,'A');}
string POP_POINTER(int i) {return pop("R3", i,'A');}
string POP_STATIC(int i,string fileName) {return "@"+fileName + "."+to_string(i)+"\nD=A\n@R13\nM=D\n@SP\nM=M-1\nA=M\nD=M\n@R13\nA=M\nM=D\n";}

//PROGRAM FLOW
string LABEL(string name){return "("+name+")\n";}
string IFGOTO(string name){return "@SP\nAM=M-1\nD=M\n@"+name+"\nD;JNE\n";}
string GOTO(string name){return "@"+name+"\n0;JMP\n";}

//FUNCTION function f k
string FUNCTION(string name, int variables){ 
    string s = "(" + name + ")\n";
    for(int i = 0; i<variables; i++){ //initialize local variable positions
        s+=PUSH_CONSTANT(0);
    }
    return s;
}//all commands in between are pushed normally
//RETURN return
string RETURN(){
    string s = "";
    //0. Save return address in case of 0 arguments
    s += "@LCL\nD=M\n@13\nM=D\n"; //store the address of LCL
    s += "@5\nA=D-A\nD=M\n@14\nM=D\n"; //stores return address (LCL-5) on register 14

    //1. Return the value to the top of the stack before function f
    s += "@SP\nA=M-1\nD=M\n@ARG\nA=M\nM=D\n";//Set the return position (Arg 0) to the top of the stack
    s += "D=A+1\n@SP\nM=D\n"; //set stack to arg 0 + 1
    
    //Restore all addresses
    s += "@13\nAM=M-1\nD=M\n@THAT\nM=D\n";//THAT
    s += "@13\nAM=M-1\nD=M\n@THIS\nM=D\n";//THAT
    s += "@13\nAM=M-1\nD=M\n@ARG\nM=D\n";//ARG
    s += "@13\nAM=M-1\nD=M\n@LCL\nM=D\n";//LCL

    //Go to return address
    s += "@14\nA=M\n0;JMP\n";
    return s;
}

//CALL FUNCTION: call f n

string CALL(string name, string returnAddress, int arguments){//there are n arguments in memory saved beforehand
    string s = "";
    s += PUSH_LABEL(returnAddress);//push return address
    s += PUSH_ADDRESS("LCL");
    s += PUSH_ADDRESS("ARG");
    s += PUSH_ADDRESS("THIS");
    s += PUSH_ADDRESS("THAT");
    s += "@SP\nD=M\n@" + to_string(arguments + 5) + "\nD=D-A\n@ARG\nM=D\n";
    s += "@SP\nD=M\n@LCL\nM=D\n";
    s += GOTO(name);
    s += "(" + returnAddress + ")\n";
    return s;
}


string parse(string fileName, int &counter)
{
    ifstream fin(fileName+".vm");

    string sout;

    string line;
    while(getline(fin,line)){
        stringstream ss(line);
        if(ss.str().empty()) continue;
        string first, second; int third;
        ss >> first;
        if(first == "//") continue;
        else if(first == "pop"){
            ss >> second >> third;
            if(second == "local") sout+=POP("LCL",third);
            else if(second == "argument")sout+=POP("ARG",third);
            else if(second == "this")sout+=POP("THIS",third);
            else if(second == "that")sout+=POP("THAT",third);
            else if(second == "temp")sout+=POP_TEMP(third);
            else if(second == "pointer")sout+=POP_POINTER(third);
            else if(second == "static")sout+=POP_STATIC(third, fileName);
            else sout += "something is wrong!!!\n";
        }
        else if(first == "push"){
            ss >> second >> third;
            if(second == "local") sout+=PUSH("LCL",third);
            else if(second == "argument")sout+=PUSH("ARG",third);
            else if(second == "this")sout+=PUSH("THIS",third);
            else if(second == "that")sout+=PUSH("THAT",third);
            else if(second == "temp")sout+=PUSH_TEMP(third);
            else if(second == "pointer")sout+=PUSH_POINTER(third);
            else if(second == "constant")sout+=PUSH_CONSTANT(third);
            else if(second == "static")sout+=PUSH_STATIC(third, fileName);
            else sout += "something is wrong!!!\n";
        }
        else if(first == "label"){
            ss >> second;
            sout += LABEL(second);
        }
        else if(first == "goto"){
            ss >> second;
            sout += GOTO(second);
        }
        else if(first == "if-goto"){
            ss >> second;
            sout += IFGOTO(second);
        }
        else if(first == "function"){
            ss >> second >> third;
            sout += FUNCTION(second, third);
        }
        else if(first == "return"){
            sout += RETURN();
        }
        else if(first == "call"){
            ss >> second >> third;
            counter++;
            sout += CALL(second, second + to_string(counter), third);
        }
        else{
            counter++;
            if(first == "add") sout += ADD();
            else if(first == "sub") sout += SUB();
            else if (first == "neg") sout += NEG();
            else if(first == "eq") sout += EQ(counter);
            else if(first == "gt") sout += GT(counter);
            else if(first == "lt") sout += LT(counter);
            else if (first == "and") sout += AND();
            else if(first == "or") sout += OR();
            else if (first == "not") sout += NOT();
            else sout += "something is wrong!!!\n";
        }

    }
    return sout;
}


int main()
{    
    int counter = 1;
    vector<string> files;
    files.push_back("Sys");
    files.push_back("Class1");
    files.push_back("Class2");
    string outFileName = "StaticsTest.asm";

    string sout = "@261\nD=A\n@SP\nM=D\n";
    sout += "@Sys.init\n0;JMP\n";

    for(string s : files){
        sout += parse(s, counter);
    }
    
    ofstream fout(outFileName);
    fout << sout;

    return 0;
}