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
          const std::string input =
               "My Bonny is over the ocean,\n"
               "My Bonny is over the sea,\n"
               "My Bonny is over the ocean,\n"
               "So bring back my Bonny to me...";

          InputBuffer ibuf{ input.data(), input.size() };
          std::istream istr{ &ibuf };

          Buffer buffer;
          BufferStream obuf{ buffer };
          std::ostream ostr{ &obuf };

          istr >> ostr.rdbuf();

          std::cout
               << "result: "
               << boost::string_ref(
                    buffer.data(),
                    buffer.size()
                    )
               << "\n";

          std::cout << "done.\n";
     }
     catch( const std::exception& e )
     {
          std::cerr << "exception: " << boost::diagnostic_information( e ) << '\n';
          return 1;
     }

     return 0;
}
