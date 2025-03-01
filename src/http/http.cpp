#include "./http.h"

#include <spdlog/spdlog.h>
#include <httplib.h>
#include <nlohmann/json.hpp>

void startServer() {
    spdlog::info(">>> HttpServer, 0.0.0.0:9863");
    httplib::Server server;

    server.Get("/", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
        res.set_header("Access-Control-Allow-Origin", "*");
    });
    server.Get("/test", [](const httplib::Request &, httplib::Response &res) {
        nlohmann::json resp_json = R"({
            "code": 0,
            "msg": "",
            "data": {
                "message": "Hello Test!"
            }
        })"_json;
        std::string resp_str = resp_json.dump();

        res.set_content(resp_str, "application/json");
        res.set_header("Access-Control-Allow-Origin", "*");
    });

    server.Options("/*", [](const httplib::Request &, httplib::Response &res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        res.set_content("", "text/plain");
    });

    server.listen("0.0.0.0", 9863);
    spdlog::info("<<< HttpServer");
}
