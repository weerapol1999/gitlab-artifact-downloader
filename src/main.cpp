#include <drogon/drogon.h>
#include "gitlab-downloader/controllers/ApiController.hpp"
#include <iostream>
#include <fmt/format.h>

int main()
{
    try
    {
        // ตั้งค่าเซิร์ฟเวอร์
        drogon::app().setLogLevel(trantor::Logger::kDebug);

        // เพิ่ม CORS
        drogon::app().registerPostHandlingAdvice(
            [](const drogon::HttpRequestPtr &,
               const drogon::HttpResponsePtr &resp)
            {
                resp->addHeader("Access-Control-Allow-Origin", "*");
                resp->addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
                resp->addHeader("Access-Control-Allow-Headers", "Content-Type");
            });

        // กำหนด HTTP listener
        drogon::app().addListener("0.0.0.0", 3000);

        // เพิ่ม log เมื่อเซิร์ฟเวอร์เริ่มต้น
        drogon::app().registerBeginningAdvice([]()
                                              { std::cout << "Server is up and running. Listening on http://localhost:3000\n"; });

        // แสดง log เมื่อรับ request
        drogon::app().registerPreRoutingAdvice([](const drogon::HttpRequestPtr &req)
                                               { std::cout << fmt::format("Received request: {} {}\n", req->methodString(), req->path()); });

        // เริ่มเซิร์ฟเวอร์
        std::cout << "Initializing server...\n";
        drogon::app().run();
    }
    catch (const std::exception &e)
    {
        std::cerr << fmt::format("Error starting server: {}\n", e.what());
        return 1;
    }

    return 0;
}