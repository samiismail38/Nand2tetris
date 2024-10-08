#include "SymbolTable.h"


SymbolTable::SymbolTable(){
  classSymbols.clear();
  subroutienSymbols.clear();
}


void SymbolTable::startSubroutine(){
  subroutineSymbols.clear();
  argIndex = 0;
  varIndex = 0;
}



void SymbolTable::define(const string& name, const string& type, Kind kind){
  if(king == STATIC){
    classSymbols[name] = {type, staticIndex++};
  }else if(kind == FIELD){
    classSymbols[name] = {type, fieldIndex++};
  }else if(kind == ARG){
    classSymbols[name] = {type, argIndex++};
  }else if(kind == VAR){
    classSymbols[name] = {type, varIndex++};
  }
}


int SymbolTable::varCount(Kind kind) const{
  if(kind == STATIC){
    return staticIndex;
  }else if (kind == FIELD){ 
    return fieldIndex;
  }else if (kind == ARG){ 
    return argIndex;
  }else if (kind == VAR){ 
    return varIndex;
  }
  return 0;
}


Kind SymbolTable::kindOf(const string& name) const {
  if(classSymbols.find(name) != classSymbol.end()){
    if(classSymbols.at(name).second == staticIndex){
      return STATIC;
    }
    return FIELD;
  }
  if(subroutineSymbols.find(name)!=subroutineSymbols.end()){
    if(subroutineSymbols.at(name).second == argIndex){
      return ARG;
    }
    return VAR;
  }
  return VAR; 
}



string SymbolTable::typeOf(const string& name)const{
  if(classSymbols.find(name) != classSymbols.end()){
    return classSymbols.at(name).first;
  }

  return subroutineSymbols.at(name).first; 
}


int SymbolTable::indexOf(const string& name) const{
  if(classSymbols.find(name) != classSymbols.end()){
    return classSymbols.at(name).second;
  }
  return subroutineSymbols.at(name).second;
}