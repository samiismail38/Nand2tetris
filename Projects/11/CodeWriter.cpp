#include "CodeWriter.h"
#include <iostream>


CodeWriter::CodeWriter(const string& outputFileName){
  outputFile.opoen(outputFileName);
}



CodeWriter::~CodeWriter(){
  if(outputFile.is_open()){
    outputFile.close();
  }
}

void CodeWriter::writeArithmetic(const string& command){
  outputFile << command << endl;
}



void CodeWriter::writePushPop(const string& command, const string& segment, int index){
  outputFile << command << " " << segment << " " << index << endl; 
} 

void CodeWriter::writeLabel(const string& label){
  outputFile << "label " << label << endl;
}


void CodeWriter::writeGoto(const string& label){
  outputFile << "goto " << label << endl;
}

void CodeWriter::writeIf(const string& label){
  outputFile << "if-goto " << label << endl;
}

void CodeWriter::writeCall(const string& functionName, int numArgs){
  outputFile << "call " << functionName << " " << numArgs << endl;
}

void codeWriter::writeFunction(const string& functionName, int numLocals){
  outputFile << "function " << functionName << " " << numLocals << endl;
}

void CodeWriter::writeReturn(){
  outputFile << "return " << endl; 

}