#include "ValidatorCLS.h"
#include <boost/asio.hpp>
#include <iostream>
#include <cerrno>


bool ValidatorIPAddresses::isValidIp(const QString& address)
{
    boost::system::error_code ec;
    bool pResult = true;
    boost::asio::ip::address::from_string(address.toStdString(),ec);
    if (ec)
    {
        std::cerr << ec.message() << std::endl;
        pResult = false;
    }
    return pResult;
}
