///
/// main.cpp
///
/// Created on: Oct 11, 2017
///     Author: alexen
///
///iGotfry был здесь

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
#include <user_streambuf.h>
#include <errors/errors.h>
#include <io/ostream.h>


namespace using_cpp {


class FileDescriptorOstream : public std::ostream {
public:
     explicit FileDescriptorOstream( int fd )
          : std::ostream{ 0 }
          , fdstreambuf_{ fd }
     {
          rdbuf( &fdstreambuf_ );
     }

protected:
     custom_streambuf::FdStreambuf fdstreambuf_;
};


} // namespace using_cpp


int main()
{
     try
     {
     }
     catch( const using_cpp::errors::Exception& e )
     {
          if( e.code().category() == using_cpp::errors::network::category() )
          {
               std::cerr << "exception: rethrow as low-level network error, code: "
                    << e.code().value() << '\n';
          }
          else if( e.code().category() == using_cpp::errors::http::category() )
          {
               std::cerr << "exception: rethrow as http error, code: " << e.code().value() << '\n';
          }
          std::cerr << "exception: " << boost::diagnostic_information( e ) << '\n';
     }
     catch( const std::exception& e )
     {
          std::cerr << "exception: " << boost::diagnostic_information( e ) << '\n';
          return 1;
     }

     return 0;
}
