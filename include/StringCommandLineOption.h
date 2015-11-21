#ifndef __StringCommandLineOption_Header__
#define __StringCommandLineOption_Header__


#include <CommandLineOption.h>




class StringCommandLineOption : public CommandLineOption {
public:
  StringCommandLineOption(char, const string&, bool);
  StringCommandLineOption(const string&, bool);
  virtual ~StringCommandLineOption();
protected:
  friend CommandLineParser; 
  const string& getValue() const;
};





#endif  // __StringCommandLineOption_Header__
