
#include "HttpServer.h"
#include "../net/InetAddress.h"
#include "../base/AsyncLog.h"
#include "../base/Singleton.h"
//#include "../net/eventloop.h"
#include "../net/EventLoopThread.h"
#include "../net/EventLoopThreadPool.h"
#include "HttpSession.h"
#include "HttpServer.h"

bool HttpServer::Init(const char* ip, short port, EventLoop* loop)
{
    InetAddress addr(ip, port);
    m_server.reset(new TcpServer(loop, addr, "ZYL-MYHTTPSERVER", TcpServer::kReusePort));
    m_server->setConnectionCallback(std::bind(&HttpServer::OnConnection, this, std::placeholders::_1));
    //锟斤拷锟斤拷锟斤拷锟斤拷
    m_server->start();

    return true;
}

void HttpServer::Uninit()
{
    if (m_server)
        m_server->stop();
}

//锟斤拷锟斤拷锟接碉拷锟斤拷锟斤拷锟矫伙拷锟斤拷锟接断匡拷锟斤拷锟斤拷锟斤拷锟斤拷要通锟斤拷conn->connected()锟斤拷锟叫断ｏ拷一锟斤拷只锟斤拷锟斤拷loop锟斤拷锟斤拷锟斤拷锟�
void HttpServer::OnConnection(std::shared_ptr<TcpConnection> conn)
{
    if (conn->connected())
    {
        std::shared_ptr<HttpSession> spSession(new HttpSession(conn));
        conn->setMessageCallback(std::bind(&HttpSession::OnRead, spSession.get(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

        {
            std::lock_guard<std::mutex> guard(m_sessionMutex);
            m_sessions.push_back(spSession);
        }
    }
    else
    {
        OnClose(conn);
    }
}

//锟斤拷锟接断匡拷
void HttpServer::OnClose(const std::shared_ptr<TcpConnection>& conn)
{
    //TODO: 锟斤拷锟斤拷锟侥达拷锟斤拷锟竭硷拷太锟斤拷锟揭ｏ拷锟斤拷要锟脚伙拷
    std::lock_guard<std::mutex> guard(m_sessionMutex);
    for (auto iter = m_sessions.begin(); iter != m_sessions.end(); ++iter)
    {
        if ((*iter)->GetConnectionPtr() == NULL)
        {
            LOGE("connection is NULL");
            break;
        }

        //通锟斤拷锟饺讹拷connection锟斤拷锟斤拷锟揭碉拷锟斤拷应锟斤拷session
        if ((*iter)->GetConnectionPtr() == conn)
        {
            m_sessions.erase(iter);
            LOGI("monitor client disconnected: %s", conn->peerAddress().toIpPort().c_str());
            break;
        }
    }
}