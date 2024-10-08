#ifndef SMYBOL_TABLE_H
#define SYMVOL_TABLE_H

#inlcude <string>
#inlclude <unordered_map>

using namespace std;


enum Kind { STATIC, FIELD, ARG, VAR};



class SymbolTable {
private:
  unordered_map<string, pair<string, int>> classSymbols;
  unordered_map<string, pair<string, int>> subroutineSymbols;


  int staticIndex = 0;
  int fieldIndex = 0;
  int argIndex = 0; 
  int varIndex = 0;

public: 
  SymbolTable();
  void startSubroutine();
  void define(const string& name, const string& type, Kind kind);
  int varCount(Kind kind) const;
  string typeOf(const string& name) const;
  int indexOf(const string& name) const;
};

#endif
