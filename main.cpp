
#include "CommandLineOptions.h"

int main( int argc, char* argv[] )
{
   CommandLineOptions opts;
   std::string version = "00.00.001";

   CommandLineOptions::statusReturn_e temp = opts.parse( argc, argv );
   if( CommandLineOptions::OPTS_SUCCESS == temp )
   {
      // Input file
      std::cout << "Using: " << opts.getInputFile() << std::endl;

      if( opts.getGFlag() )
      {
         // Configure program behavior for G
         std::cout << "Using G" << std::endl;
      }

      if( opts.getRFlag() )
      {
         std::cout << "Using R" << std::endl;
      }

      if( opts.getJFlag() )
      {
         std::cout << "Using J" << std::endl;
      }

      std::cout << "User Time: " << opts.getUserTime() << std::endl;

      std::cout << "User Value: " << opts.getUserValue() << std::endl;
   }
   else if( CommandLineOptions::OPTS_VERSION == temp )
   {
      std::cout << "Version: " << version << std::endl;
   }
   else if( CommandLineOptions::OPTS_HELP == temp )
   {
      // we dont need to do anything here
   }
   else
   {
      std::cout << "ERROR - problem with options" << std::endl;
   }

   return 0;
}
