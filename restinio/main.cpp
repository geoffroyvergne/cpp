#include <restinio/all.hpp>
#include "json/json.h"

using namespace restinio;

std::string getIndex(restinio::request_handle_t& req, restinio::router::route_params_t& params) {
    const auto qp = parse_query(req->header().query());

    Json::Value data;
    data["code"] = 200;
    data["value"] = "Response OK";
    Json::StreamWriterBuilder builder;
    builder["commentStyle"] = "None";
    builder["indentation"] = "";

    return Json::writeString(builder, data);
}

int main() {
    try {
        auto router = std::make_unique<router::express_router_t<>>();

        router->http_get(R"(/index)", [](auto req, auto params) {

                return req->create_response()
                    .set_body(getIndex(req, params))
                    .append_header(restinio::http_field::content_type, "application/json")
                    .done();
            });

        router->non_matched_request_handler(
            [](auto req){
                return req->create_response(restinio::status_not_found()).connection_close().done();
            });

        struct server_traits : public default_single_thread_traits_t {
            using request_handler_t = restinio::router::express_router_t<>;
        };

        restinio::run(
            //restinio::on_this_thread()
            //restinio::on_thread_pool( std::thread::hardware_concurrency() )
            //restinio::on_this_thread<server_traits>()
            restinio::on_thread_pool<server_traits>(std::thread::hardware_concurrency())
            .port(3000)
            .address("0.0.0.0")
            .request_handler(std::move(router)));
            
    } catch(const std::exception & ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
		return 1;
    }

    return 0;
}
