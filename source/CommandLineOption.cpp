#include <CommandLineOption.h>
#include <CommandLineExceptions.h>



/** @brief Copy constructor
 * @param clo command line option to copy
**/
CommandLineOption::CommandLineOption(const CommandLineOption& clo)
: type(clo.type)
, mandatoryOption(clo.mandatoryOption)
, mandatoryArgument(clo.mandatoryArgument)
, shortForm(clo.shortForm)
, longForm(clo.longForm)
, optionFlags(clo.optionFlags)
, helpText(clo.helpText)
, argument(clo.argument) {

}

/** @brief short & long form constructor
 * @param sf short form tag
 * @param lf long form tag
 * @param t option type id
 * @param mo mandatory option flag
 * @param ma mandatory option flag
**/
CommandLineOption::CommandLineOption(char sf, string lf, OptionType t, bool mo, bool ma)
: type(t)
, mandatoryOption(mo)
, mandatoryArgument(ma)
, shortForm(sf)
, longForm(lf)
, optionFlags("")
, helpText("")
, argument("") {
  this->createOptionFlagsValue();
}

/** @brief long only form constructor
 * @param lf long form tag
 * @param t option type id
 * @param mo mandatory option flag
 * @param ma mandatory option flag
**/
CommandLineOption::CommandLineOption(string lf, OptionType t, bool mo, bool ma)
: type(t)
, mandatoryOption(mo)
, mandatoryArgument(ma)
, shortForm(' ')
, longForm(lf)
, optionFlags("")
, helpText("")
, argument("") {
  this->createOptionFlagsValue();
}

/** @brief Destructor
**/
CommandLineOption::~CommandLineOption() {
}

/** @brief clone method
 * @return a new copy of itself
**/
CommandLineOption* CommandLineOption::clone() const {
  return new CommandLineOption(*this);
} 

/** @return command line option type id
 * @see OptionType enumerator 
**/
CommandLineOption::OptionType CommandLineOption::getType() const {
  return this->type;
}

/** @return command line option short form tag
**/
char CommandLineOption::getShortForm() const {
  return this->shortForm;
}

/** @return command line option long form tag
**/
const string& CommandLineOption::getLongForm() const {
  return this->longForm;
}

/** @return command line option short/long form flags\n
 * i.g "-h,--help"
**/
const string& CommandLineOption::getOptionFlags() const {
  return this->optionFlags;
}

/** @brief create command line option short/long form flags\n
 * i.g "-h,--help"
**/
void CommandLineOption::createOptionFlagsValue() {

  if (' ' != this->getShortForm()) {
    ((this->optionFlags = "-") += this->getShortForm()) += ",";
  }

  this->optionFlags += "--";
  this->optionFlags += this->getLongForm();
}

/** @return help string that describes option meaning
**/
const string& CommandLineOption::getHelpText() const {
  return this->helpText;
}

/** @brief set help string that describes option meaning
 * @param newHelpText help description text
**/
void CommandLineOption::setHelpText(const string& newHelpText) {
  this->helpText = newHelpText;
}

/** @return true if an option is mandatory
**/
bool CommandLineOption::isMandatoryOption() const {
  return this->mandatoryOption;
}

/** @return true if an option requires an argument 
**/
bool CommandLineOption::isArgumentMandatory() const {
  return this->mandatoryArgument;
}

/** @return option argument 
**/
const string& CommandLineOption::getArgument() const {
  return this->argument;
}

/** @brief set option argument 
 * @param arg option argument value 
**/
void CommandLineOption::setArgument(const string& arg) {
  if (true == this->checkArgument(arg)) {
    this->argument = arg;
  } else {
    throw InvalidCommandLineOptionArgumentException(this->optionFlags + ", passed argument: " + arg);
  }
}

/** @brief virtual method that check option argument validity
**/
bool CommandLineOption::checkArgument(const string& arg) const{
  return true;
}
