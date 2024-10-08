#inlcude "compilation_engine.h"
#include <iostream>


CompilationEngine::CompilationEngine(JackTokenizer &tokenizer, const string& outputFileName) 
: tokenizer(tokenizer){
    outputGile.open(outputFileName);
}

void CompilationEngine::writeXML(const string& tag, const string& content){
  outputFile << "<" << tag << ">" << content << "</" << tag << ">" << endl;
}

void CompilationEngine::compile(){
  compileClass();
}

void CompilationEngine::compileClass(){
  tokenizer.advance()
  if(tokenizer.tokenType() == KEYWORD && tokenizer.keyWord() == CLASS){
    writeXML("keyword", "clas");
  }

  tokenizer.advance();
  if(tokenizer.tokenType() == IDENTIFIER){
    writeXML("identifier", tokenizer.identifier());
  }


  tokenizer.advance();
  if(tokenizer.tokeType() == SYMBOL && tokenizer.symbol() == '{'){
    writeXML("symbol", "{");
  }


  while(tokenizer.hasmoreTokens()  && tokenizr.tokenType() == KEYWORD &&
  (tokenizer.keyWord() == CONSTRUCTOR || tokenizer.keyWord() == FUNCTION || tokenizer.keyWord == METHOD)){
    comileSubroutine();
  }


  tokenizer.advance();
  if(tokenizer.tokenType() == SYMBOL tokenizer.symbol() == '}'){
    writeXML("symbol", "}");

  }


}
void CompilationEngine::compileClassVarDec(){
  writeXML("keyWord", tokenizer.keyWord() == STATIC ? "static" : "field");

  tokenizer.advance();
  if(tokenizer.tokenType() == KEYWORD || tokenizer.tokenType() == IDENTIFIER){
    writeXML("keyword", tokenizer.tokenType() == KEYWORD ? "int" : tokenizer.indentifier());
  }

  tokenizer.advance();
  while(tokenizr.tokenType() == SYMBOL && tokenizer.symbol() == ','){
    writeXML("symbol", ","):
    tokenizer.advance();
    if(tokenizer.tokenType() == IDENTIFIER){
      writeXML("identifier", tokenizer.identifier());
    }
    tokenizer.advance();
  }


  if(tokenizer.tokenType() == SYMBOL && tokenizer.symbol() == ';'){
    writeXML("symbol", ";");
  }
  
  tokenizer.advance();
}

void CompilationENgine::compileSubroutine(){
  write("keyword", tokenizer.keyWord() == CONSTRUCTOR ? "constructor" : 
  tokenizer.keyWord() == FUNCTION ? "function" : "method");

  tokenizer.advance();
  if(tokenizer.tokenType() == KEYWORD || tokenizer.tokenType() == IDENTIFIER){
    writeXML("keyWord", tokenizer.tokenType() == KEYWORD ? "void" : tokenizer.identifier();)
  }


  tokenizer.advance();
  if(tokenizer.tokenType() == IDENTIFIER){
    writeXML("identifier", tokenizer.identifier());
  }


  tokenizer.advance();
  if(tokenizer.tokenType() == SYMBOL && tokenizer.symbol() == '('){
    writeXML("symbol", "(");
    compileParameterList();
  }

  tokenizer.advance();
  if(tokenizer.tokenType() == SYMBOL && tokenizer.symbol() == ')'){
    writeXML("symbol", ")");
  }
}


void CompilationEngine::compileParameterList(){
  if(tokenizer.tokenType() != SYMBOL || tokenizer.symbol() != ')'){
    do{
      if(tokenizer.tokenType() == KEYWORD || tokenizer.tokenType() == INDETIFIER){
        writeXML("keyword", tokenizer.tokenType() == KEYWORD ? "int" : tokenizer.identifier());
      }

      tokenizer.advance();
      if(tokenizer.tokenType() == IDENTIFIER){
        wrtieXML("identifier", tokenizer.identifier());
      }

      tokenizer.advance();
    }while(tokenizer.tokenType() == SYMBOL && tokenizer.symbol() == ',');
  }
}


void CompilationEngine::compileStatements(){
  while(tokenizer.tokenType() == KEYWORD){
    if(tokenizer.keyWord() == LET){
      compileLet; 
    }else if(tokenizer.keyWord() == IF){
      compileIf();
    }else if(tokenizer.keyWord() == WHILE){
      compileWhile();
    }else if(tokenizer.keyWord() == DO){
      compileDo();
    }else if(tokenizer.keyWord() == RETURN){
      compileReturn();
    }
  }
}

