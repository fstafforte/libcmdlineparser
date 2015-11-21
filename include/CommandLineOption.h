#ifndef __CommandLineOption_Header__
#define __CommandLineOption_Header__


#include <string>
#include <vector>

using namespace std;

class CommandLineParser;


/** @brief Base class for all command line option types
*
**/
class CommandLineOption {
public:

  /** @brief this enumeration represent command line option type
  **/
  enum OptionType {
    /*! boolean option id */
    BOOLEAN,  
    /*! integer option id */
    INTEGER,
    /*! floating point option id */  
    FPOINT,
    /*! string option id */
    STRING   
  };

protected:

  friend CommandLineParser;

  CommandLineOption(const CommandLineOption&);
  CommandLineOption(char, string, OptionType, bool, bool);
  CommandLineOption(string, OptionType, bool, bool);

public:

  virtual ~CommandLineOption();

  virtual CommandLineOption* clone() const;
  OptionType getType() const; 
  
  char getShortForm() const;
  const string& getLongForm() const;
  const string& getOptionFlags() const;
  
  const string& getHelpText() const;

  bool          isMandatoryOption() const;
  bool          isArgumentMandatory() const;
  const string& getArgument() const;

protected:
  void setHelpText(const string&);
  void setArgument(const string&);
  virtual bool checkArgument(const string&) const;

  void  createOptionFlagsValue();
  /*! option type id */
  OptionType  type;             
  /*! mandatory option flag */
  bool    mandatoryOption;      
  /*! mandatory argument flag */
  bool    mandatoryArgument;    
  /*! short form option tag */
  char    shortForm;            
  /*! long form option tag */
  string  longForm;             
  /*! option flags as string */
  string  optionFlags;          
  /*! help string that describes option meaning */ 
  string  helpText;             
  /*! argument value as string in the command line */
  string  argument;             
};


#endif  // __CommandLineOption_Header__
