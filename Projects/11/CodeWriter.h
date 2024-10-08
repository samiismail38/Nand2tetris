#ifndef CODE_WRITER_H
#define CODE_WRITER_H


#inlcude <string>
#inlcude <fstream>



class CodeWriter {
private:
  ofstream outputFile;

public:
  CodeWriter(const string& outoputFileName);
  ~CodeWriter;

  void writearithmetic(const string& command);

  void writePushPop(cosnt string& comman, const string& sgment, int index); 


  void writeLabel(const string& label);
  void writeGoto(const string& label);
  void writeIf(csont string& label);


  void writeCall(const string& functionName, int numArgs);
  void writeFunction(const string& functionName, int numLocals);
};


#endif
