/*
*  Compile:                                                                                                                                                
* g++ -std=c++17 -Wall main.cpp -o main -lcurl -lcurlpp 
*
* 
* ./curl_web_crawler example.com string
*
  
*/

#include <iostream>
#include <chrono>
#include <string>

#include <cstdlib>
#include <fstream>
#include <sstream>


#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

          

//main 
int main(int argc, char *argv[])
{
  if(argc != 3) {
    std::cerr << argv[0] << ": Wrong number of arguments" << std::endl 
	      << argv[0] << ": Usage: " << " url " << "string" << std::endl;
	     
    return EXIT_FAILURE;
  }
  
  
  // Url ex. google.com  
  char *url = argv[1];
  
  // String to search for
  std::string search_str = argv[2];
  
    // Diagnostic file name
  std::string file;
  // Port
  long port {80};
  
  //File out stream
  std::ofstream fileout {output.txt};
  
  // Select port;
  std::cout << ": Use port number: " << "\t" << std::endl;
  std::cin >> port;
  
  std::cout << ": Write to file: " << "\t" << std::endl;
  std::cin >> file;

  
  // Open input file  
  fileout.open(file);

 
  
  try {
    curlpp::Cleanup cleaner;
    curlpp::Easy request;

    // String to search for
    std::ostringstream response_data;
   
    // Setting the URL to retrive.
    request.setOpt(new curlpp::options::Url(url));
    
    // Verbose - set true for command line verbose from curlpp
    request.setOpt(new curlpp::options::Verbose(true));
    
    // Follow location
    request.setOpt(curlpp::options::FollowLocation(true));
    
    // User agent
    request.setOpt(curlpp::options::UserAgent("Mozilla/5.0 (Windows NT 6.1; WOW64; rv:54.0) Gecko/20100101 Firefox/54.0"));

    // Port option
    request.setOpt(new curlpp::options::Port(port));
   
    // Write stream
    request.setOpt(curlpp::options::WriteStream(&response_data));
    
    // Do the dew
    request.perform();
       


	


  // Output  
    fileout << request;

  // search for the string in the response
    if (response_data.str().find(search_str) != std::string::npos) 
    {
        std::cout << "Found string '" << search_str << "' in " << url << std::endl;
    }
    
    else 
    {
    std::cout << "Did not find string '" << search_str << "' in " << url << std::endl;
    }

  // Close file
    fileout.close();


    return EXIT_SUCCESS;
 
}
  // Curlpp Error Handling 
  catch ( curlpp::LogicError & e ) {
    std::cout << e.what() << std::endl;
  }
  
catch ( curlpp::RuntimeError & e ) {
    std::cout << e.what() << std::endl;
  }

  return EXIT_FAILURE;
}




