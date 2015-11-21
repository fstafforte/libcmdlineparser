/**
 * @example this is an example of how to use command line option library
 *          using all types of option managed by the CommandLineParser class
 * 
**/
#include <iostream>
#include <iomanip>
#include <CommandLineParser.h>
#include <CommandLineExceptions.h>




int main(int argc, char** argv) {
int retval = 0;
CommandLineParser parser;

  try { 
    const BooleanCommandLineOption& helpOption = parser.addHelpOption();
    const BooleanCommandLineOption& versionOption = parser.addVersionOption();
                                                                                 // false = not mandatory option
    const BooleanCommandLineOption& debugOption = parser.addBooleanOption('d', "debug", false);
    const BooleanCommandLineOption& verboseOption = parser.addBooleanOption("verbose", false);
    const IntegerCommandLineOption& intervalOption = parser.addIntegerOption('i', "interval", true); 
    const FPointCommandLineOption& tolleranceOption = parser.addFPointOption('t', "tollerance", false); 
    const StringCommandLineOption& configFileOption = parser.addStringOption('c', "config-file", true); 

    parser.addHelp(debugOption, "print debug info");
    parser.addHelp(verboseOption, "print debug info");
    parser.addHelp(intervalOption, "polling interval");
    parser.addHelp(tolleranceOption, "speed tollerance");
    parser.addHelp(configFileOption, "configuration file path");

    parser.parse(argc, argv);


    const StringArray& remainingArgs = parser.getRemainingArgs();

    for (StringArray::size_type i = 0; i < remainingArgs.size(); ++i) {
      if (0 == i) {
        cout << "remaining arguments:\n";
      }
      cout << (i + 1) << ") " << remainingArgs[i] << "\n";
    }

    bool helpOptionValue = parser.getOptionValue(helpOption);
    if (false == helpOptionValue) {
      parser.checkMandatoryOptions();

      bool versionOptionValue = parser.getOptionValue(versionOption);

      if (true == versionOptionValue) {
        cout << "ver. 1.0.1\n";
      }
    
      bool debugOptionValue = parser.getOptionValue(debugOption);

      bool verboseOptionValue = parser.getOptionValue(verboseOption);

      int64_t intervalOptionValue = parser.getOptionValue(intervalOption);

      double tolleranceOptionValue = parser.getOptionValue(tolleranceOption);

      const string& configFileOptionValue = parser.getOptionValue(configFileOption);

      cout << boolalpha;
      cout << "debugOptionValue........: " << debugOptionValue << "\n";
      cout << "verboseOptionValue......: " << verboseOptionValue << "\n";
      cout << "intervalOptionValue.....: " << intervalOptionValue << "\n";
      cout << "tolleranceOptionValue...: " << tolleranceOptionValue << "\n";
      cout << "configFileOptionValue...: " << configFileOptionValue << "\n";
       

    } else {
      parser.printUsage();
    }
  } catch (const runtime_error ex) {
    cerr << ex.what() << "\n";
    parser.printUsage();
  }


  return retval;
}
