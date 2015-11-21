#include <BooleanCommandLineOption.h>
#include <algorithm>

/** @brief Boolean option constructor only a command line parser can call it
*   @param shortForm a character used to identify an option in a short form\n
*          i.g "-h"
*   @param longForm a string used to identify an option in a long form\n
*          i.g "--help"
*   @param mandatoryOption a boolean value to set an option as mandatory
**/
BooleanCommandLineOption::BooleanCommandLineOption(char shortForm, const string& longForm, bool mandatoryOption)
: CommandLineOption(shortForm, longForm, CommandLineOption::BOOLEAN, mandatoryOption, false) {
  this->setArgument("true");
}


/** @brief Boolean option constructor only a command line parser can call it
*
*   @param longForm a string used to identify an option in a long form\n
*          i.g "--help"
*   @param mandatoryOption a boolean value to set an option as mandatory
**/
BooleanCommandLineOption::BooleanCommandLineOption(const string& longForm, bool mandatoryOption)
: CommandLineOption('\0', longForm, CommandLineOption::BOOLEAN, mandatoryOption, false) {
}

/** @brief Boolean option destructor
**/
BooleanCommandLineOption::~BooleanCommandLineOption() {
}

/**
*  @return The option value as a boolean value according to\n
*          the value of its argument (true by default)\n
*          if its argument is "true" (case insensitive) or != "true"\n
*          i.g. "--debug=False" returns the boolean value false\n
*               "--debug" returns true (default)\n
**/
bool BooleanCommandLineOption::getValue() const {
  string to_lower_arg;

  transform(this->argument.begin(), this->argument.end(), back_inserter(to_lower_arg), ::tolower);
  return (to_lower_arg == "true"); 
}

/** @brief Reimplemented from CommandLineOption::checkArgument\n
*          this method return true if the argument passed is a string (case insensitive)\n
*          whith the value of "true" or "false".
*   @param arg comman dline option argument
*   @return true if argument is a valid boolean string ("true" or "false", case insensitive) 
**/
bool BooleanCommandLineOption::checkArgument(const string& arg) const {
  string to_lower_arg;

  transform(arg.begin(), arg.end(), back_inserter(to_lower_arg), ::tolower);
  return ((to_lower_arg == "true") || (to_lower_arg == "false"));
}
