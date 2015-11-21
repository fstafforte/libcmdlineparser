#include <FPointCommandLineOption.h>
#include <cstdlib>


/** @brief Floating point option constructor only a command line parser can call it
*   @param shortForm a character used to identify an option in a short form\n
*          i.g "-t"
*   @param longForm a string used to identify an option in a long form\n
*          i.g "--tollerance"
*   @param mandatoryOption a boolean value to set an option as mandatory
**/
FPointCommandLineOption::FPointCommandLineOption(char shortForm, const string& longForm, bool mandatoryOption)
: CommandLineOption(shortForm, longForm, CommandLineOption::FPOINT, mandatoryOption, true) {
}


/** @brief Floating point option constructor only a command line parser can call it
*
*   @param longForm a string used to identify an option in a long form\n
*          i.g "--tollerance"
*   @param mandatoryOption a boolean value to set an option as mandatory
**/
FPointCommandLineOption::FPointCommandLineOption(const string& longForm, bool mandatoryOption)
: CommandLineOption('\0', longForm, CommandLineOption::FPOINT, mandatoryOption, true) {
}

/** @brief Floating point option destructor
**/
FPointCommandLineOption::~FPointCommandLineOption() {
}


/**
*  @return The option value as a floating point value (double)\n
*          i.g. "--tollerance=123.45 or -t 123.45"
**/
double FPointCommandLineOption::getValue() const {
char* endptr = NULL;

  return strtod(this->argument.c_str(), &endptr);

}


/** @brief Reimplemented from CommandLineOption::checkArgument\n
*          this method return true if the argument passed is a string representing a numeric value\n
*          i.g "--tollerance=123.45" or -t 123.45. Intger value are ammitted "--tollerance 1000"
*   @param arg comman dline option argument
*   @return true if argument is a valid floating point number
**/
bool FPointCommandLineOption::checkArgument(const string& arg) const {
char* endptr = NULL;

  strtod(arg.c_str(), &endptr);
  return ('\0' == *endptr);
}

