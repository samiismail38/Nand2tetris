#ifndef JACK_TOKENIZER_H
#define JACK_TOKENIZER_H


#include <string>
#include <fstream>
#include <unordered_map>

using namespace std;



enum TokenType{
  KEYWORD,
  SYMBOL,
  INDENTIFIER,
  INT_CONST, 
  STRING_CONST,
  NONE
};


enum KeyWord{
  CLASS, METHOD, FUNCTION, CONSTRUCTOR, INT, BOOLEAN, CHAR, 
  VOID, VAR, STATIC, FIELD, LET, DO, IF, ELSE, WHILE, RETURN, 
  TRUE, FALSE, NULL_M THIS
};



class JackTokenizer{
private:
  ifstreasm inputFile;
  string currentToken;
  TokenType tokentype;
  KeyWord keywordType;
  int intVal;
  string strinVal;

  unordered_map<string, Keyword> keywordMap;

  void skipWhitesåaceAndComments();
  bool isSymbol(char ch);
  string extractInteger();
  string extractStringConstant(); 
  string extractIdentifierOrKeyword();
  bool isKeyword(const string &token);

public:
  JackTokenizer(const string &fileName);
  ~JackTokenizer();

  bool hasMoreTokens();
  void advance();

  TokenType tokenType() const;
  KeyWord keyWord() const;
  char symbol() const;
  int intVal() const;
  string stringVal() const;
  string indetifier() const;

};

#endif