#include "./http.h"

#include <spdlog/spdlog.h>
#include <httplib.h>

void startServer() {
    spdlog::info("spdlog: Hello World!");

    httplib::Server server;
    server.Get("/", [](const httplib::Request &, httplib::Response &res) {
    res.set_content("Hello World!", "text/plain");
    });
    server.listen("0.0.0.0", 8080);
}
