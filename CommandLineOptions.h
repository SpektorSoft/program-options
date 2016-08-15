#ifndef _COMMAND_LINE_OPTIONS_H__
#define _COMMAND_LINE_OPTIONS_H__

#include <string>
#include <boost/program_options.hpp>
namespace po = boost::program_options;

// ----------------------------------------------------------------------------
// Handle command line options
//
// Options:
//  [-h|--help]                     Show help menu
//  [-V|--version]                  Display version information
//  [-t|--time] ARG (double)        User-supplied run time (default = 100.0)
//  [-G|--gflag]                    G flag
//  [-R|--rflag]                    R flag
//  [-J|--jflag]                    J flag
//  [-f|--file] ARG (std::string)   Input file
//  [--value] ARG (int)             User value
// ----------------------------------------------------------------------------

class CommandLineOptions
{
public:
   enum statusReturn_e
   {
      OPTS_SUCCESS,
      OPTS_VERSION,
      OPTS_HELP,
      OPTS_FAILURE
   };

   CommandLineOptions();
   ~CommandLineOptions();
   statusReturn_e parse( int argc, char* argv[] );

   inline const std::string & getInputFile() const;
   inline double getUserTime(){ return myUserTime; };
   inline int getUserValue(){ return myUserValue; };
   inline bool getGFlag(){ return myGFlag; };
   inline bool getRFlag(){ return myRFlag; };
   inline bool getJFlag(){ return myJFlag; };

protected:
   void setup();
   bool validateFiles();

private:
   // Not implemented -- not for use
   CommandLineOptions( const CommandLineOptions &rhs );
   CommandLineOptions &operator=( const CommandLineOptions &rhs );

   po::options_description myOptions;
   std::string myInputFile;
   double myUserTime;
   int myUserValue;
   bool myGFlag;
   bool myRFlag;
   bool myJFlag;
};

inline
const std::string & CommandLineOptions::getInputFile() const
{
   static const std::string emptyString;
   return ( 0 < myInputFile.size() ) ? myInputFile : emptyString;
}

#endif // _COMMAND_LINE_OPTIONS_H__
