#include <restinio/all.hpp>

using namespace restinio;

int main() {

    try {
        auto router = std::make_unique<router::express_router_t<>>();
        router->http_get(
            R"(/index)",
            [](auto req, auto params) {
                const auto qp = parse_query(req->header().query());
                return req->create_response()
                    .set_body("Hello, World!")
                    .append_header( restinio::http_field::content_type, "application/json" )
                    .done();
            });

        struct server_traits : public default_single_thread_traits_t {
            using request_handler_t = restinio::router::express_router_t<>;
        };

        restinio::run(
            //restinio::on_this_thread()
            //restinio::on_thread_pool( std::thread::hardware_concurrency() )
            //restinio::on_this_thread<server_traits>()
            restinio::on_thread_pool<server_traits>(std::thread::hardware_concurrency())
            .port(8080)
            .address("localhost")
            .request_handler(std::move(router)));
            /*.request_handler([](auto req) {
                return req->create_response()
                    .set_body("Hello, World!!")
                    .done();});*/
            
    } catch(const std::exception & ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
		return 1;
    }

    return 0;
}
