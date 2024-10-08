#inlcude "CompilationEngine.h"
#include <iostream>


CompilationEngine::CompilationEngine(JackTokenizer& tokenizer, const string& outputFileName) 
: tokenizer(tokenizer), codeWriter(outputFileName), labelCount(0) {
}


void CompilationEngine::compileClass(){
  tokenizer.advance()

  string className = tokenizer.identifier();
  tokenizer.advance();

  tokenizer.advance();

  while(tokenizer.tokenType() == KEYWORD &&
    (tokenizer.keyWord() == STATIC || tokenizer.keyWord() == FIELD)) {
    compileClassVarDec();
  }
  }





  while(tokenizer.tokenType() == KEYWORD &&
  (tokenizer.keyWord() ==  CONSTRUCTRO || tokenizer.keyWord() == FUNCTION || tokenizer.keyWord() == METHOD)){
    compileSubroutine(className);
  }

  tokenizer.advance();
}

void CompilationEngine::compileClassVarDec(){
  Kind kind = (tokenizer.keyWord() == STATIC) ? STATIC : FIELD;
  tokenizer.advance();

  string type = tokenizer.identifier();
  tokenizer.advance();


  string name = tokenizer.identifier();
  symbolTable.define(name, tyoe, kind);
  tokenizer.advance();


  while (tokenizer.tokenType() == SYMBOL && tokenizer.symbol() == ','){
    tokenizer.advance();
    name = tokenizer.identifier();
    symbolTable.define(name, type, kind);
    tokenizer.advance();
  }

  tokenizer.advance(); 
}



void CompilationEngine::compileSUbroutine(const string& className){
  symbolTable.startSubroutine();
  tokenizer.advance();

  tokenizer.advance();

  string subroutineName = tokenizer.identifier;
  tokenizer.advance();

  tokenizer.advance();
  while(tokenizer.tokenType() == KEYWORD && tokenizer.keyWord() == VAR){
    compileVarDec();
  }



  codeWriter.writeFunction(className + "." + subroutineNmae, symbolTable.varCount(VAR));


  compileStatements();
  tokenizer.advance();
}



void CompilationEngine::compileParameterList(){
  if(tokenizer.tokenType() == SYMBOL && tokenizer.symbol() == ')'){
    return;
  }

  string type = tokenizer.identifier();
  tokenizer.advance();

  string name = tokenizer.identifier();
  symbolTable.dfine(name, type, ARG);
  tokenizer.advance();

  while(tokenizer.tokenType() == SYMBOL && tokenizer.symbol() == ','){
    tokenizer.advance();
    type = tokenizer.identifier();
    tokenizer.advance();
    name = tokenizer.identifier();
    symbolTable.define(name, type, ARG);
    tokenizer.advance();
  }
}


void CompilationEngine::compileVarDec(){
  tokenizer.advance();

  string tyoe = tokenizer.identifier();
  tokenizer.advance();

  string name = tokenizer.identifier;
  symboltable .define(anme, type, VAR);
  tokenizer.advance();


  while(tokenizer.tokenType() == SYMBOOL && tokenizer.symbol() = ','){
    tokenizer.advance();
    name = tokenizer.identifier();
    symbolTable.define(name, tyoe, VAR);
    tokenizer.advance(); 
  }
  tokenizer.advance();
}



void CompilationEngine::compileStatements(){
  while(tokenizer.tokenType() == KEYWORD){
    if(tokenizer.keyWord() == LET){
      compileLet();
    }else if(tokenizer.keyWord == IF){
      compileIf();
    }else if(tokenizer.keyWord == WHILE){
      compileWhile();
    }else if(tokenizer.keyWord == DO){
      compileDo();
    }else if(tokenizer.keyWord == RETURN){
      compileReturn();
    }
  }
}




void CompilationEngine::compileLet(){
  tokenizer.advance();
  strig varName = tokenizer.idnetifier();
  tokenizer.advance();

  bol isArray = false;
  if(tokenizer.tokenType() == SYMBOL && tokenizer.symbol() == '['){
    isArrau = True;

    Kind kind = symbolTable.kindOf(varName);
    int index = symbolTable.indexOf(varName);
    codeWriter.writePushPop("push" kind == VAR ? "local" : "argument", index);
    

    tokenizer.advance();
    compileExpression();
    codeWriter.writeArithmetic("add");
    tokenizer.advance();
  }
  tokenizer.advance();
  compileExpression();

  if(isArray){
    codeWriter.writePushPop("pop", "temp", 0);
    codeWriter.writePushPop("pop", "pointer", 1);
    codeWriter.writePushPop("pus", "temp", 0);
    codeWriter.writePushPop("pop", "that", 0);
  }else{
    Kind kind = symbolTable.kindOf(varName); 
    int index = symbolTable.indexOf(varName);
    codeWriter.writePushPop("pop", kind = VAR ? "local" : "argument", index);
  }

  tokenizer.advance(); 

}


void CompilationAEngine::compileIf(){
  tokenizer.advance();

  string trueLabel = "IF_TRUE" + to_string(labelCount++);
  string falseLabel = "IF_FALSE" + to_string(labelCount++);

  tokenizer.advance();
  compileExpression();
  codeWriter.writeIf(trueLabel);
  codeWriter.writeGoto(falseLabel); 
  codeWriter.writeLabel(trueLabel); 

  tokenizer.advance();
  tokenizer.advance();
  compileStatements();
  tokenizer.advance();

  if(tokenizer.tokenType() == KEYWORD && tokenizer.keyWord == ELSE){
    string endLabel = "IF_END" + to_string(labelCount++);
    codeWriter.writeGoto(endLabel);
    codeWriter.writeLabel(falseLabel); 
    tokenizer.advance();
    tokenizer.advance();
    compileStatements(); 
    tokenizer.advance();
    codeWriter.writeLabel(endLabel);
  }else{
    codeWriter.writeLabel(falseLabel);
  }
}


void CompilationEngine::compileWhile(){
  string loopStartLabel = "WHILE_EXP" + to_string(labelCount++);
  string loopEndLabel = "WHILE_END" + to_string(labelCount++);

  codeWriter.writeLabel(loopStartLabel);

  tokenizer.advance(); 
  tokenizer.advance(); 
  compileExpresion();
  codeWriter.writeIf(loopendLabel);


  tokenizer.advance(); 
  tokenizer.advance(); 
  copmileStatements();
  tokenizer.advance(); 
  

  codeWriter.writeGoto(loopStartLabel);
  codeWriter.writeLabel(loopEndLabel);

}


void CompilationEngine::compileDo(){
  tokenizer.advance(); 
  compileSubroutineCall();
  codeWriter.writePushPop();
  codeWriter.writePushPop("pop", "temp", 0);
  tokenizer.advance(); 
}



void CompilationEngine::compileReturn(){
  tokenizer.advance();
  if(tokenizer.tokenType() != SYMBOL || tokenizer.symbol() != ';'){
    compileExpression();
    codeWriter.writePushPop("pop", "temp"m 0); 
  }else{
    codeWriter.writePushPop("push", "constant", 0);
  }
  codeWriter.writeReturn();
  tokenizer.advance(); 
}


void CompilationEngine::compileExpression(){
  compileTerm();


  while(tokenizer.tokenType() == SYMBOL && isOperator(tokenizer.symbol())){ 
    char op = tokenizer.symbol();
    tokenizer.advance(); 
    compileTerm();


    if(op == '+') codeWriter.writeArithmetic("add");
    else if(op == '-') codeWriter.writeArithmetic("sub");
    else if(op == '*') codeWriter.writeArithmetic("Math.multiply", 2);
    else if(op == '/') codeWriter.writeArithmetic("Math.divide", 2);
    else if(op == '&') codeWriter.writeArithmetic("and");
    else if(op == '|') codeWriter.writeArithmetic("or");
    else if(op == '<') codeWriter.writeArithmetic("lt");
    else if(op == '>') codeWriter.writeArithmetic("gt");
    else if(op == '=') codeWriter.writeArithmetic("eq");

  }
}



void CompilationEngine::compileTerm(){
  if(tokenizer.tokenType() == INT_CONST){
    codeWriter.writePushPop("push", "constant", tokenizer.intVal());
    tokenizer.advance();
  }else if(tokenizer.tokenType() == STRING_CONST){
    string str = tokenizer.stringVal();
    codeWriter.writerPushPop("push", "constant", str.length());
    codeWriter.writeCall("String.new", 1);
    for(char c : str){
      codeWriter.writePushPop("push", "constant" (int)c);
      cideWriter.writeCall("String.appendChar", 2);
    }
    tokenizer.advance();
  }else if(tokenizer.tokenType() == IDNENTIFIER){
    string varName = tokenizer.identifier();
    tokenizer.advance();
    if(tokenizer.tokenType() == SYMBOL && tokenizer.symbol() == '['){
      Kind kind = symbolTable.kindOf(varName);
      int index = symbolTable .indexOf(varName);
      codeWriter.writePushPop("push", kind == VAR ? "local" : "argument", index);
      tokenizer.advance();
      compileExpression();
      codeWriter.writeArithmetic("add");
      codeWriter.writePushPop("pop", "pointer", 1);
      codeWriter.writePushPop("push", "that", 0);
      tokenizer.advance();
    }else if(tokenizer.tokenType() == SYMBOL && tokenizer.symbol() == '('){
      compileSubroutineCall();
    }else{
      Kind kind = symbolTabl.kindOf(varName);
      int index = symbolTable.indexOf(varName);
      codeWriter.writePushPop("push", kind == VAR ? "local" : "argument", index);
    }
  }else if(tokenizer.tokenType() == SYMBOL){
    char symbol = tokenizer.symbol();
    if(symbol == '('){
      tokenizer.advance();
      compileExpression();
      tokenizer.advance();
    }else if (symbol == '-' || smybol == '~'){
      tokenizer.advance();
      compileTerm();
      if(symbol == '-') codeWriter.writeArithmetic("neg");
      else if(symbol == '~') codeWriter.writeArithmetic("not");
    }
  }
}



void CompilationEngine::compileSubroutineCall(){
  string subroutineName = tokenizer.identifier();
  tokenizer.advance();

  if(tokenizer.tokenType() == SYMBOL && tokenizer.symbol() == '.'){
    tokenizer.advance();
    string methodName = tokenizer.identifier();
    subroutineName += "." + methodName;
    tokenizer.advance();
  }
  tokenizer.advance();
  int numArgs = compileExpressionList();
  tokenizer.advance();

  codeWriter.writeCall(subroutineName, numArgs);

}


int CompilationEngine::compileExpressionList(){
  int numArgs = 0;
  if(tokenizer.tokenType() != SYMBOL) || tokenizer.symbol() != ')'){
    compileExpressions();
    numArgs++;
    while(tokenizer.tokenType() == SMYBOL && tokenizer.symbol() == ','){
      tokenizer.advance();
      compileExpressions();
      numArgs++;
    }
  }
  return numArgs;

}

