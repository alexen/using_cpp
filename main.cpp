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
#include <optional>
#include <chrono>

#include <boost/utility/string_ref.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/date_time.hpp>

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


class Employee
{
     static std::uint16_t idCounter;
public:
     struct Name
     {
          Name( std::string last, std::string first, std::optional< std::string > middle = {} )
               : lastName{ std::move( last ) }
               , firstName{ std::move( first ) }
               , middleName{ std::move( middle ) }
          {}

          std::string lastName;
          std::string firstName;
          std::optional< std::string > middleName;
     };

     Employee( Name name, boost::gregorian::date birthDate )
          : id_{ ++idCounter }
          , name_{ std::move( name ) }
          , birthDate_{ std::move( birthDate ) }
     {}

     Employee(
          std::string lastName,
          std::string firstName,
          std::optional< std::string > middleName,
          std::uint16_t year,
          std::uint16_t mon,
          std::uint16_t day
     )
          : Employee( {std::move( lastName ), std::move( firstName ), std::move( middleName )}, {year, mon, day} )
     {}

     std::uint16_t id() const noexcept
     {
          return id_;
     }

     const Name& name() const noexcept
     {
          return name_;
     }

     const boost::gregorian::date& birthDate() const noexcept
     {
          return birthDate_;
     }

private:
     std::uint16_t id_;
     Name name_;
     boost::gregorian::date birthDate_;
};

std::uint16_t Employee::idCounter = 0u;


std::ostream& operator<<( std::ostream& os, const Employee::Name& en )
{
     os << en.lastName << ' ' << en.firstName;
     if( en.middleName )
     {
          os << ' ' << *en.middleName;
     }
     return os;
}


std::ostream& operator<<( std::ostream& os, const Employee& e )
{
     return os << e.id() << ',' << e.name() << ',' << e.birthDate();
}


class Company
{
public:
     Company( std::string name )
          : name_{ std::move( name ) }
     {}

     const std::string& name() const noexcept
     {
          return name_;
     }

     template< typename ...Args >
     void addEmployee( Args&& ...args )
     {
          emps_.emplace_back( std::forward< Args >( args )... );
     }

     void printEmployees( std::ostream& os ) const
     {
          for( auto&& e: emps_ )
          {
               os << e << '\n';
          }
     }

private:
     std::string name_;
     std::vector< Employee > emps_;
};


std::ostream& operator<<( std::ostream& os, const Company& c )
{
     os << c.name() << '\n';
     c.printEmployees( os );
     return os;
}


} // namespace using_cpp


int main()
{
     using namespace std::string_literals;

     try
     {
          using_cpp::Employee emp{{ "Иванов", "Иван", "Иванович" }, { 1969, 3, 14 }};
          std::cout << "Employee: " << emp << '\n';

          using_cpp::Company c{ R"(ОАО "Фуагра")" };
          c.addEmployee( emp );
          c.addEmployee( "Петров"s, "Петр"s, "Петрович"s, 1973, 12, 24 );
          c.addEmployee( "Сергеева"s, "Алина"s, "Геннадьевна"s, 1984, 2, 4 );

          std::cout << "Company: " << c << '\n';
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
