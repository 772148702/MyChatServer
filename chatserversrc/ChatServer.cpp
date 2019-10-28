/**
 *  闁跨喐鏋婚幏鐑芥晸閺傘倖瀚归柨鐔告灮閹风兘鏁撻弬銈嗗闁跨喐鏋婚幏鐑芥晸閺傘倖瀚归柨鐔哥％閿涘瓥MServer.cpp
 *  zhangyl 2017.03.09
 **/
#include "ChatServer.h"

#include "../net/InetAddress.h"
#include "../base/AsyncLog.h"
#include "../base/Singleton.h"
#include "ChatSession.h"
#include "UserManager.h"

ChatServer::ChatServer()
{
    m_logPackageBinary = false;
}

bool ChatServer::Init(const char* ip, short port, EventLoop* loop)
{   
    InetAddress addr(ip, port);
    m_server.reset(new TcpServer(loop, addr, "FLAMINGO-SERVER", TcpServer::kReusePort));
    m_server->setConnectionCallback(std::bind(&ChatServer::OnConnection, this, std::placeholders::_1));
    //闁跨喐鏋婚幏鐑芥晸閺傘倖瀚归柨鐔告灮閹风兘鏁撻弬銈嗗
    m_server->start(6);

    return true;
}

void ChatServer::Uninit()
{
    if (m_server)
        m_server->stop();
}

void ChatServer::EnableLogPackageBinary(bool enable)
{
    m_logPackageBinary = enable;
}

bool ChatServer::IsLogPackageBinaryEnabled()
{
    return m_logPackageBinary;
}

void ChatServer::OnConnection(std::shared_ptr<TcpConnection> conn)
{
    if (conn->connected())
    {
        LOGD("client connected: %s", conn->peerAddress().toIpPort().c_str());
        ++m_sessionId;
        std::shared_ptr<ChatSession> spSession(new ChatSession(conn, m_sessionId));
        conn->setMessageCallback(std::bind(&ChatSession::OnRead, spSession.get(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));       

        std::lock_guard<std::mutex> guard(m_sessionMutex);
        m_sessions.push_back(spSession);
    }
    else
    {
        OnClose(conn);
    }
}

void ChatServer::OnClose(const std::shared_ptr<TcpConnection>& conn)
{
    //闁跨喕顫楅崙銈嗗闁跨喐鏋婚幏鐑芥晸閻偂绱幏鐑芥晸閺傘倖瀚归柨鐔告灮閹凤拷
    //bool bUserOffline = false;
    UserManager& userManager = Singleton<UserManager>::Instance();

    //TODO: 闁跨喐鏋婚幏鐑芥晸閺傘倖瀚归柨鐔惰寧鏉堢偓瀚归柨鐔告灮閹风兘鏁撶粩顓犮€嬮幏宄般亰闁跨喐鏋婚幏鐑芥晸閹活叏缍囬幏鐑芥晸閺傘倖瀚圭憰渚€鏁撻懘姘串閹凤拷
    std::lock_guard<std::mutex> guard(m_sessionMutex);
    for (auto iter = m_sessions.begin(); iter != m_sessions.end(); ++iter)
    {
        if ((*iter)->GetConnectionPtr() == NULL)
        {
            LOGE("connection is NULL");
            break;
        }
        
        //闁岸鏁撻弬銈嗗闁跨喖銈虹拋瑙勫connection闁跨喐鏋婚幏鐑芥晸閺傘倖瀚归柨鐔稿疆绾板瀚归柨鐔告灮閹峰嘲绨查柨鐔告灮閹风ession
        if ((*iter)->GetConnectionPtr() == conn)
        {
            //闁跨喐鏋婚幏绋磂ssion闁跨喐鏋婚幏鐑芥晸閺傘倖瀚规稊瀣闁跨喐鏋婚幏鐑芥晸閺傘倖瀚归柨鐔告灮閹风兘鏁撶粩顓狀暜閹风兘鏁撻弬銈嗗閺佸湯ession闁跨喐鏋婚幏鐑芥晸閺傘倖瀚归柨鐔告灮閹疯渹璐熼柨鐔告灮閹风兘鏁撻弬銈嗗闁跨喐鏋婚幏鐑芥晸閺傘倖瀚归柨鐔侯仾閿濆繑瀚归柨鐔诲壖闂堚晜瀚归柨鐔告灮閹风兘鏁撻弬銈嗗闁跨喐鏋婚幏鐑芥晸閺傘倖瀚归柨鐔告灮閹风兘鏁撻弬銈嗗闁跨喐鏋婚幏鐑芥晸閺傘倖瀚归柨鐔荤窛閿燂拷
            if ((*iter)->IsSessionValid())
            { 
                //闁跨喐鏋婚幏鐑芥晸閺傘倖瀚归柨鐔告灮閹风兘鏁撻弬銈嗗闁跨喓顏悮瀛樺闁跨喓鐛ら敐蹇斿闁跨喐鏋婚幏鐑芥晸閺傘倖瀚归柨鐔告灮閹风兘鏁撻弬銈嗗闁跨喐鏋婚幏鐑芥晸閺傘倖瀚归柨鐔告灮閹风兘鏁撻弬銈嗗闁跨喐鏋婚幏鐑芥晸鏉堝喛鎷�
                std::list<User> friends;
                int32_t offlineUserId = (*iter)->GetUserId();
                userManager.GetFriendInfoByUserId(offlineUserId, friends);
                for (const auto& iter2 : friends)
                {
                    for (auto& iter3 : m_sessions)
                    {
                        //闁跨喓鐓悮瀛樺闁跨喐鏋婚幏鐑芥晸鐟欐帒鍤栭幏鐑芥晸閺傘倖瀚归柨鐔侯仾閿濆繑瀚归柨鐔告灮閹风兘鏁撶粩顓濈串閹风兘鏁撻弬銈嗗闁跨喓姘甧ssion闁跨喐鏋婚幏锟�
                        if (iter2.userid == iter3->GetUserId())
                        {
                            iter3->SendUserStatusChangeMsg(offlineUserId, 2);

                            LOGI("SendUserStatusChangeMsg to user(userid=%d): user go offline, offline userid = %d", iter3->GetUserId(), offlineUserId);
                        }
                    }
                }
            }
            else
            {
                LOGI("Session is invalid, userid=%d", (*iter)->GetUserId());
            }
            
            //閸嬫粓鏁撻弬銈嗗闁跨喐鏋婚幏绋磂ssion闁跨喍鑼庣喊澶嬪闁跨喓顏涵閿嬪闁跨噦鎷�
            //(*iter)->DisableHeartbaetCheck();
            //闁跨喓鐓导娆愬闁跨喐鏋婚幏鐑芥晸閺傘倖瀚�
            m_sessions.erase(iter);
            //bUserOffline = true;
            LOGI("client disconnected: %s", conn->peerAddress().toIpPort().c_str());
            break;
        }
    }

    LOGI("current online user count: %d", (int)m_sessions.size());
}

void ChatServer::GetSessions(std::list<std::shared_ptr<ChatSession>>& sessions)
{
    std::lock_guard<std::mutex> guard(m_sessionMutex);
    sessions = m_sessions;
}

bool ChatServer::GetSessionByUserIdAndClientType(std::shared_ptr<ChatSession>& session, int32_t userid, int32_t clientType)
{
    std::lock_guard<std::mutex> guard(m_sessionMutex);
    std::shared_ptr<ChatSession> tmpSession;
    for (const auto& iter : m_sessions)
    {
        tmpSession = iter;
        if (iter->GetUserId() == userid && iter->GetClientType() == clientType)
        {
            session = tmpSession;
            return true;
        }
    }

    return false;
}

bool ChatServer::GetSessionsByUserId(std::list<std::shared_ptr<ChatSession>>& sessions, int32_t userid)
{
    std::lock_guard<std::mutex> guard(m_sessionMutex);
    std::shared_ptr<ChatSession> tmpSession;
    for (const auto& iter : m_sessions)
    {
        tmpSession = iter;
        if (iter->GetUserId() == userid)
        {
            sessions.push_back(tmpSession);
            return true;
        }
    }

    return false;
}

int32_t ChatServer::GetUserStatusByUserId(int32_t userid)
{
    std::lock_guard<std::mutex> guard(m_sessionMutex);
    for (const auto& iter : m_sessions)
    {
        if (iter->GetUserId() == userid)
        {
            return iter->GetUserStatus();
        }
    }

    return 0;
}

int32_t ChatServer::GetUserClientTypeByUserId(int32_t userid)
{
    std::lock_guard<std::mutex> guard(m_sessionMutex);
    bool bMobileOnline = false;
    int clientType = CLIENT_TYPE_UNKOWN;
    for (const auto& iter : m_sessions)
    {
        if (iter->GetUserId() == userid)
        {   
            clientType = iter->GetUserClientType();
         
            if (clientType == CLIENT_TYPE_PC)
                return clientType;
            else if (clientType == CLIENT_TYPE_ANDROID || clientType == CLIENT_TYPE_IOS)
                bMobileOnline = true;
        }
    }

    //閸欘亪鏁撻弬銈嗗闁跨喕顢滄导娆愬闁跨喐鏋婚幏鐑芥晸缁旑厽澧犻崙銈嗗闁跨喐鏋婚幏鐑芥晸鐞涙ぞ绱幏鐑芥晸閺傘倖瀚归柨鐔告灮閹烽濮搁幀锟�
    if (bMobileOnline)
        return clientType;

    return CLIENT_TYPE_UNKOWN;
}