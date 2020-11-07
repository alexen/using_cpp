/// @file
/// @brief
/// @copyright Copyright (c) InfoTeCS. All Rights Reserved.

#pragma once

#include <system_error>


namespace using_cpp {
namespace errors {
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


} // namespace http


std::error_code make_error_code( const network::NetworkError error );
std::error_code make_error_code( const http::HttpErrorStatus status );


} // namespace errors
} // namespace using_cpp


namespace std {


template<> struct is_error_code_enum< using_cpp::errors::network::NetworkError > : true_type {};
template<> struct is_error_code_enum< using_cpp::errors::http::HttpErrorStatus > : true_type {};


} // namespace std
