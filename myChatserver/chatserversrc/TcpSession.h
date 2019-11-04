//
// Created by lzy on 11/4/19.
//

#ifndef SERVER_TCPSESSION_H
#define SERVER_TCPSESSION_H

#include <memory>
#include "net/TcpConnection.h"
using namespace net;

class TcpSession {
public:
    TcpSession(const std::weak_ptr<TcpConnection>& tmpconn);
    ~TcpSession();

    TcpSession(const TcpSession& rhs) = delete;
    TcpSession& operator =(const TcpSession& rhs) = delete;

    std::shared_ptr<TcpConnection> getConnectionPtr()
    {
        if (tmpConn_.expired())
            return NULL;

        return tmpConn_.lock();
    }

    void send(int32_t cmd, int32_t seq, const std::string& data);
    void send(int32_t cmd, int32_t seq, const char* data, int32_t dataLength);
    void send(const std::string& p);
    void send(const char* p, int32_t length);

private:
    void sendPackage(const char* p, int32_t length);

protected:
    std::weak_ptr<TcpConnection>    tmpConn_;
};


#endif //SERVER_TCPSESSION_H
