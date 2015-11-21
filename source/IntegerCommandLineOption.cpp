#include <IntegerCommandLineOption.h>
#include <cstdlib>

/** @brief Integer option constructor only a command line parser can call it
*   @param shortForm a character used to identify an option in a short form\n
*          i.g "-i"
*   @param longForm a string used to identify an option in a long form\n
*          i.g "--interval"
*   @param mandatoryOption a boolean value to set an option as mandatory
**/
IntegerCommandLineOption::IntegerCommandLineOption(char shortForm, const string& longForm, bool mandatoryOption)
: CommandLineOption(shortForm, longForm, CommandLineOption::INTEGER, mandatoryOption, true) {
}


/** @brief Integer option constructor only a command line parser can call it
*   @param longForm a string used to identify an option in a long form\n
*          i.g "--interval"
*   @param mandatoryOption a boolean value to set an option as mandatory
**/
IntegerCommandLineOption::IntegerCommandLineOption(const string& longForm, bool mandatoryOption)
: CommandLineOption('\0', longForm, CommandLineOption::INTEGER, mandatoryOption, true) {
}

/** @brief Floating point option destructor
**/
IntegerCommandLineOption::~IntegerCommandLineOption() {
}

/**
*  @return The option value as a integer value (64 bits integer)\n
*          i.g. "--tollerance=1000 or -i 1000"
**/
int64_t IntegerCommandLineOption::getValue() const {
char* endptr = NULL;

  return strtoll(this->argument.c_str(), &endptr, 0);
}


/** @brief Reimplemented from CommandLineOption::checkArgument\n
*          this method return true if the argument passed is a string representing a numeric integer value\n
*          i.g "--interval=1000" or -i 1000.
*   @param arg comman dline option argument
*   @return true if argument is a valid integer number
**/
bool IntegerCommandLineOption::checkArgument(const string& arg) const {
char* endptr = NULL;

   strtoll(arg.c_str(), &endptr, 0);
   return ('\0' == *endptr); 

}
