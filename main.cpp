///
/// main.cpp
///
/// Created on: Oct 11, 2017
///     Author: alexen
///

#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <tuple>
#include <vector>
#include <locale>
#include <streambuf>
#include <fstream>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <system_error>
#include <numeric>
#include <boost/bind/bind.hpp>
#include <boost/container_hash/hash.hpp>
#include <boost/utility/string_view.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/exception/diagnostic_information.hpp>


namespace case_ignored {


struct hash {
     std::size_t operator()( const std::string& s ) const noexcept {
          std::size_t seed = 0u;
          std::for_each( std::cbegin( s ), std::cend( s ),
               [ &seed ]( const char c ){
                    boost::hash_combine( seed, ::tolower( c ) );
               });
          return seed;
     }
};

struct equal_to {
     bool operator()( const std::string& lhs, const std::string& rhs ) const {
          static constexpr auto equal = []( const char l, const char r ){
               return ::tolower( l ) == ::tolower( r );
          };
          return lhs.size() == rhs.size()
               && std::equal( lhs.begin(), lhs.end(), rhs.begin(), equal );
     }
};


} // namespace case_ignored
namespace http {


using Headers = std::unordered_multimap<
     std::string
     , std::string
     , case_ignored::hash
     , case_ignored::equal_to
     >;


} // namespace http


std::ostream& operator<<( std::ostream& os, const http::Headers::value_type& v )
{
     os << v.first;
     if( !v.second.empty() )
     {
          os << ": " << v.second;
     }
     return os;
}


std::ostream& operator<<( std::ostream& os, const http::Headers& h )
{
     for( auto&& item: h )
     {
          os << "  " << item << '\n';
     }
     return os;
}


void parseHeader( const char* ptr, std::size_t size, http::Headers& headers )
{
     BOOST_ASSERT( boost::string_view( ptr, size ).ends_with( "\r\n" ) );

     const auto end = ptr + size - 2u;
     auto sep = std::find( ptr, end, ':' );

     std::string key{ ptr, sep };
     if( sep != end )
     {
          sep = std::find_if_not( ++sep, end, ::isspace );
     }
     std::string value{ sep, end };

     headers.emplace( std::move( key ), std::move( value ) );
}


void parseResponseHeaders( std::initializer_list< boost::string_view > r, http::Headers& h )
{
     std::for_each( r.begin(), r.end(), [ &h ]( boost::string_view data ){
          parseHeader( data.data(), data.size(), h );
     } );
}


void testHeaders()
{

     std::initializer_list< boost::string_view > r1{
          "HTTP/1.1 200 OK\r\n"
          , "Server: nginx\r\n"
          , "Date: Wed, 01 Nov 2023 16:46:20 GMT\r\n"
          , "Content-Type: text/html; charset=UTF-8\r\n"
          , "Connection: keep-alive\r\n"
          , "Set-Cookie: region_id=2eac47ad4da9bad80b75b8c6c10e42763572104ff9f674a15219f28c861b9ea6a%3A2%3A%7Bi%3A0%3Bs%3A9%3A%22region_id%22%3Bi%3A1%3Bs%3A2%3A%2277%22%3B%7D; path=/; httponly\r\n"
          , "Set-Cookie: _csrf-frontend=da4e6e13f4b768ee3991ef1fc377a4b5473bd372563cb15aae5963dff2cddbcfa%3A2%3A%7Bi%3A0%3Bs%3A14%3A%22_csrf-frontend%22%3Bi%3A1%3Bs%3A32%3A%22HbuvYHL-GGmtcwXebdwKLMoqkDO45iYg%22%3B%7D; path=/; httponly\r\n"
          , "X-Frame-Options: SAMEORIGIN\r\n"
          , "X-XSS-Protection: 1; mode=block\r\n"
          , "Strict-Transport-Security: max-age=31536000; includeSubDomains;\r\n"
          , "X-Content-Type-Options: nosniff\r\n"
     };

     std::initializer_list< boost::string_view > r2{
          "HTTP/2 302\r\n"
          , "x-yandex-eu-request: 0\r\n"
          , "location: https://yandex.ru/showcaptcha?cc=1&mt=FB78C9EFA7C3C56495A0429F98677E88878D20491D4C3A646E3238A966BC9D24C90E485C01C94B76F800C201EDBB137DF52337F0AE78B5C89CEBCB74FB41756DF5AF4AB330736D90C6272810EAAD07ACF701C7EB39CF6E676B4C42218374ECB5128ED646CBC04C4166F20607D960BB&retpath=aHR0cHM6Ly95YW5kZXgucnUvPw%2C%2C_8a3d8cd91de78fdae70cfbebe10f931b&t=2/1698857181/966758794276b9154bb6cad9ad5ff9cd&u=903a995f-f592af86-109a9dd7-8ab9683c&s=f681bc8350d7ac7b9b6ee06c10c1bf14\r\n"
          , "nel: {\"report_to\": \"network-errors\", \"max_age\": 100, \"success_fraction\": 0.001, \"failure_fraction\": 0.1}\r\n"
          , "x-content-type-options: nosniff\r\n"
          , "x-yandex-captcha: captcha\r\n"
          , "set-cookie: spravka=dD0xNjY3MzIxMTgxO2k9OTAuMTU0LjcxLjEzODtEPTk1NTA3ODExODJEQkUzMTcxMkYyRkQ1MkIwOTM4NkI1RUYzMkVFRTc2QzM0MUY2NUQ4RDM3RTI4QUNFOTBGRDlBQjY3NkI2MzBEOTBBNUM5O3U9MTY2NzMyMTE4MTEzNjE3NzgyMTtoPTcyNTVmNGE3MTI3ZWQ3YjZiOWYyMjllYzRkMzM5Njk1; domain=.yandex.ru; path=/; expires=Fri, 01 Dec 2023 16:46:21 GMT\r\n"
          , "set-cookie: _yasc=qVyM3iyehvONTP14kOnYSC6biWP5QNdA5aBQdwpJx7gdEN5BwfTRfPOrWkXJ682GuP6x; domain=.yandex.ru; path=/; expires=Sat, 29 Oct 2033 16:46:21 GMT; secure\r\n"
          , "set-cookie: i=MN0wSU91YrCcndkK0e4rJFyBsyv7oA9gZp+e0J7aMiw+gRPEA5HFmFaGoTWrqFJbLXOg9Z5IWao8Fue0Fh12SDHKKbM=; Expires=Fri, 31-Oct-2025 16:46:21 GMT; Domain=.yandex.ru; Path=/; Secure; HttpOnly\r\n"
          , "set-cookie: yandexuid=1972649271698857181; Expires=Fri, 31-Oct-2025 16:46:21 GMT; Domain=.yandex.ru; Path=/; Secure\r\n"
          , "set-cookie: yashr=4077123721698857181; Path=/; Domain=.yandex.ru; Expires=Thu, 31 Oct 2024 16:46:21 GMT; Secure; HttpOnly\r\n"
          , "x-yandex-req-id: 1698857181135446-3642460723897264927-balancer-l7leveler-kubr-yp-sas-149-BAL\r\n"
          , "accept-ch: Sec-CH-UA-Platform-Version, Sec-CH-UA-Mobile, Sec-CH-UA-Model, Sec-CH-UA, Sec-CH-UA-Full-Version-List, Sec-CH-UA-WoW64, Sec-CH-UA-Arch, Sec-CH-UA-Bitness, Sec-CH-UA-Platform, Sec-CH-UA-Full-Version, Viewport-Width, DPR, Device-Memory, RTT, Downlink, ECT\r\n"
          , "report-to: { \"group\": \"network-errors\", \"max_age\": 100, \"endpoints\": [{\"url\": \"https://dr.yandex.net/nel\", \"priority\": 1}, {\"url\": \"https://dr2.yandex.net/nel\", \"priority\": 2}]}\r\n"
     };


     http::Headers h1;
     parseResponseHeaders( r1, h1 );
     std::cout << "Headers #1:\n" << h1 << '\n';

     http::Headers h2;
     parseResponseHeaders( r2, h2 );
     std::cout << "Headers #2:\n" << h2 << '\n';

     auto key = "set-cookie";
     std::cout << "Headers #1: " << key << " contaned " << h1.count( key ) << " times\n";
     std::cout << "Headers #2: " << key << " contaned " << h2.count( key ) << " times\n";

     key = "SET-COOKIE";
     std::cout << "Headers #1: " << key << " contaned " << h1.count( key ) << " times\n";
     std::cout << "Headers #2: " << key << " contaned " << h2.count( key ) << " times\n";

     key = "Set-Cookie";
     std::cout << "Headers #1: " << key << " contaned " << h1.count( key ) << " times\n";
     std::cout << "Headers #2: " << key << " contaned " << h2.count( key ) << " times\n";
}


int main()
{
     try
     {
          testHeaders();
     }
     catch( const std::exception& e )
     {
          std::cerr << "exception: " << boost::diagnostic_information( e ) << '\n';
          return 1;
     }

     return 0;
}
