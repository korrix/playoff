#include "Connection.h"

#include <boost/asio.hpp>

namespace networking {
model::Event Connection::request(const model::Event &event) {
    {
        auto json = serialization::toJson(event);

        boost::asio::streambuf request;
        std::ostream request_stream(&request);
        request_stream << json << std::endl;

        boost::asio::write(socket_, request);
    }
    {
        boost::asio::streambuf response;
        boost::asio::read_until(socket_, response, "\n");
        std::istream response_stream(&response);

        nlohmann::json json;
        response_stream >> json;

        auto res = serialization::fromJson<model::Event>(json);
        res.visit([](auto, auto &error) {
            if constexpr(std::is_base_of_v<std::exception, std::decay_t<decltype(error)>>) {
                throw error;
            }
        });

        return res;
    }
}
}  // namespace networking