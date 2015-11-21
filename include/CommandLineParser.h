#ifndef __CommandLineParser_Header__
#define __CommandLineParser_Header__

#include <BooleanCommandLineOption.h>
#include <IntegerCommandLineOption.h>
#include <FPointCommandLineOption.h>
#include <StringCommandLineOption.h>
#include <iostream>
#include <inttypes.h>


typedef vector<bool> BooleanArray;
typedef vector<int64_t> IntegerArray;
typedef vector<double> FPointArray;
typedef vector<string> StringArray;
typedef vector<CommandLineOption*> CommandLineOptionArray;

/** @brief This class manages a process command line options.\n
 *        It provides methods to add options, facilities to add\n 
 *        classic options such as 'version' or 'help' and to parse\n
 *        a process command line, and get remaining arguments\n
 *        that are not related to an option\n
 *        More over provides methods to print out options usage\n
 *        and the possibility to check if mandatory options\n 
 *        has been provided in the command line.\n
 *        For each type of option a getter method is provided.\n
 *        Sometimes user need to provide an option more then one time\n
 *        in a process command line so there are getter methods that can be used\n
 *        to get an array of options.\n
 **/
class CommandLineParser {
public:
  CommandLineParser();
  virtual ~CommandLineParser();

  const BooleanCommandLineOption& addBooleanOption(const string&, bool);
  const BooleanCommandLineOption& addBooleanOption(char, const string&, bool);
  const IntegerCommandLineOption& addIntegerOption(const string&, bool);
  const IntegerCommandLineOption& addIntegerOption(char, const string&, bool);
  const FPointCommandLineOption& addFPointOption(const string&, bool);
  const FPointCommandLineOption& addFPointOption(char, const string&, bool);
  const StringCommandLineOption& addStringOption(const string&, bool);
  const StringCommandLineOption& addStringOption(char, const string&, bool);
  const BooleanCommandLineOption& addVersionOption();
  const BooleanCommandLineOption& addHelpOption();
  void  addHelp(const CommandLineOption&, const string&);

  void  printUsage(ostream& = cout);

  bool          getOptionValue(const BooleanCommandLineOption&);
  int64_t       getOptionValue(const IntegerCommandLineOption&);
  double        getOptionValue(const FPointCommandLineOption&);
  const string  getOptionValue(const StringCommandLineOption&);
  
  void getOptionValues(const BooleanCommandLineOption&, BooleanArray&);
  void getOptionValues(const IntegerCommandLineOption&, IntegerArray&);
  void getOptionValues(const FPointCommandLineOption&, FPointArray&);
  void getOptionValues(const StringCommandLineOption&, StringArray&);

  const StringArray& getRemainingArgs() const;

  void parse(int, char**);
  void  checkMandatoryOptions();
protected:
  void                checkOptionAlreadyExists(char, const string&);  // Throws a CommandLineOptionAlreadyExistsException
  CommandLineOption*  findOptionByShortForm(char);
  CommandLineOption*  findOptionByLongForm(const string&);
  CommandLineOption*  findOption(const CommandLineOption& option);

  CommandLineOptionArray options; 
  CommandLineOptionArray parsedOptions; 
  StringArray            remainingArgs;
};

#endif  // __CommandLineParser_Header__
