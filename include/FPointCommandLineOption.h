#ifndef __FPointCommandLineOption_Header__
#define __FPointCommandLineOption_Header__


#include <CommandLineOption.h>




/** @brief This class represent a floating point command line option.\n
*          An argument its mandatory i.g "--tollerance 123.45 ot -t 123.45".
**/
class FPointCommandLineOption : public CommandLineOption {
public:
  FPointCommandLineOption(char, const string&, bool);
  FPointCommandLineOption(const string&, bool);
  virtual ~FPointCommandLineOption();
protected:
  friend CommandLineParser; 
  double getValue() const;
  virtual bool checkArgument(const string&) const;
};





#endif  // __FPointCommandLineOption_Header__
