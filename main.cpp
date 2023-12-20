#include <iostream>
#include "includes/CLI11.hpp"
#include "http_client.hpp"

int main(int argc, char **argv)
{

    CLI::App app;
    std::string url;
    std::string verb;
    std::string data;
    std::vector<std::string> headers;
    bool verbose;

    app.add_flag("-v, --verbose", verbose, "Dump complete request and response");
    app.add_option("-X, --request", verb, "specify request method to use")
        ->default_val("GET")
        ->check(CLI::IsMember({"GET", "POST", "PUT", "DELETE"}));
    app.add_option("-d, --data", data, "Add data to the request body");
    app.add_option("-H, --header", headers, "Pass custom header(s) to server");
    app.add_option("url", url, "url")->required();
    CLI11_PARSE(app, argc, argv);

    Http_Client client(url);
    std::cout << client.send(verb, &data, &headers, verbose);

    return 0;
}
