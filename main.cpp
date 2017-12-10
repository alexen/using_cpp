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
#include <functional>
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


bool operator==( const Person& p1, const Person& p2 )
{
     return p1.lastName() == p2.lastName()
          && p1.firstName() == p2.firstName();
}


template< typename T >
std::size_t hash( const T& v )
{
     return std::hash< T >{}( v );
}


struct PersonHasher {
     std::size_t operator()( const Person& p ) const noexcept
     {
          return hash( p.lastName() ) ^ hash( p.firstName() );
     }
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
          std::unordered_multiset< std::string > uset;

          uset.emplace( "My" );
          uset.emplace( "Bonny" );
          uset.emplace( "is" );
          uset.emplace( "over" );
          uset.emplace( "the" );
          uset.emplace( "ocean" );
          uset.emplace( "My" );
          uset.emplace( "Bonny" );
          uset.emplace( "is" );
          uset.emplace( "over" );
          uset.emplace( "the" );
          uset.emplace( "sea" );
          uset.emplace( "Quick" );
          uset.emplace( "brown" );
          uset.emplace( "fox" );
          uset.emplace( "jump" );
          uset.emplace( "over" );
          uset.emplace( "sleeping" );
          uset.emplace( "fat" );
          uset.emplace( "lazy" );
          uset.emplace( "dog" );

          std::cout << uset << "\n";

          std::cout << "bucket count: " << uset.bucket_count() << "\n";
          for( auto i = 0u; i < uset.bucket_count(); ++i )
          {
               std::cout << "bucket index " << std::setw( 2 ) << i << ": " << uset.bucket_size( i ) << " "
                    << ostream_tools::range( uset.cbegin( i ), uset.cend( i ) ) << "\n";
          }
     }
     catch( const std::exception& e )
     {
          std::cerr << "exception: " << boost::diagnostic_information( e ) << '\n';
          return 1;
     }

     return 0;
}
