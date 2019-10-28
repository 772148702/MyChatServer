#pragma once

#include "../net/Buffer.h"
#include "../base/Timestamp.h"
#include "../net/TcpConnection.h"
#include <memory>


using namespace net;

class MonitorSession
{
    public:
       MonitorSession(std::shared_ptr<TcpConnection>& conn);
       ~MonitorSession() = default;
       MonitorSession(const MonitorSession& rhs) = delete;
       MonitorSession& operator =(const MonitorSession& rhs) = delete;
    public:
        void OnRead(const std::shared_ptr<TcpConnection>& conn, Buffer* pBuffer, Timestamp receivTime);

        std::shared_ptr<TcpConnection> GetConnectionPtr()
        {
            if(m_tmpConn.expired())
                return NULL;
            return m_tmpConn.lock();
        }
        void ShowHelp();
        void Send(const char* data, size_t length);
    private:
        bool Process(const std::shared_ptr<TcpConnection>& conn, const std::string& inbuf);
        bool ShowOnlineUserList(const std::string& token="");
        bool ShowSpecifiedUserInfoById(int32_t userid);
    private:
        std::weak_ptr<TcpConnection> m_tmpConn;
};