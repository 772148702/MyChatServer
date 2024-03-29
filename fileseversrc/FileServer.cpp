#include "FileServer.h"
#include "../net/InetAddress.h"
#include "../base/AsyncLog.h"
#include "../base/Singleton.h"
#include "FileSession.h"

bool FileServer::Init(const char* ip, short port, EventLoop* loop, const char* fileBaseDir/* = "filecache/"*/)
{
    m_strFileBaseDir = fileBaseDir;

    InetAddress addr(ip, port);
    m_server.reset(new TcpServer(loop, addr, "ZYL-MYImgAndFileServer", TcpServer::kReusePort));
    m_server->setConnectionCallback(std::bind(&FileServer::OnConnection, this, std::placeholders::_1));
    //启动侦听
    m_server->start(6);

    return true;
}


void FileServer::Uninit()
{
    if(m_server)
        m_server->stop();
}
void FileServer::OnConnection(std::shared_ptr<TcpConnection> conn)
{
    if (conn->connected())
    {
        LOGI("client connected: %s", conn->peerAddress().toIpPort().c_str());
        std::shared_ptr<FileSession> spSession(new FileSession(conn, m_strFileBaseDir.c_str()));
        conn->setMessageCallback(std::bind(&FileSession::OnRead, spSession.get(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

        std::lock_guard<std::mutex> guard(m_sessionMutex);
        m_sessions.push_back(spSession);
    }
    else
    {
        OnClose(conn);
    }
}

void FileServer::OnClose(const std::shared_ptr<TcpConnection>& conn)
{
    //TODO: 这样的代码逻辑太混乱，需要优化
    std::lock_guard<std::mutex> guard(m_sessionMutex);
    for (auto iter = m_sessions.begin(); iter != m_sessions.end(); ++iter)
    {
        if ((*iter)->GetConnectionPtr() == NULL)
        {
            LOGE("connection is NULL");
            break;
        }
                          
        //用户下线
        m_sessions.erase(iter);
        //bUserOffline = true;
        LOGI("client disconnected: %s", conn->peerAddress().toIpPort().c_str());
        break;       
    }    
} 