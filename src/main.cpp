#include <iostream>
#include "crow.h"

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
        .methods(crow::HTTPMethod::GET)(
            []()
            {
                crow::json::wvalue res;
                res["message"] = "Home page";

                return crow::response(200, res);
            });

    app.port(18080).multithreaded().run();

    return 0;
}