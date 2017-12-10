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
#include <person.h>
#include <person_io.h>


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

          std::unordered_set< Person > persons;

          persons.emplace( "Кулибин", "Артур" );
          persons.emplace( "Проскурин", "Фёдор" );
          persons.emplace( "Дерябин", "Константин" );
          persons.emplace( "Корягин", "Михаил" );
          persons.emplace( "Собакевич", "Тарас" );

          std::cout << persons << "\n";

          const Person p1{ "Сергей", "Андрей" };
          const Person p2{ "Андрей", "Сергей" };

          std::cout
               << p1 << ": " << std::hash< Person >{}( p1 ) << "\n"
               << p2 << ": " << std::hash< Person >{}( p2 ) << "\n";
     }
     catch( const std::exception& e )
     {
          std::cerr << "exception: " << boost::diagnostic_information( e ) << '\n';
          return 1;
     }

     return 0;
}
