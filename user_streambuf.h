///
/// user_streambuf.h
///
/// Created on: Dec 23, 2017
///     Author: alexen
///

#pragma once

#include <streambuf>
#include <vector>


using Buffer = std::vector< char >;


class BufferStream : public std::streambuf {
public:
     explicit BufferStream( Buffer& outbuf ) : outbuf_{ outbuf } {}
protected:
     virtual int_type overflow( const int_type c ) override
     {
          if( c != EOF )
          {
               outbuf_.push_back( c );
          }
          return c;
     }

     virtual std::streamsize xsputn( const char* str, std::streamsize len ) override
     {
          outbuf_.insert( outbuf_.end(), str, str + len );
          return len;
     }
private:
     Buffer& outbuf_;
};


class StaticBufferStream : public std::streambuf {
public:
     StaticBufferStream( char* data, std::streamsize len )
          : curr_{ data }
          , end_{ data + len }
     {}

protected:
     virtual int_type overflow( const int_type c ) override
     {
          if( c != EOF )
          {
               const char cc = c;
               return copy( &cc, 1 );
          }
          return c;
     }

     virtual std::streamsize xsputn( const char* cc, std::streamsize n ) override
     {
          return copy( cc, n );
     }

private:
     std::streamsize copy( const char* cc, const std::streamsize n )
     {
          for( int i = 0; i < n && curr_ != end_; ++i, ++curr_ )
          {
               *curr_ = cc[ i ];
          }
          return curr_ == end_ ? EOF : n;
     }

     char* curr_;
     const char* const end_;
};


class FdStreambuf : public std::streambuf {
public:
     explicit FdStreambuf( int fd ) : fd_{ fd } {}
protected:
     virtual int_type overflow( const int_type c ) override
     {
          if( c != EOF )
          {
               const char cc = c;
               if( copy( &cc, 1 ) < 0 )
               {
                    return EOF;
               }
          }
          return c;
     }

     virtual std::streamsize xsputn( const char* cc, std::streamsize n ) override
     {
          return copy( cc, n );
     }

private:
     int copy( const char* cc, std::streamsize n )
     {
          return write( fd_, cc, n );
     }

     int fd_;
};
