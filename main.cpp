///
/// main.cpp
///
/// Created on: Oct 11, 2017
///     Author: alexen
///

#include <map>
#include <set>
#include <tuple>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <boost/exception/diagnostic_information.hpp>
#include <stl_container_io.h>


class Person {
public:
     Person( const std::string& lastName, const std::string& firstName )
          : lastName_{ lastName }
          , firstName_{ firstName }
     {
          std::cout << __PRETTY_FUNCTION__ << "\n";
     }

     Person( const Person& o )
          : lastName_{ o.lastName_ }
          , firstName_{ o.firstName_ }
     {
          std::cout << __PRETTY_FUNCTION__ << "\n";
     }

     Person( Person&& o )
          : lastName_{ std::move( o.lastName_ ) }
          , firstName_{ std::move( o.firstName_ ) }
     {
          std::cout << __PRETTY_FUNCTION__ << "\n";
     }

     const std::string& lastName() const
     {
          return lastName_;
     }

     const std::string& firstName() const
     {
          return firstName_;
     }

private:
     const std::string lastName_;
     const std::string firstName_;
};


std::ostream& operator<<( std::ostream& ostr, const Person& p )
{
     ostr << "Person("
          << ostream_tools::quote( p.lastName() )
          << ", "
          << ostream_tools::quote( p.firstName() )
          << ")";
     return ostr;
}


int main()
{
     try
     {
          std::map< int, const char* > m;

          m.emplace( 0,  "zero" );
          m.emplace( 1,   "one" );
          m.emplace( 2,   "two" );
          m.emplace( 3, "three" );
          m.emplace( 4,  "four" );
          m.emplace( 5,  "five" );
          m.emplace( 6,   "six" );
          m.emplace( 7, "seven" );
          m.emplace( 8, "eight" );
          m.emplace( 9,  "nine" );

          std::cout << m << "\n";

          std::map< int, Person > m2;

          m2.emplace( std::piecewise_construct, std::make_tuple( 1 ), std::make_tuple( "Иванов", "Валерий" ) );
          m2.emplace( std::piecewise_construct, std::make_tuple( 2 ), std::make_tuple( "Петров", "Максим" ) );
          m2.emplace( std::piecewise_construct, std::make_tuple( 3 ), std::make_tuple( "Сидоров", "Олег" ) );

          std::cout << m2 << "\n";
     }
     catch( const std::exception& e )
     {
          std::cerr << "exception: " << boost::diagnostic_information( e ) << '\n';
          return 1;
     }

     return 0;
}
