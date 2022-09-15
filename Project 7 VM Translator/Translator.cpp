#include <bits/stdc++.h>

using namespace std;

string fileName = "StackTest";
string outFileName = "Output.asm";
int counter = 0;

//MISC
string END = "(END)\n@END\n0;JMP\n";

//ARITHMETIC
string ADD = "@SP\nM=M-1\nA=M\nD=M\nA=A-1\nM=M+D\n";
string SUB = "@SP\nM=M-1\nA=M\nD=M\nA=A-1\nM=M-D\n";
string NEG = "@SP\nA=M-1\nM=-M\n";
string EQ(int i) {return "@SP\nM=M-1\nA=M\nD=M\nA=A-1\nD=M-D\nM=-1\n@EQ"+to_string(i)+"\nD;JEQ\n@SP\nA=M-1\nM=0\n(EQ"+to_string(i)+")\n";}
string GT(int i) {return"@SP\nM=M-1\nA=M\nD=M\nA=A-1\nD=M-D\nM=-1\n@GT"+to_string(i)+"\nD;JGT\n@SP\nA=M-1\nM=0\n(GT"+to_string(counter)+")\n";} 
string LT(int i) {return"@SP\nM=M-1\nA=M\nD=M\nA=A-1\nD=M-D\nM=-1\n@LT"+to_string(i)+"\nD;JLT\n@SP\nA=M-1\nM=0\n(LT"+to_string(counter)+")\n";} 
string AND = "@SP\nM=M-1\nA=M\nD=M\nA=A-1\nM=M&D\n";
string OR = "@SP\nM=M-1\nA=M\nD=M\nA=A-1\nM=M|D\n";
string NOT = "@SP\nA=M-1\nM=!M\n";

//MEMORY
string push(int i){return "\n@"+to_string(i)+"\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";}
string PUSH(string argument, int i){return "@"+argument+"\nD=M" + push(i);} //LCL, ARG, THIS, THAT
string PUSH_TEMP(int i){return "@R5\nD=A"+push(i);} //TEMP
string PUSH_POINTER(int i){return "@R3\nD=A"+push(i);} //POINTER
string PUSH_CONSTANT(int i){return "@"+to_string(i)+"\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";}//CONSTANT
string PUSH_STATIC(int i){return "@"+fileName +"."+ to_string(i)+"\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";}//STATIC

string pop(string argument, int i, char c){return "@"+argument+"\nD="+c+"\n@"+to_string(i)+"\nD=D+A\n@R13\nM=D\n@SP\nM=M-1\nA=M\nD=M\n@R13\nA=M\nM=D\n";}
string POP(string argument, int i) {return pop(argument, i,'M');}
string POP_TEMP(int i) {return pop("R5", i,'A');}
string POP_POINTER(int i) {return pop("R3", i,'A');}
string POP_STATIC(int i) {return "@"+fileName + "."+to_string(i)+"\nD=A\n@R13\nM=D\n@SP\nM=M-1\nA=M\nD=M\n@R13\nA=M\nM=D\n";}




int main()
{
    ifstream fin(fileName+".vm");
    ofstream fout(outFileName);

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
            else if(second == "static")sout+=POP_STATIC(third);
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
            else if(second == "static")sout+=PUSH_STATIC(third);
            else sout += "something is wrong!!!\n";
        }
        else{
            counter++;
            if(first == "add") sout += ADD;
            else if(first == "sub") sout += SUB;
            else if (first == "neg") sout += NEG;
            else if(first == "eq") sout += EQ(counter);
            else if(first == "gt") sout += GT(counter);
            else if(first == "lt") sout += LT(counter);
            else if (first == "and") sout += AND;
            else if(first == "or") sout += OR;
            else if (first == "not") sout += NOT;
            else sout += "something is wrong!!!\n";
        }

    }
    fout << sout<<END;

    return 0;
}