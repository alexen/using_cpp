///
/// person.cpp
///
/// Created on: Dec 10, 2017
///     Author: alexen
///

#include <entities/person.h>
#include <io/tools.h>
#include <iostream>



std::ostream& operator<<( std::ostream& ostr, const using_cpp::entities::Person& p )
{
     ostr << "Person("
          << using_cpp::io::tools::quote( p.lastName() )
          << ", "
          << using_cpp::io::tools::quote( p.firstName() )
          << ")";
     return ostr;
}


namespace using_cpp {
namespace entities {


Person::Person( const std::string& lastName, const std::string& firstName, std::ostream& ostr )
     : lastName_{ lastName }
     , firstName_{ firstName }
     , ostr_( ostr )
{
     ostr_ << __PRETTY_FUNCTION__ << "\n";
}


Person::Person( const Person& o )
     : lastName_{ o.lastName_ }
     , firstName_{ o.firstName_ }
     , ostr_( o.ostr_ )
{
     ostr_ << __PRETTY_FUNCTION__ << "\n";
}


Person::Person( Person&& o )
     : lastName_{ std::move( o.lastName_ ) }
     , firstName_{ std::move( o.firstName_ ) }
     , ostr_( o.ostr_ )
{
     ostr_ << __PRETTY_FUNCTION__ << "\n";
}


const std::string& Person::lastName() const noexcept
{
     return lastName_;
}


const std::string& Person::firstName() const noexcept
{
     return firstName_;
}


} // namespace entities
} // namespace using_cpp
