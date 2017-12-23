///
/// main.cpp
///
/// Created on: Oct 11, 2017
///     Author: alexen
///

#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <tuple>
#include <vector>
#include <locale>
#include <streambuf>
#include <fstream>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <system_error>
#include <boost/utility/string_ref.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <stl_container_io.h>
#include <person.h>
#include <person_io.h>
#include <user_streambuf.h>


class FileDescriptorOstream : public std::ostream {
public:
     explicit FileDescriptorOstream( int fd )
          : std::ostream{ 0 }
          , fdstreambuf_{ fd }
     {
          rdbuf( &fdstreambuf_ );
     }

protected:
     FdStreambuf fdstreambuf_;
};


int main()
{
     try
     {
          FILE* fptr = fopen( "/tmp/output.txt", "w" );
          if( !fptr )
          {
               BOOST_THROW_EXCEPTION( std::system_error( errno, std::system_category() ) );
          }
          std::unique_ptr< FILE, decltype( &fclose ) > file{ fptr, fclose };
          FileDescriptorOstream ostr{ 1 };
          ostr << '@' << "\n"
               << std::make_tuple( 3.14, "hello", '1') << "\n"
               << 1 << '\n'
               << 2  << '\n'
               << 2.18 << '\n';
     }
     catch( const std::exception& e )
     {
          std::cerr << "exception: " << boost::diagnostic_information( e ) << '\n';
          return 1;
     }

     return 0;
}
