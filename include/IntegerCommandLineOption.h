#ifndef __IntegerCommandLineOption_Header__
#define __IntegerCommandLineOption_Header__


#include <CommandLineOption.h>
#include <inttypes.h>

class CommandLineParser;

class IntegerCommandLineOption : public CommandLineOption {
public:
  IntegerCommandLineOption(char, const string&, bool);
  IntegerCommandLineOption(const string&, bool);
  virtual ~IntegerCommandLineOption();
protected:  
  friend CommandLineParser; 
  int64_t getValue() const;
  virtual bool checkArgument(const string&) const;
};





#endif  // __IntegerCommandLineOption_Header__
