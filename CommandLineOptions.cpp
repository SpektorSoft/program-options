#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/algorithm/string/trim.hpp>
namespace fs = boost::filesystem;

#include "CommandLineOptions.h"

CommandLineOptions::CommandLineOptions():
      myOptions(""),
      myInputFile(""),
      myUserTime( -99999999.99999 ),
      myUserValue( 0xffffffff ),
      myGFlag( false ),
      myRFlag( false ),
      myJFlag( false )
{
   setup();
}

CommandLineOptions::~CommandLineOptions()
{

}

void CommandLineOptions::setup()
{
   po::options_description options( "Program Options" );
   options.add_options()
         ( "help,h", "Display help menu." )
         ( "version,V", "Display program version number" )
         ( "time,t", po::value<double>( &myUserTime )->default_value( 100.0 ), "User-specified time" )
         ( "file,f", po::value< std::string >( &myInputFile ), "User-specified input file" )
         ( "value", po::value< int >( &myUserValue )->default_value( 43 ), "User-specified value" )
         ( "gflag,G", po::bool_switch( &myGFlag )->default_value( false ), "Toggle G-flag" )
         ( "rflag,R", po::bool_switch( &myRFlag )->default_value( false ), "Toggle R-flag" )
         ( "jflag,J", po::bool_switch( &myJFlag )->default_value( false ), "Toggle J-flag" );

   myOptions.add( options );
}

CommandLineOptions::statusReturn_e CommandLineOptions::parse( int argc, char* argv[] )
{
   statusReturn_e ret = OPTS_SUCCESS;

   po::variables_map varMap;
   char filename[5000];

   try
   {
      po::store( po::parse_command_line( argc, argv, myOptions ), varMap );
      po::notify( varMap );

      // Help option
      if( varMap.count( "help" ) )
      {
         std::cout << myOptions << std::endl;
         return OPTS_HELP;
      }

      // Version info
      if( varMap.count( "version" ) )
      {
         return OPTS_VERSION;
      }

      // Enforce an input file argument every time
      if( !( 0 < varMap.count( "file" ) ) )
      {
         std::cout << "ERROR - Input file must be specified!!!" << std::endl;
         std::cout << myOptions << std::endl;
         return OPTS_FAILURE;
      }
      else
      {
         // Strip whitespaces from front/back of filename string
         boost::algorithm::trim( myInputFile );

         // resolve the filename to be fully-qualified
         realpath( myInputFile.c_str(), filename );
         myInputFile = filename;

         ret = validateFiles() ? OPTS_SUCCESS : OPTS_FAILURE;
      }

      // We can check if a value is defaulted
      if( !varMap[ "value" ].defaulted() )
      {
         std::cout << "WARNING - Default value for User-Value overwritten to " << myUserValue << std::endl;
      }
   }
   catch( std::exception &e )
   {
      std::cout << "ERROR - parsing error: " << e.what() << std::endl;
      ret = OPTS_FAILURE;
   }
   catch( ... )
   {
      std::cout << "ERROR - parsing error (unknown type)." << std::endl;
      ret = OPTS_FAILURE;
   }

   return ret;
}

bool CommandLineOptions::validateFiles()
{
   if( !boost::filesystem::is_regular_file( myInputFile ) )
   {
      std::cout << "ERROR - Input file provided does not exist! [" << myInputFile << "]" << std::endl;
      return false;
   }
   return true;
}
