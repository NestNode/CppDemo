#include "./http.h"

#include <spdlog/spdlog.h>
#include <httplib.h>

void startServer() {
    spdlog::info(">>> HttpServer port:0.0.0.0");
    httplib::Server server;
    server.Get("/", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
    });
    server.listen("0.0.0.0", 8080);
    spdlog::info("<<< HttpServer");
}
