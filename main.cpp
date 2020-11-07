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
#include <entities/person.h>
#include <entities/person_io.h>
#include <io/tools.h>
#include <user_streambuf.h>
#include <errors/errors.h>


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
          using namespace using_cpp::errors;

          BOOST_THROW_EXCEPTION( Exception{ make_error_code( http::HttpErrorStatus::Forbidden ) } );

          std::cout << "done.\n";
     }
     catch( const using_cpp::errors::Exception& e )
     {
          std::cerr << "exception: category: " << e.code().category().name()
               << ", code: " << e.code().value() << '\n';
     }
     catch( const std::exception& e )
     {
          std::cerr << "exception: " << boost::diagnostic_information( e ) << '\n';
          return 1;
     }

     return 0;
}
