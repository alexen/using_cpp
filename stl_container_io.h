///
/// stl_container_io.h
///
/// Created on: Dec 9, 2017
///     Author: alexen
///

#pragma once

#include <cstddef>
#include <map>
#include <set>
#include <array>
#include <ostream>
#include <iterator>

#include <boost/type_index.hpp>


namespace ostream_tools
{


template< typename T >
struct Quote {
     explicit Quote( const T& v ) : value{ v } {}
     void print( std::ostream& ostr ) const
     {
          ostr << value;
     }
     const T& value;
};


template<>
struct Quote< char > {
     explicit Quote( char c ) : value{ c } {}
     void print( std::ostream& ostr ) const
     {
          ostr << '\'' << value << '\'';
     }
     const char value;
};


template< typename T, std::size_t Size >
struct Quote< T[ Size ] > {
     explicit Quote( T const (&c)[ Size ] ) : value{ c } {}
     void print( std::ostream& ostr ) const
     {
          ostr << '"' << value << '"';
     }
     T const (&value)[ Size ];
};


template<>
struct Quote< const char* > {
     explicit Quote( const char* const cstr ) : value{ cstr } {}
     void print( std::ostream& ostr ) const
     {
          ostr << '"' << value << '"';
     }
     const char* const value;
};


template<>
struct Quote< std::string > {
     explicit Quote( const std::string& str ) : value{ str } {}
     void print( std::ostream& ostr ) const
     {
          ostr << '"' << value << '"';
     }
     const std::string& value;
};


template< typename T >
inline Quote< T > quote( const T& value )
{
     return Quote< T >{ value };
}


template< typename Iter >
struct Range {
     Range( Iter b, Iter e )
          : begin{ b }
          , end{ e }
     {}
     const Iter begin, end;
};


template< typename Iter >
inline Range< Iter > range( Iter begin, Iter end )
{
     return Range< Iter >{ begin, end };
}


template< typename Iter >
inline Range< Iter > range( const std::pair< Iter, Iter >& pair )
{
     return Range< Iter >{ pair.first, pair.second };
}


template< std::size_t Index, std::size_t Size, typename ...Args >
struct TuplePrinter
{
     static void print( std::ostream& ostr, const std::tuple< Args... >& tuple )
     {
          ostr
               << ostream_tools::quote( std::get< Index >( tuple ) )
               << (Index + 1 == Size ? "" : ", ");
          TuplePrinter< Index + 1, Size, Args... >::print( ostr, tuple );
     }
};


template< std::size_t Size, typename ...Args >
struct TuplePrinter< Size, Size, Args... >
{
     static void print( std::ostream&, const std::tuple< Args... >& )
     {}
};

}


template< typename T >
inline std::ostream& operator<<( std::ostream& ostr, const ostream_tools::Quote< T >& quoted )
{
     quoted.print( ostr );
     return ostr;
}


template< typename Iter >
std::ostream& operator<<( std::ostream& ostr, const ostream_tools::Range< Iter >& seq )
{
     for( auto iter = seq.begin; iter != seq.end; ++iter )
     {
          ostr << (iter == seq.begin ? "" : ", ") << ostream_tools::quote( *iter );
     }
     return ostr;
}


template< typename ...Args >
inline std::ostream& operator<<( std::ostream& ostr, const std::tuple< Args... >& tuple )
{
     ostr << "std::tuple<";
     ostream_tools::TuplePrinter< 0, sizeof...( Args ), Args... >::print( ostr, tuple );
     ostr << ">";
     return ostr;
}


template< typename T, typename U >
inline std::ostream& operator<<( std::ostream& ostr, const std::pair< T, U >& pair )
{
     ostr << "std::pair<"
          << boost::typeindex::type_id_with_cvr< T >().pretty_name()
          << ", "
          << boost::typeindex::type_id_with_cvr< U >().pretty_name()
          << ">{"
          << ostream_tools::quote( pair.first )
          << ", "
          << ostream_tools::quote( pair.second )
          << "}";
     return ostr;
}


template< typename T, std::size_t Size >
inline std::ostream& operator<<( std::ostream& ostr, const std::array< T, Size >& array )
{
     ostr << "std::array<"
          << boost::typeindex::type_id_with_cvr< T >().pretty_name()
          << ", "
          << Size
          << ">{"
          << ostream_tools::range( array.cbegin(), array.cend() )
          << "}";
     return ostr;
}


template< typename T >
inline std::ostream& operator<<( std::ostream& ostr, const std::set< T >& set )
{
     ostr << "std::set<"
          << boost::typeindex::type_id_with_cvr< T >().pretty_name()
          << ">{"
          << ostream_tools::range( set.cbegin(), set.cend() )
          << "}";
     return ostr;
}


template< typename K, typename V >
std::ostream& operator<<( std::ostream& ostr, const std::map< K, V >& m )
{
     ostr << "std::map<"
          << boost::typeindex::type_id_with_cvr< K >().pretty_name()
          << ", "
          << boost::typeindex::type_id_with_cvr< V >().pretty_name()
          << ">{";
     for( auto iter = m.cbegin(); iter != m.cend(); ++iter )
     {
          ostr << (iter == m.cbegin() ? "" : ", ")
               << ostream_tools::quote( iter->first )
               << ": "
               << ostream_tools::quote( iter->second );
     }
     ostr << "}";
     return ostr;
}
