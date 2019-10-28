#pragma once

#include <memory>
#include "../net/TcpConnection.h"

using namespace net;

class BussinessLogic final
{
    private:
        BussinessLogic() = delete;
        ~BussinessLogic() = delete;

        BussinessLogic(const BussinessLogic& rhs) = delete;
        BussinessLogic& operator=(const BussinessLogic& rhs) = delete;
    public:
        static void RegisterUser(const std::string& data, const std::shared_ptr<TcpConnection>& conn, bool keepalive, std::string& retData);
};