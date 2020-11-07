///
/// person_io.h
///
/// Created on: Dec 10, 2017
///     Author: alexen
///

#pragma once

#include <iosfwd>


namespace using_cpp {
namespace entities {

class Person;

} // namespace entities
} // namespace using_cpp


std::ostream& operator<<( std::ostream& ostr, const using_cpp::entities::Person& p );
