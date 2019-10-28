#pragma once

#include <memory>
#include <mutex>
#include <list>
#include "../net/EventLoop.h"
#include "../net/TcpServer.h"
using namespace net;


class HttpSession;
class HttpServer final
{
    public:
        HttpServer() = default;
        ~HttpServer() = default;
        HttpServer(const HttpServer& rhs) = delete;
        HttpServer& operator= (const HttpServer& rhs)= delete;
    public:
        bool Init(const char* ip,short port,EventLoop* loop);
        void Uninit();

        void OnConnection(std::shared_ptr<TcpConnection> conn);
        void OnClose(const std::shared_ptr<TcpConnection>& conn);
    private:
        std::shared_ptr<TcpServer>                  m_server;
        std::list<std::shared_ptr<HttpSession>>     m_sessions;
        std::mutex                                  m_sessionMutex;
};