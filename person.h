///
/// person.h
///
/// Created on: Dec 10, 2017
///     Author: alexen
///

#pragma once

#include <iostream>
#include <string>
#include <functional>


class Person {
public:
     Person( const std::string& lastName, const std::string& firstName, std::ostream& ostr = std::clog );

     Person( const Person& o );

     Person( Person&& o );

     const std::string& lastName() const noexcept;

     const std::string& firstName() const noexcept;

private:
     const std::string lastName_;
     const std::string firstName_;
     std::ostream& ostr_;
};


inline bool operator==( const Person& p1, const Person& p2 )
{
     return p1.lastName() == p2.lastName() && p1.firstName() == p2.firstName();
}


namespace std
{

template<>
struct hash< Person > {
     size_t operator()( const Person& p ) const noexcept
     {
          return hash< std::string >{}( p.lastName() )
               ^ hash< std::string >{}( p.firstName() );
     }
};

}