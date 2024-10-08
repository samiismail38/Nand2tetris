#ifndef COMPILATION_ENGINE_H
#define COMPILATION_ENGINE_H


#include "JackTokenizer.h"
#include <fstream>
#include <string>

class CompilationEngine(){
private:
  JackTokenizer& tokenizer;
  ofstream outputFile;

  void writeXML(const string &tag, const string& content);


  void compileClass();
  void compileClassVarDec();
  void compileSubroutine();
  void compileParameterList();
  void compileVarDec();
  void compileStatements();
  void compileDo();
  void compileLet();
  void compileWhile();
  void compileReturn();
  void compileIf();
  void compileExpression();
  void compileTerm();
  void compileExpressionList();


public:
  CompilationEngine(JackTokenizer& tokenizer, const string& outputFileName);

};

#endif