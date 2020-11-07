/// @file
/// @brief
/// @copyright Copyright (c) InfoTeCS. All Rights Reserved.

#include <errors/errors.h>


namespace using_cpp {
namespace errors {

namespace {
namespace aux {


struct NetworkErrorCategory : std::error_category
{
     const char* name() const noexcept override
     {
          return "network error";
     }
     std::string message( int ec ) const override
     {
          return network::details( static_cast< network::NetworkError >( ec ) );
     }
};


struct HttpErrorCategory : std::error_category
{
     const char* name() const noexcept override
     {
          return "http error";
     }
     std::string message( int ec ) const override
     {
          return http::details( static_cast< http::HttpErrorStatus >( ec ) );
     }
};


} // namespace aux
} // namespace {unnamed}


namespace network {


const std::string details( const NetworkError error )
{
     using namespace std::literals;
     switch( error )
     {
          case NetworkError::NetworkUnreachable:       return "network is unreachable"s;
          case NetworkError::AddressAlreadyUsed:       return "address is already in use"s;
          case NetworkError::ProtocolNotSupported:     return "protocol is not supported"s;
          case NetworkError::ChannelIsBusy:            return "channel is busy"s;
          case NetworkError::ConnectionRefused:        return "connection refused"s;
          default:
               break;
     }
     return "unexplained error"s;
}


const std::error_category& category()
{
     static const aux::NetworkErrorCategory inst;
     return inst;
}


} // namespace network
namespace http {


const std::string details( const HttpErrorStatus status )
{
     using namespace std::literals;
     switch( status )
     {
          case HttpErrorStatus::InternalServerError:   return "INTERNAL SERVER ERROR"s;
          case HttpErrorStatus::BadRequest:            return "BAD REQUEST"s;
          case HttpErrorStatus::ServiceNotAvailable:   return "SERVICE IS NOT AVAILABLE"s;
          case HttpErrorStatus::NotFound:              return "NOT FOUND"s;
          case HttpErrorStatus::Forbidden:             return "FORBIDDEN"s;
          case HttpErrorStatus::Unauthorized:          return "UNAUTHORIZED"s;
          default:
               break;
     }
     return "UNRECOGNIZED STATUS"s;
}


const std::error_category& category()
{
     static const aux::HttpErrorCategory inst;
     return inst;
}


} // namespace http


std::error_code make_error_code( const using_cpp::errors::network::NetworkError error )
{
     return { static_cast< int >( error ), network::category() };
}


std::error_code make_error_code( const using_cpp::errors::http::HttpErrorStatus status )
{
     return { static_cast< int >( status ), http::category() };
}


} // namespace errors
} // namespace using_cpp
