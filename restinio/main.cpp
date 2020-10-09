#include <restinio/all.hpp>
#include "json/json.h"

//using namespace restinio;

restinio::request_handling_status_t handleIndex(restinio::request_handle_t& req, restinio::router::route_params_t& params) {
    const auto qp = restinio::parse_query(req->header().query());

    Json::Value data;
    data["code"] = 200;
    data["value"] = "Response OK";
    Json::StreamWriterBuilder builder;
    builder["commentStyle"] = "None";
    builder["indentation"] = "";

    return req->create_response(restinio::status_ok())
        .set_body(Json::writeString(builder, data))
        .append_header(restinio::http_field::content_type, "application/json")
        .done();
}

int connect(std::string address, int port) {
    try {
        std::unique_ptr<restinio::router::express_router_t<>> router = std::make_unique<restinio::router::express_router_t<>>();

        router->http_get(R"(/index)", [](auto req, auto params) {
            return handleIndex(req, params);
        });

        router->non_matched_request_handler([](auto req){
            return req->create_response(restinio::status_not_found()).connection_close().done();
        });

        struct server_traits : public restinio::default_single_thread_traits_t {
            using request_handler_t = restinio::router::express_router_t<>;
        };

        restinio::run(
            //restinio::on_this_thread()
            //restinio::on_thread_pool( std::thread::hardware_concurrency() )
            //restinio::on_this_thread<server_traits>()
            restinio::on_thread_pool<server_traits>(std::thread::hardware_concurrency())
            .port(port)
            .address(address)
            .request_handler(std::move(router)));
            
    } catch(const std::exception & ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
		return 1;
    }

    return 0;
}

int main() {
    return connect("0.0.0.0", 3000);
}
