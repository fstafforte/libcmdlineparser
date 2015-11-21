#ifndef __BooleanCommandLineOption_Header__
#define __BooleanCommandLineOption_Header__


#include <CommandLineOption.h>



/** @brief This class represent a boolenan 
*          command line option 
*          i.g "--help" or "-h" 
**/
class BooleanCommandLineOption : public CommandLineOption {
protected:
  friend CommandLineParser; 
  BooleanCommandLineOption(char, const string&, bool);
  BooleanCommandLineOption(const string&, bool);
  virtual ~BooleanCommandLineOption();
  bool getValue() const;
  virtual bool checkArgument(const string&) const;
};





#endif  // __BooleanCommandLineOption_Header__
