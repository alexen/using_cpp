///
/// person_io.h
///
/// Created on: Dec 10, 2017
///     Author: alexen
///

#pragma once

#include <iosfwd>

class Person;

std::ostream& operator<<( std::ostream& ostr, const Person& p );
