//
// Created by lzy on 11/4/19.
//

#ifndef SERVER_CHATSERVER_H
#define SERVER_CHATSERVER_H
#include <memory>
#include <list>
#include <map>
#include <mutex>
#include <atomic>
#include "net/TcpServer.h"
#include "net/EventLoop.h"
#include "ChatSession.h"

using namespace net;

enum CLIENT_TYPE
{
    CLIENT_TYPE_UNKOWN,
    CLIENT_TYPE_PC,
    CLIENT_TYPE_ANDROID,
    CLIENT_TYPE_IOS,
    CLIENT_TYPE_MAC
};

struct StoredUserInfo
{
    int32_t         userid;
    std::string     username;
    std::string     password;
    std::string     nickname;
};


class ChatServer {
public:

private:
    std::unique_ptr<TcpServer>                     m_server;
    std::list<std::shared_ptr<ChatSession>>        m_sessions;
    std::mutex                                     m_sessionMutex;      //多线程之间保护m_sessions
    std::atomic_int                                m_sessionId{};
    std::mutex                                     m_idMutex;           //多线程之间保护m_baseUserId
    std::atomic_bool                               m_logPackageBinary;  //是否日志打印出包的二进制数据
};


#endif //SERVER_CHATSERVER_H
