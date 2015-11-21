#include <StringCommandLineOption.h>


/** @brief String option constructor only a command line parser can call it
*   @param shortForm a character used to identify an option in a short form\n
*          i.g "-c"
*   @param longForm a string used to identify an option in a long form\n
*          i.g "--config-file"
*   @param mandatoryOption a boolean value to set an option as mandatory
**/
StringCommandLineOption::StringCommandLineOption(char shortForm, const string& longForm, bool mandatoryOption)
: CommandLineOption(shortForm, longForm, CommandLineOption::STRING, mandatoryOption, true) {
}


/** @brief String option constructor only a command line parser can call it
*   @param longForm a string used to identify an option in a long form\n
*          i.g "--config-file"
*   @param mandatoryOption a boolean value to set an option as mandatory
**/
StringCommandLineOption::StringCommandLineOption(const string& longForm, bool mandatoryOption)
: CommandLineOption('\0', longForm, CommandLineOption::STRING, mandatoryOption, true) {
}

/** @brief Floating point option destructor
**/
StringCommandLineOption::~StringCommandLineOption() {
}

/**
*  @return The option value as a string value as passed in the command line\n
*          i.g. "--config-file=foo.cfg or -c foo.cfg"
**/
const string& StringCommandLineOption::getValue() const {
  return this->argument;
}
