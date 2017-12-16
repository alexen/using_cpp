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
#include <fstream>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <boost/exception/diagnostic_information.hpp>
#include <stl_container_io.h>
#include <person.h>
#include <person_io.h>


class Redirector {
public:
     explicit Redirector( std::ostream& from )
          : ostr_( from )
     {}

     void to( std::ostream& to )
     {
          streambuf_ = ostr_.rdbuf( to.rdbuf() );
     }

     ~Redirector()
     {
          if( streambuf_ )
          {
               ostr_.rdbuf( streambuf_ );
          }
     }

private:
     std::ostream& ostr_;
     std::streambuf* streambuf_ = nullptr;
};


int main()
{
     try
     {
          std::cout << std::make_tuple( "Pi is", ':', 3.14 ) << "\n";
          std::cout << std::array< float, 4 >{ 1.2, 3.4, 2.1, 0.5 } << "\n";
     }
     catch( const std::exception& e )
     {
          std::cerr << "exception: " << boost::diagnostic_information( e ) << '\n';
          return 1;
     }

     return 0;
}
