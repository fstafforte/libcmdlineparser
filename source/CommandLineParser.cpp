#include  <CommandLineParser.h>
#include  <CommandLineExceptions.h>
#include  <algorithm>


/** @brief constructor
**/
CommandLineParser::CommandLineParser()
: options()
, parsedOptions()
, remainingArgs()  {

}
/** @brief CommandLineParser destructor.\n
*         It deallocate all instanciated resources (CommandLineOption)\n
**/
CommandLineParser::~CommandLineParser() {
CommandLineOptionArray::size_type i = 0;

  for (i = 0; i < this->options.size(); ++i) {
    delete this->options[i];
  }

  for (i = 0; i < this->parsedOptions.size(); ++i) {
    delete this->parsedOptions[i];
  }
}

/** @brief Add a long form only boolean option.\n
*          It throws a CommandLineOptionAlreadyExistsException exception\n
*          in case the option has been already added or another option is identified by\n
*          the same short or long option tag.\n
*
* @param longForm long form option tag
* @param mandatoryOption boolean flag used to add a manatory option
* @return a BooleanCommandLineOption class reference
**/ 
const BooleanCommandLineOption& CommandLineParser::addBooleanOption(const string& longForm, bool mandatoryOption) {
  return this->addBooleanOption(' ', longForm, mandatoryOption);
}

/** @brief Add a short and long form boolean option\n
*          It throws a CommandLineOptionAlreadyExistsException exception\n
*          in case the option has been already added or another option is identified by\n
*          the same short or long option tag.\n
*
* @param shortForm long form option tag
* @param longForm long form option tag
* @param mandatoryOption boolean flag used to add a manatory option
* @return a BooleanCommandLineOption class reference
**/ 
const BooleanCommandLineOption& CommandLineParser::addBooleanOption(char shortForm, const string& longForm, bool mandatoryOption) {
  this->checkOptionAlreadyExists(shortForm, longForm);
  BooleanCommandLineOption* option = new BooleanCommandLineOption(shortForm, longForm, mandatoryOption); 
  this->options.push_back(option);
  return *option;
}

/** @brief Add a long form only integer option\n
*          It throws a CommandLineOptionAlreadyExistsException exception\n
*          in case the option has been already added or another option is identified by\n
*          the same short or long option tag.\n
*
* @param longForm long form option tag
* @param mandatoryOption boolean flag used to add a manatory option
* @return a IntegerCommandLineOption class reference
**/ 
const IntegerCommandLineOption& CommandLineParser::addIntegerOption(const string& longForm, bool mandatoryOption) {
  return this->addIntegerOption(' ', longForm, mandatoryOption);
}

/** @brief Add a short and long form integer option\n
*          It throws a CommandLineOptionAlreadyExistsException exception\n
*          in case the option has been already added or another option is identified by\n
*          the same short or long option tag.\n
*
* @param shortForm long form option tag
* @param longForm long form option tag
* @param mandatoryOption boolean flag used to add a manatory option
* @return a IntegerCommandLineOption class reference
**/ 
const IntegerCommandLineOption& CommandLineParser::addIntegerOption(char shortForm, const string& longForm, bool mandatoryOption) {
  this->checkOptionAlreadyExists(shortForm, longForm);
  IntegerCommandLineOption* option = new IntegerCommandLineOption(shortForm, longForm, mandatoryOption);
  this->options.push_back(option);
  return *option;
}

/** @brief Add a long form only floating point option\n
*          It throws a CommandLineOptionAlreadyExistsException exception\n
*          in case the option has been already added or another option is identified by\n
*          the same short or long option tag.\n
* @param longForm long form option tag
* @param mandatoryOption boolean flag used to add a manatory option
* @return a FPointCommandLineOption class reference
**/ 
const FPointCommandLineOption& CommandLineParser::addFPointOption(const string& longForm, bool mandatoryOption) {
  return this->addFPointOption(' ', longForm, mandatoryOption);
}

/** @brief Add a short and long form floating point option\n
*          It throws a CommandLineOptionAlreadyExistsException exception\n
*          in case the option has been already added or another option is identified by\n
*          the same short or long option tag.\n
* @param shortForm long form option tag
* @param longForm long form option tag
* @param mandatoryOption boolean flag used to add a manatory option
* @return a FPointCommandLineOption class reference
**/ 
const FPointCommandLineOption& CommandLineParser::addFPointOption(char shortForm, const string& longForm, bool mandatoryOption) {
  this->checkOptionAlreadyExists(shortForm, longForm);
  FPointCommandLineOption* option = new FPointCommandLineOption(shortForm, longForm, mandatoryOption);
  this->options.push_back(option);
  return *option;
}

/** @brief Add a long form only string option\n
*          It throws a CommandLineOptionAlreadyExistsException exception\n
*          in case the option has been already added or another option is identified by\n
*          the same short or long option tag.\n
* @param longForm long form option tag
* @param mandatoryOption boolean flag used to add a manatory option
* @return a StringCommandLineOption class reference
**/ 
const StringCommandLineOption& CommandLineParser::addStringOption(const string& longForm, bool mandatoryOption) {
  return this->addStringOption(' ', longForm, mandatoryOption);
}

/** @brief Add a short and long form string option\n
*          It throws a CommandLineOptionAlreadyExistsException exception\n
*          in case the option has been already added or another option is identified by\n
*          the same short or long option tag.\n
* @param shortForm long form option tag
* @param longForm long form option tag
* @param mandatoryOption boolean flag used to add a manatory option
* @return a StringCommandLineOption class reference
**/
const StringCommandLineOption& CommandLineParser::addStringOption(char shortForm, const string& longForm, bool mandatoryOption) {
  this->checkOptionAlreadyExists(shortForm, longForm);
  StringCommandLineOption* option = new StringCommandLineOption(shortForm, longForm, mandatoryOption);
  this->options.push_back(option);
  return *option;
}

/** @brief It adds the classic boolean option to obtain the program version.\n
*          More over it adds a short help text printed out by printUsage method.
*          @see printUsage
* @return a BooleanCammandLineOption class reference
**/
const BooleanCommandLineOption& CommandLineParser::addVersionOption() {
  const BooleanCommandLineOption& option = this->addBooleanOption('v', "version", false);
  this->addHelp(option, "show program version");
  return option;
}

/** @brief It adds the classic boolean option to obtain the program help usage.\n
*          More over it adds a short help text printed out by printUsage method.
*          @see printUsage
* @return a BooleanCammandLineOption class reference
**/
const BooleanCommandLineOption& CommandLineParser::addHelpOption() {
  const BooleanCommandLineOption& option = this->addBooleanOption('h', "help", false);
  this->addHelp(option, "this help");
  return option; 
}

/** @brief It adds a short help text to a specific added command line option\n
*          that is printed out by printUsage method.\n
*          It throws an UnknownCommandLineOptionException in case of an unknown option\n
*          has been provided.
*
*          @see printUsage
* @param option a CammandLineOption class reference 
* @param helpText a short help text printed out by printUsage method. 
**/
void CommandLineParser::addHelp(const CommandLineOption& option, const string& helpText) {
  CommandLineOption* foundOption = this->findOption(option);
  if (NULL == foundOption) {
    throw UnknownCommandLineOptionException(option.getOptionFlags()); 
  }

  foundOption->setHelpText(helpText); 
}

/** @brief It prints out a command line option menu to a STL ostream class (cout by deafault)\n
*
* i.g usage: prgram [options]\n
*         options:
*             < -h,--help: this help >
* @param os output stream class reference
**/ 
void CommandLineParser::printUsage(ostream& os) {

  os << "usage: program [options]\n"; 
  os << "\toptions:\n";
  CommandLineOptionArray::size_type i = 0;
  CommandLineOptionArray::size_type size = this->options.size();
  for (i = 0; (i < size); ++i) {
    const CommandLineOption* option = this->options[i];
    os << "\t\t< " << option->getOptionFlags() << ": " << option->getHelpText() << " >\n"; 
  }
}

/** @brief getter method to obtain the boolean option value
* 
*  @param option a boolean option returned by one of the addBooleanOption methods
*  @return boolean option value
*  
**/
bool CommandLineParser::getOptionValue(const BooleanCommandLineOption& option) {
BooleanArray valuesArray;
bool retval = false;

  this->getOptionValues(option, valuesArray);
  if (valuesArray.size() > 0) {
    retval = valuesArray[0];
  }

  return retval;
}

/** @brief getter method to obtain the integer (64 bits long) option value
* 
*  @param option an integer option returned by one of the addIntegerOption methods
*  @return integer option value
*  
**/
int64_t CommandLineParser::getOptionValue(const IntegerCommandLineOption& option) {
IntegerArray valuesArray;
int64_t retval = 0;

  this->getOptionValues(option, valuesArray);
  if (valuesArray.size() > 0) {
    retval = valuesArray[0];
  }

  return retval;
}

/** @brief getter method to obtain the floating point (double) option value
* 
*  @param option an floating point option returned by one of the addFPointOption methods
*  @return floating point option value
*  
**/
double CommandLineParser::getOptionValue(const FPointCommandLineOption& option) {
FPointArray valuesArray;
double retval = 0.0f;

  this->getOptionValues(option, valuesArray);
  if (valuesArray.size() > 0) {
    retval = valuesArray[0];
  }

  return retval;
}

/** @brief getter method to obtain the string option value
* 
*  @param option a string option returned by one of the addStringOption methods
*  @return string option value
*  
**/
const string CommandLineParser::getOptionValue(const StringCommandLineOption& option) {
StringArray valuesArray;
string retval;

  this->getOptionValues(option, valuesArray);
  if (valuesArray.size() > 0) {
    retval = valuesArray[0];
  }

  return retval;
}

/** @brief getter method to obtain the boolean option values array
* 
*  @param option a boolean option returned by one of the addBooleanOption methods
*  @param valuesArray a reference to a booleans array where option values have to be stored
*  
**/
void CommandLineParser::getOptionValues(const BooleanCommandLineOption& option, BooleanArray& valuesArray) {
CommandLineOptionArray::size_type i = 0;

  for (i = 0; i < this->parsedOptions.size(); ++i) {
    CommandLineOption* parsedOption = this->parsedOptions[i];
    if ((CommandLineOption::BOOLEAN == parsedOption->getType()) && 
        (option.getOptionFlags() == parsedOption->getOptionFlags())) {
      valuesArray.push_back(reinterpret_cast<BooleanCommandLineOption*>(parsedOption)->getValue());
    }
  }
  
}

/** @brief getter method to obtain the integer (64 bits long) option values array
* 
*  @param option an integer option returned by one of the addIntegerOption methods
*  @param valuesArray a reference to an integers array where option values have to be stored
*  
**/
void CommandLineParser::getOptionValues(const IntegerCommandLineOption& option, IntegerArray& valuesArray) {
CommandLineOptionArray::size_type i = 0;

  for (i = 0; i < this->parsedOptions.size(); ++i) {
    CommandLineOption* parsedOption = this->parsedOptions[i];
    if ((CommandLineOption::INTEGER == parsedOption->getType()) && 
        (option.getOptionFlags() == parsedOption->getOptionFlags())) {
      valuesArray.push_back(reinterpret_cast<IntegerCommandLineOption*>(parsedOption)->getValue());
    }
  }
  
}

/** @brief getter method to obtain the floating point (double) option values array
* 
*  @param option an floating point option returned by one of the addFPointOption methods
*  @param valuesArray a reference to a floating points array where option values have to be stored
*  
**/
void CommandLineParser::getOptionValues(const FPointCommandLineOption& option, FPointArray& valuesArray) {
CommandLineOptionArray::size_type i = 0;

  for (i = 0; i < this->parsedOptions.size(); ++i) {
    CommandLineOption* parsedOption = this->parsedOptions[i];
    if ((CommandLineOption::FPOINT == parsedOption->getType()) && 
        (option.getOptionFlags() == parsedOption->getOptionFlags())) {
      valuesArray.push_back(reinterpret_cast<FPointCommandLineOption*>(parsedOption)->getValue());
    }
  }
  
}

/** @brief getter method to obtain the string option values array
* 
*  @param option a string option returned by one of the addStringOption methods
*  @param valuesArray a reference to a strings array where option values have to be stored
*  
**/
void CommandLineParser::getOptionValues(const StringCommandLineOption& option, StringArray& valuesArray) {
CommandLineOptionArray::size_type i = 0;

  for (i = 0; i < this->parsedOptions.size(); ++i) {
    CommandLineOption* parsedOption = this->parsedOptions[i];
    if ((CommandLineOption::STRING == parsedOption->getType()) && 
        (option.getOptionFlags() == parsedOption->getOptionFlags())) {
      valuesArray.push_back(reinterpret_cast<StringCommandLineOption*>(parsedOption)->getValue());
    }
  }
  
}

/** @brief a getter method to retrive all command line arguments not releative to an option 
* 
* @return an array of string containing the remaining comman line arguments
**/
const StringArray& CommandLineParser::getRemainingArgs() const {
  return this->remainingArgs;
}

/** @brief  parse process command line arguments\n
*           in case of errors the following exceptions are thrown
*           UnknownCommandLineOptionException
*           MissingMandatoryArgumentException
*           AmbigousCommandLineOptionException
* 
* @param argc arguments number in a process command line as passed to main function
* @param argv zero terminated string representing a process command line arguments as passed to main function
**/
void CommandLineParser::parse(int argc, char** argv) {
int i = 0;
StringArray args;
StringArray::size_type idx = 0;
StringArray::size_type size = 0;
CommandLineOption* option = NULL;

  for (i = 1; i < argc; ++i) {
    args.push_back(argv[i]);
  }

  size = args.size();
  for (idx = 0; idx < size; ++idx) {
    const string& arg = args[idx];
    if (arg[0] == '-') {
      if (arg[1] == '-') { // long option flag      
        string longOpt(arg.substr(2));
        string::size_type assignPos = longOpt.find("=");
        string optionArg;
        if (string::npos != assignPos) {
          optionArg=longOpt.substr(assignPos + 1);
          longOpt.erase(assignPos);
        }

        if (NULL == (option = this->findOptionByLongForm(longOpt))) {
          throw UnknownCommandLineOptionException(arg);
        }
        if (true == option->isArgumentMandatory()) {
          if (0 == optionArg.length()) {
            ++idx;
            if (idx == size) {
              throw MissingMandatoryArgumentException(option->getOptionFlags());
            }
            option->setArgument(args[idx]);
          } else {
            option->setArgument(optionArg);
          }
        } else if (0 != optionArg.length()) {
          option->setArgument(optionArg);
        } 
        this->parsedOptions.push_back(option->clone()); 
      } else { // short option flag
        if (arg.length() == 2) { // single option (i.g -o)
          if (NULL == (option = this->findOptionByShortForm(arg[1]))) {
            throw UnknownCommandLineOptionException(arg); 
          }
          if (true == option->isArgumentMandatory()) {
            ++idx;
            if (idx == size) {
              throw MissingMandatoryArgumentException(arg); 
            }
            option->setArgument(args[idx]);
          }
          this->parsedOptions.push_back(option->clone());
        } else { // more than one option flag
          string::size_type pos = 1;
          string::size_type arglen = arg.length();
          for (pos = 1; pos < arglen; ++pos) {

            if (NULL == (option = this->findOptionByShortForm(arg[pos]))) {
              throw UnknownCommandLineOptionException(string("-") + arg[pos]); 
            }

            if (CommandLineOption::BOOLEAN == option->getType()) {
              this->parsedOptions.push_back(option->clone());
            } else { // other option types must have a argument
              if (pos < (arglen - 1)) { // argument on the same command line argument arg (i.g -abgoofy)
                option->setArgument(arg.substr(pos + 1));
              } else { // argument is another command line argument (i.g. -ab goofy)
                ++idx;
                if (idx == size) {
                  throw MissingMandatoryArgumentException(string("-") + arg[pos]);
                }
              }
              this->parsedOptions.push_back(option->clone());
              pos = arglen;
            }
          }
        }
      }
    } else {
      this->remainingArgs.push_back(arg);
    }       
  }
}


/** @brief check if mandatory options have been found during\n
*          the process command line options parsing
*          if one of the mandatory option is missed a\n
*          MissingMandatoryOptionException is thrown
**/
void CommandLineParser::checkMandatoryOptions() {
StringArray::size_type idx = 0;
StringArray::size_type size = 0;

  // looking for mandatory options
  for (CommandLineOptionArray::size_type optIdx = 0; optIdx < this->options.size(); ++optIdx) {
    CommandLineOption* option = this->options[optIdx];
    if (true == option->isMandatoryOption()) {
      size = this->parsedOptions.size();
      for (idx = 0; idx < size; ++idx) {
        if (this->parsedOptions[idx]->getOptionFlags()  == option->getOptionFlags()) {
          break;
        }
      }

      if (idx >= size) {
        throw MissingMandatoryOptionException(option->getOptionFlags());
      }
    }
  }

}

/** @brief check if an option already exists between the added once
*          if it exists a CommandLineOptionAlreadyExistsException is thrown
* @param shortForm short form option tag
* @param longForm  long form option tag
**/
void CommandLineParser::checkOptionAlreadyExists(char shortForm, const string& longForm) {
CommandLineOptionArray::size_type i = 0;
CommandLineOptionArray::size_type size = this->options.size();
  
  for (i = 0; (i < size); ++i) {
    const CommandLineOption* option = this->options[i];
    if ((option->getShortForm() == shortForm) || (option->getLongForm() == longForm)) {
      throw CommandLineOptionAlreadyExistsException(option->getOptionFlags());
    }
  }
}


/** @brief find an option between the added once by its short form tag
* @param shortForm short form option tag
* @return CommandLineOption poiter or null if not found
**/
CommandLineOption* CommandLineParser::findOptionByShortForm(char shortForm) {
CommandLineOptionArray::size_type i = 0;
CommandLineOptionArray::size_type size = this->options.size();
CommandLineOption* retval = NULL;

  for (i = 0; (i < size); ++i) {
    CommandLineOption* option = this->options[i];
    if (option->getShortForm() == shortForm) {
      retval = option;
      break;
    }
  }

  retval = (i >= size) ? NULL : retval;

  return retval;
}

/** @brief find an option between the added once by its long form tag
* @param longForm short form option tag
* @return CommandLineOption poiter or null if not found
**/
CommandLineOption* CommandLineParser::findOptionByLongForm(const string& longForm) {
CommandLineOptionArray::size_type i = 0;
CommandLineOptionArray::size_type j = 0;
CommandLineOptionArray::size_type size = this->options.size();
CommandLineOption* retval = NULL;


  for (i = 0; (i < size); ++i) {
    CommandLineOption* option = this->options[i];
    const string& optionLongForm = option->getLongForm();
    
    if (optionLongForm == longForm) {
      retval = option;
      break;
    } else {
      string::size_type pos = optionLongForm.find(longForm);
      if (0 == pos) { // looking for ambiguity
        for (j = i + 1; j < size; ++j) {
          CommandLineOption* otherOption = this->options[j];
          if (0 == (pos = otherOption->getLongForm().find(longForm))) {
            throw AmbigousCommandLineOptionException(string("--") + longForm); 
          } 
        }
        retval = option; 
        break; // no ambiguity ... option found 
      }
    }
  }

  retval = (i >= size) ? NULL : retval;

  return retval;
}


/** @brief find an option between the added once.
* @param option a reference to a command line option to find 
* @return CommandLineOption poiter or null if not found
* @see addHelp method
**/
CommandLineOption* CommandLineParser::findOption(const CommandLineOption& option) {
CommandLineOptionArray::size_type i = 0;
CommandLineOptionArray::size_type size = this->options.size();
CommandLineOption* retval = NULL;
  
  for (i = 0; (i < size); ++i) {
    retval = this->options[i];
    if ((retval->getShortForm() == option.getShortForm()) || (retval->getLongForm() == option.getLongForm())) {
      break;
    }
  }

  retval = (i >= size) ? NULL : retval;

  return retval;
}
