/// @file
/// @brief
/// @copyright Copyright (c) InfoTeCS. All Rights Reserved.

#pragma once

#include <system_error>
#include <boost/exception/exception.hpp>


namespace using_cpp {
namespace errors {


struct Exception : std::system_error, boost::exception
{
     explicit Exception( const std::error_code& ec ) : std::system_error{ ec } {}
};


namespace network {


enum class NetworkError
{
     NetworkUnreachable,
     AddressAlreadyUsed,
     ProtocolNotSupported,
     ChannelIsBusy,
     ConnectionRefused
};


const std::string details( const NetworkError error );
const std::error_category& category();


} // namespace network
namespace http {


enum class HttpErrorStatus
{
     InternalServerError,
     BadRequest,
     ServiceNotAvailable,
     NotFound,
     Forbidden,
     Unauthorized
};


const std::string details( const HttpErrorStatus status );
const std::error_category& category();


} // namespace http


std::error_code make_error_code( const network::NetworkError error );
std::error_code make_error_code( const http::HttpErrorStatus status );


} // namespace errors
} // namespace using_cpp


namespace std {


template<> struct is_error_code_enum< using_cpp::errors::network::NetworkError > : true_type {};
template<> struct is_error_code_enum< using_cpp::errors::http::HttpErrorStatus > : true_type {};


} // namespace std
