///
/// person.cpp
///
/// Created on: Dec 10, 2017
///     Author: alexen
///

#include <person.h>
#include <stl_container_io.h>


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


std::ostream& operator<<( std::ostream& ostr, const Person& p )
{
     ostr << "Person("
          << ostream_tools::quote( p.lastName() )
          << ", "
          << ostream_tools::quote( p.firstName() )
          << ")";
     return ostr;
}
