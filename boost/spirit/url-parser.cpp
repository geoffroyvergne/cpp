// https://gist.github.com/microcai/516ffa19cfbb92d1ea4f5dd1d9c00472
// https://gist.github.com/microcai/0bd9255e12b6655b88554b7e76735ab3

#include <iostream>

#include <optional>
#include <vector>
#include <string>
#include <string_view>
#include <variant>

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

#include <boost/asio/ip/address.hpp>

struct KV {
	std::string k;
	std::string v;
};

struct URL {
	using host_t = boost::variant<std::string, boost::asio::ip::address>;

	std::string schema; // http/https

	host_t host;
	std::string username;
	std::string password;
	boost::optional<int> port;
	std::string path = "/";
	std::vector<KV> query;
	std::string fragment;
};

namespace qi = boost::spirit::qi;

BOOST_FUSION_ADAPT_STRUCT(
	KV,
	(std::string, k)
	(std::string, v)
)

BOOST_FUSION_ADAPT_STRUCT(
	URL,
	(std::string, schema)
	(URL::host_t, host)
	(std::string, username)
	(std::string, password)
	(boost::optional<int>, port)
	(std::string, path)
	(std::vector<KV>, query)
	(std::string, fragment)
)

static boost::asio::ip::address_v4 from_v4_string(std::vector<char> str) {
	return boost::asio::ip::address_v4::from_string(str.data());
}

static boost::asio::ip::address_v6 from_v6_string(std::vector<char> str) {
	return boost::asio::ip::address_v6::from_string(str.data());
}

BOOST_PHOENIX_ADAPT_FUNCTION(boost::asio::ip::address_v4, v4_from_string, from_v4_string, 1)
BOOST_PHOENIX_ADAPT_FUNCTION(boost::asio::ip::address_v6, v6_from_string, from_v6_string, 1)


template <typename Iterator>
struct uri_grammer : qi::grammar<Iterator, URL()> {
	typedef unsigned long ulong;
	uri_grammer() : uri_grammer::base_type(url) {
		using namespace boost::phoenix;

		url = schema [ at_c<0>(qi::_val) = qi::_1 ]
			>> "://" -( username [ at_c<2>(qi::_val) = qi::_1 ] >> -( ':' >> password  [ at_c<3>(qi::_val) = qi::_1 ] ) >> '@' )
			>> host [ at_c<1>(qi::_val) = qi::_1 ]
			>> -(qi::lit(':') >> qi::int_ [ at_c<4>(qi::_val) = qi::_1 ] )
			>> -(path [ at_c<5>(qi::_val) = qi::_1 ] >> -('?' >> query[ at_c<6>(qi::_val) = qi::_1 ]))
			>> -('#' >> fragment [ at_c<7>(qi::_val) = qi::_1 ]);

		host = ip_host | domain_host;

		domain_host = qi::lexeme[ +(qi::char_("a-zA-Z0-9.")) ];
		ipv4_host = (+qi::char_("0-9.")) [ qi::_val = v4_from_string(qi::_1) ] ;
		ipv6_host = (+qi::char_("0123456789abcdefABCDEF:")) [ qi::_val = v6_from_string(qi::_1) ] ;

		ip_host =  ('[' >>  ipv6_host[ qi::_val =  construct<boost::asio::ip::address>(qi::_1) ] >> ']') | ipv4_host [ qi::_val =  construct<boost::asio::ip::address>(qi::_1)];

		username = qi::lexeme[ +(qi::char_ - ':' - '@') ];
		password = qi::lexeme[ +(qi::char_ - '@') ];

		schema = qi::lexeme[ +(qi::char_ - ':' - '/') ];

		path = qi::lexeme[ +(qi::char_ - '?' - '#') ];

		query =  pair >> *((qi::lit(';') | '&') >> pair);
		pair  =  key >> -('=' >> value);
		key = qi::lexeme[ +(qi::char_ - '=' - '#') ];
		value = qi::lexeme[ *(qi::char_ - '&' - '#') ];

		fragment = qi::lexeme[ +(qi::char_) ];

	};

	qi::rule<Iterator, URL()> url;
	qi::rule<Iterator, std::string()> schema, path;

	qi::rule<Iterator, boost::variant<std::string, boost::asio::ip::address>()> host;

	qi::rule<Iterator, std::string()> domain_host;
	qi::rule<Iterator, boost::asio::ip::address()> ip_host;

	qi::rule<Iterator, boost::asio::ip::address_v4()> ipv4_host;
	qi::rule<Iterator, boost::asio::ip::address_v6()> ipv6_host;;

	qi::rule<Iterator, std::string()> username, password;

	qi::rule<Iterator, std::vector<KV>()> query;
	qi::rule<Iterator, KV()> pair;
	qi::rule<Iterator, std::string()> key, value;

	qi::rule<Iterator, std::string()> fragment;
};

URL parse_url(const std::string_view& url) {
	URL ast;

	uri_grammer<std::string_view::const_iterator> gramer;

	//auto first = url.begin();
	//bool r = boost::spirit::qi::parse(first, url.end(), gramer, ast);

	return ast;
}

int main() {
    URL url = parse_url("https://www.google.fr/");
    std::cout << "schema : " << url.schema << std::endl;
    std::cout << "host : " << url.host << std::endl;
    //std::cout << "port : " << url.port << std::endl;
    //std::cout << "query_path : " << url.query_path << std::endl;
    //std::cout << "query_params : " << url.query_params << std::endl;
    std::cout << "anchor : " << url.fragment << std::endl;

    return EXIT_SUCCESS;
}
