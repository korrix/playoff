#include "Server.h"

#include <boost/asio.hpp>
#include <spdlog/spdlog.h>

int main(int argc, char *argv[]) {
    try {
        if(argc != 2) {
            spdlog::error("Usage: {} <port>", argv[0]);  // I know, i know ;)
            return EXIT_FAILURE;
        }

        boost::asio::io_context io_context(1);

        server::Server server(io_context, std::atoi(argv[1]));

        io_context.run();
    } catch(std::exception &e) {
        spdlog::error("Exeption: {}", e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}