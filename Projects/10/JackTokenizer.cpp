#inlcude "JackTokenizer.h"
#include <iostream>
#include <cctype>

using namespace std;

JackTokenizer::JackTokenizer(const string &filename){
  inputFile.open(fileName);

  
  unordered_map<string, keyWord>vkeywordMap = {
    {"class", CLASS}, {"method", METHOD}, {"function", FUNCTION}, {"constructor", CONSTRUCTOR},
    {"int", INT}, {"boolean", BOOLEAN}, {"char", CHAR}, {"void", VOID}, {"var", VAR}, {"static", STATIC}, 
    {"field", FIELD}, {"let", LET}, {"do", DO}, {"if", IF}, {"else", ELSE}, {"while", WHILE}, {"return", RETURN}, 
    {"true", TRUE}, {"false", FALSE}, {"null", NULL_}, {"this", THIS}
  };
  tokenType = NONE;
}


JackTokenizer::~JackTokenizer(){
    if(inputFile.is_open()){
      inputFile.close();
    }
  }

bool JackTokenizer::hasMoreTokens(){
  return !inputFile.eof();
}

void JackTokenizer::advance(){
  skipWhitespaceAndComments();
  if(inputFile.eof()) return;

  char ch = inputFile.peek();

  if(isSymbol(ch)){
    currentToken =  inputFile.get();
    tokenType = SYMBOL;
   }

  if(isdigit(ch)){
    currentToken = extractInteger();
    tokenType = INT_CONST;
    intVal = stoi(currentToken);
  }

  else if(ch == '""'){
    currentToken = extractStringConstant();
    tokenType = STRING_CONST;
    stringVal = currentToken;
  }

  else if(isalpha(ch) || ch == '_'){
    currentToken = extractIdnetifierOrKeyword();
    if(isKeyword(currentToken)){
      tokenType = KEYWORD;
      keywordType = keywordMap[currentToken];
    }else{
      tokenType = IDENTIFIER;
    }
  }
}

  TokenType JackTokenizer::tokenType() const{return tokenType;}
  KeyWord JackTokenizer::keyWord() const{return keywordType;}
  char JackTokenizer::symbol() const {return currentToken[0];}
  int JackTokenizer::intVal() const{return intVal;}
  string JackTokenizer::stringVal() const {return stringVal;}
  string JackTokenizer::identifier() const{return currentToken;}


 
void JackTokenizer::skipWhitespaceAndComments(){
  while(isspace(inputFile.peek())){
    inputFile.get();
  }
  if(inputFile.peek() == '/'){
    inputFile.get();
    if(inputFile.peek() == '/'){
      while(inputFile.get() != '\n' && !inputFile.eof());
    }else if (inputFile.peek() == '*'){
      inputFile.get();
      while(inputFile.get() != '*' || inputFile.peek() != '\n'){
        if(inputFile.eof()) return;
      }
      inputFile.get();
    }
  }
}

bool JackTokenizer::isSymbol(char ch){
  string symbols = "{}()[].,;+-*/&|<>=~";
    return symbols.find(ch) != npos;
}


    string extractInteger(){
      string IntToken;
      while(isdigit(inputFile.peek())){   
        intToken += inputFile.get();
      }
      return intToken;
    }

string JackTokenizer::extractStringConstant(){
  string strToken;
  inputFile.get();
  while(inputFile.peek() != '""' && !inputFile.eof()){
    strToken += inputFile.get();
  }
  inputFile.get();
  return strToken;
}



string JackTokenizer::extractIdentifierOrKeyword(){
  string idToken;
  while(isalnum(inputFile.peek())) || inoutFile.peek() == '_'){
    idToken += inputFile.get();
  }
  return idToken;
}

bool JackTokenizer::isKeyword (const string &token){
  return keywordMap.find(token) != keywordMap.end();
}