/**
 * ChatSession.cpp
 * zhangyl, 2017.03.10
 **/
#include "ChatSession.h"
#include <string.h>
#include <sstream>
#include <list>
#include "../net/TcpConnection.h"
#include "../net/ProtocolStream.h"
#include "../base/AsyncLog.h"
#include "../base/Singleton.h"
#include "../jsoncpp1.9.0/json.h"
#include "Msg.h"
#include "UserManager.h"
#include "ChatServer.h"
#include "MsgCacheManager.h"
#include "../zlib1.2.11/ZlibUtil.h"
#include "BussinessLogic.h"

//锟斤拷锟斤拷锟斤拷纸锟斤拷锟斤拷锟斤拷锟轿�10M
#define MAX_PACKAGE_SIZE    10 * 1024 * 1024

using namespace std;
using namespace net;

//锟斤拷锟斤拷锟斤拷锟斤拷锟绞憋拷锟斤拷莅锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟矫筹拷30锟斤拷
#define MAX_NO_PACKAGE_INTERVAL  30

ChatSession::ChatSession(const std::shared_ptr<TcpConnection>& conn, int sessionid) :
TcpSession(conn), 
m_id(sessionid),
m_seq(0),
m_isLogin(false)
{
	m_userinfo.userid = 0;
    m_lastPackageTime = time(NULL);

//#ifndef _DEBUG
    //锟斤拷锟斤拷注锟酵碉拷锟斤拷锟斤拷锟斤拷锟节碉拷锟斤拷
    //EnableHearbeatCheck();
//#endif
}

ChatSession::~ChatSession()
{
    std::shared_ptr<TcpConnection> conn = GetConnectionPtr();
    if (conn)
    {
        LOGI("remove check online timerId, userid: %d, clientType: %d, client address: %s", m_userinfo.userid, m_userinfo.clienttype, conn->peerAddress().toIpPort().c_str());
        conn->getLoop()->remove(m_checkOnlineTimerId);
    }
}

void ChatSession::OnRead(const std::shared_ptr<TcpConnection>& conn, Buffer* pBuffer, Timestamp receivTime)
{
    while (true)
    {
        //锟斤拷锟斤拷一锟斤拷锟斤拷头锟斤拷小
        if (pBuffer->readableBytes() < (size_t)sizeof(msg))
        {
            //LOGI << "buffer is not enough for a package header, pBuffer->readableBytes()=" << pBuffer->readableBytes() << ", sizeof(msg)=" << sizeof(msg);
            return;
        }

        //取锟斤拷头锟斤拷息
        msg header;
        memcpy(&header, pBuffer->peek(), sizeof(msg));
        //锟斤拷锟捷帮拷压锟斤拷锟斤拷
        if (header.compressflag == PACKAGE_COMPRESSED)
        {
            //锟斤拷头锟叫达拷锟斤拷锟斤拷锟斤拷锟截憋拷锟斤拷锟斤拷
            if (header.compresssize <= 0 || header.compresssize > MAX_PACKAGE_SIZE ||
                header.originsize <= 0 || header.originsize > MAX_PACKAGE_SIZE)
            {
                //锟酵伙拷锟剿凤拷锟角凤拷锟斤拷锟捷帮拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟截憋拷之
                LOGE("Illegal package, compresssize: %lld, originsize: %lld, , close TcpConnection, client: %s",  header.compresssize, header.originsize, conn->peerAddress().toIpPort().c_str());
                conn->forceClose();
                return;
            }

            //锟秸碉拷锟斤拷锟斤拷锟捷诧拷锟斤拷一锟斤拷锟斤拷锟斤拷锟侥帮拷
            if (pBuffer->readableBytes() < (size_t)header.compresssize + sizeof(msg))
                return;

            pBuffer->retrieve(sizeof(msg));
            std::string inbuf;
            inbuf.append(pBuffer->peek(), header.compresssize);
            pBuffer->retrieve(header.compresssize);
            std::string destbuf;
            if (!ZlibUtil::UncompressBuf(inbuf, destbuf, header.originsize))
            {
                LOGE("uncompress error, client: %s", conn->peerAddress().toIpPort().c_str());
                conn->forceClose();
                return;
            }

            if (!Process(conn, destbuf.c_str(), destbuf.length()))
            {
                //锟酵伙拷锟剿凤拷锟角凤拷锟斤拷锟捷帮拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟截憋拷之
                LOGE("Process error, close TcpConnection, client: %s", conn->peerAddress().toIpPort().c_str());
                conn->forceClose();
                return;
            }

            m_lastPackageTime = time(NULL);
        }
        //锟斤拷锟捷帮拷未压锟斤拷
        else
        {
            //锟斤拷头锟叫达拷锟斤拷锟斤拷锟斤拷锟截憋拷锟斤拷锟斤拷
            if (header.originsize <= 0 || header.originsize > MAX_PACKAGE_SIZE)
            {
                //锟酵伙拷锟剿凤拷锟角凤拷锟斤拷锟捷帮拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟截憋拷之
                LOGE("Illegal package, compresssize: %lld, originsize: %lld, , close TcpConnection, client: %s", header.compresssize, header.originsize, conn->peerAddress().toIpPort().c_str());
                conn->forceClose();
                return;
            }

            //锟秸碉拷锟斤拷锟斤拷锟捷诧拷锟斤拷一锟斤拷锟斤拷锟斤拷锟侥帮拷
            if (pBuffer->readableBytes() < (size_t)header.originsize + sizeof(msg))
                return;

            pBuffer->retrieve(sizeof(msg));
            std::string inbuf;
            inbuf.append(pBuffer->peek(), header.originsize);
            pBuffer->retrieve(header.originsize);
            if (!Process(conn, inbuf.c_str(), inbuf.length()))
            {
                //锟酵伙拷锟剿凤拷锟角凤拷锟斤拷锟捷帮拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟截憋拷之
                LOGE("Process error, close TcpConnection, client: %s", conn->peerAddress().toIpPort().c_str());
                conn->forceClose();
                return;
            }
                
            m_lastPackageTime = time(NULL);
        }// end else

    }// end while-loop

}

bool ChatSession::Process(const std::shared_ptr<TcpConnection>& conn, const char* inbuf, size_t buflength)
{   
    BinaryReadStream readStream(inbuf, buflength);
    int32_t cmd;
    if (!readStream.ReadInt32(cmd))
    {
        LOGE("read cmd error, client: %s", conn->peerAddress().toIpPort().c_str());
        return false;
    }

    //int seq;
    if (!readStream.ReadInt32(m_seq))
    {
        LOGE("read seq error, client: %s", conn->peerAddress().toIpPort().c_str());
        return false;
    }

    std::string data;
    size_t datalength;
    if (!readStream.ReadString(&data, 0, datalength))
    {
        LOGE("read data error, client: %s", conn->peerAddress().toIpPort().c_str());
        return false;
    }
   
    //锟斤拷锟斤拷锟斤拷太频锟斤拷锟斤拷锟斤拷锟斤拷印
    if (cmd != msg_type_heartbeat)
        LOGI("Request from client: userid=%d, cmd=%d, seq=%d, data=%s, datalength=%d, buflength=%d", m_userinfo.userid, cmd, m_seq, data.c_str(), datalength, buflength);
    
    if (Singleton<ChatServer>::Instance().IsLogPackageBinaryEnabled())
    {
        LOGI("body stream, buflength: %d, client: %s", buflength, conn->peerAddress().toIpPort().c_str());
        //LOG_DEBUG_BIN((unsigned char*)inbuf, buflength);
    }
        
    switch (cmd)
    {
        //锟斤拷锟斤拷锟斤拷
        case msg_type_heartbeat:
            OnHeartbeatResponse(conn);
            break;

        //注锟斤拷
        case msg_type_register:
            OnRegisterResponse(data, conn);
            break;
        
        //锟斤拷录
        case msg_type_login:                          
            OnLoginResponse(data, conn);
            break;
        
        //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷丫锟斤拷锟铰硷拷锟角帮拷锟斤拷虏锟斤拷芙锟斤拷胁锟斤拷锟�
        default:
        {
            if (m_isLogin)
            {
                switch (cmd)
                {
                    //锟斤拷取锟斤拷锟斤拷锟叫憋拷
                    case msg_type_getofriendlist:
                        OnGetFriendListResponse(conn);
                        break;

                    //锟斤拷锟斤拷锟矫伙拷
                    case msg_type_finduser:
                        OnFindUserResponse(data, conn);
                        break;

                    //锟接猴拷锟斤拷
                    case msg_type_operatefriend:    
                        OnOperateFriendResponse(data, conn);
                        break;

                    //锟矫伙拷锟斤拷锟斤拷锟斤拷锟斤拷锟皆硷拷锟斤拷锟斤拷状态
                    case msg_type_userstatuschange:
        	            OnChangeUserStatusResponse(data, conn);
                        break;

                    //锟斤拷锟斤拷锟矫伙拷锟斤拷息
                    case msg_type_updateuserinfo:
                        OnUpdateUserInfoResponse(data, conn);
                        break;
        
                    //锟睫革拷锟斤拷锟斤拷
                    case msg_type_modifypassword:
                        OnModifyPasswordResponse(data, conn);
                        break;
        
                    //锟斤拷锟斤拷群
                    case msg_type_creategroup:
                        OnCreateGroupResponse(data, conn);
                        break;

                    //锟斤拷取指锟斤拷群锟斤拷员锟斤拷息
                    case msg_type_getgroupmembers:
                        OnGetGroupMembersResponse(data, conn);
                        break;

                    //锟斤拷锟斤拷锟斤拷息
                    case msg_type_chat:
                    {
                        int32_t target;
                        if (!readStream.ReadInt32(target))
                        {
                            LOGE("read target error, client: %s", conn->peerAddress().toIpPort().c_str());
                            return false;
                        }
                        OnChatResponse(target, data, conn);
                    }
                        break;
        
                    //群锟斤拷锟斤拷息
                    case msg_type_multichat:
                    {
                        std::string targets;
                        size_t targetslength;
                        if (!readStream.ReadString(&targets, 0, targetslength))
                        {
                            LOGE("read targets error, client: %s", conn->peerAddress().toIpPort().c_str());
                            return false;
                        }

                        OnMultiChatResponse(targets, data, conn);
                    }

                        break;

                    //锟斤拷幕锟斤拷图
                    case msg_type_remotedesktop:
                    {
                        string bmpHeader;
                        size_t bmpHeaderlength;
                        if (!readStream.ReadString(&bmpHeader, 0, bmpHeaderlength))
                        {
                            LOGE("read bmpheader error, client: %s", conn->peerAddress().toIpPort().c_str());
                            return false;
                        }

                        string bmpData;
                        size_t bmpDatalength;
                        if (!readStream.ReadString(&bmpData, 0, bmpDatalength))
                        {
                            LOGE("read bmpdata error, client: %s", conn->peerAddress().toIpPort().c_str());
                            return false;
                        }
                                   
                        int32_t target;
                        if (!readStream.ReadInt32(target))
                        {
                            LOGE("read target error, client: %s", conn->peerAddress().toIpPort().c_str());
                            return false;
                        }
                        OnScreenshotResponse(target, bmpHeader, bmpData, conn);
                    }
                        break;

                    //锟斤拷锟斤拷锟矫伙拷锟斤拷锟斤拷锟斤拷息
                    case msg_type_updateteaminfo:
                    {
                        int32_t operationType;
                        if (!readStream.ReadInt32(operationType))
                        {
                            LOGE("read operationType error, client: %s", conn->peerAddress().toIpPort().c_str());
                            return false;
                        }

                        string newTeamName;
                        size_t newTeamNameLength;
                        if (!readStream.ReadString(&newTeamName, 0, newTeamNameLength))
                        {
                            LOGE("read newTeamName error, client: %s", conn->peerAddress().toIpPort().c_str());
                            return false;
                        }

                        string oldTeamName;
                        size_t oldTeamNameLength;
                        if (!readStream.ReadString(&oldTeamName, 0, oldTeamNameLength))
                        {
                            LOGE("read newTeamName error, client: %s", conn->peerAddress().toIpPort().c_str());
                            return false;
                        }
                        
                        OnUpdateTeamInfoResponse(operationType, newTeamName, oldTeamName, conn);
                        break;
                    }
                        
                    //锟睫改猴拷锟窖憋拷注锟斤拷息
                    case msg_type_modifyfriendmarkname:
                    {
                        int32_t friendid;
                        if (!readStream.ReadInt32(friendid))
                        {
                            LOGE("read friendid error, client: %s", conn->peerAddress().toIpPort().c_str());
                            return false;
                        }

                        string newmarkname;
                        size_t newmarknamelength;
                        if (!readStream.ReadString(&newmarkname, 0, newmarknamelength))
                        {
                            LOGE("read newmarkname error, client: %s", conn->peerAddress().toIpPort().c_str());
                            return false;
                        }

                        OnModifyMarknameResponse(friendid, newmarkname, conn);
                        break;
                    }
                    
                    //锟狡讹拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
                    case msg_type_movefriendtootherteam:
                    {
                        int32_t friendid;
                        if (!readStream.ReadInt32(friendid))
                        {
                            LOGE("read friendid error, client: %s", conn->peerAddress().toIpPort().c_str());
                            return false;
                        }

                        string newteamname;
                        size_t newteamnamelength;
                        if (!readStream.ReadString(&newteamname, 0, newteamnamelength))
                        {
                            LOGE("read newteamname error, client: %s", conn->peerAddress().toIpPort().c_str());
                            return false;
                        }

                        string oldteamname;
                        size_t oldteamnamelength;
                        if (!readStream.ReadString(&oldteamname, 0, oldteamnamelength))
                        {
                            LOGE("read oldteamname error, client: %s", conn->peerAddress().toIpPort().c_str());
                            return false;
                        }

                        OnMoveFriendToOtherTeamResponse(friendid, newteamname, oldteamname, conn);
                    }
                        break;                      

                    default:
                        //pBuffer->retrieveAll();
                        LOGE("unsupport cmd, cmd: %d, data=%s, connection name:", cmd, data.c_str(), conn->peerAddress().toIpPort().c_str());
                        //conn->forceClose();
                        return false;
                }// end inner-switch
            }
            else
            {
                //锟矫伙拷未锟斤拷录锟斤拷锟斤拷锟竭客伙拷锟剿诧拷锟杰斤拷锟叫诧拷锟斤拷锟斤拷示锟斤拷未锟斤拷录锟斤拷
                std::string data = "{\"code\": 2, \"msg\": \"not login, please login first!\"}";
                Send(cmd, m_seq, data);
                LOGI("Response to client: cmd=%d, , data=%s, , sessionId=%d", cmd, data.c_str(), m_id);                
            }// end if
         }// end default
    }// end outer-switch

    ++ m_seq;

    return true;
}

void ChatSession::OnHeartbeatResponse(const std::shared_ptr<TcpConnection>& conn)
{
    std::string dummydata;    
    Send(msg_type_heartbeat, m_seq, dummydata);

    //锟斤拷锟斤拷锟斤拷锟斤拷志锟酵诧拷要锟斤拷印锟剿ｏ拷锟斤拷锟斤拷锟斤拷写锟斤拷锟斤拷志
    //LOGI << "Response to client: cmd=1000" << ", sessionId=" << m_id;
}

void ChatSession::OnRegisterResponse(const std::string& data, const std::shared_ptr<TcpConnection>& conn)
{
    string retData;
    BussinessLogic::RegisterUser(data, conn, true, retData);

    if (!retData.empty())
    {
        Send(msg_type_register, m_seq, retData);

        LOGI("Response to client: cmd=msg_type_register, data: %s. client: %s", retData.c_str(), conn->peerAddress().toIpPort().c_str());
    }
}

void ChatSession::OnLoginResponse(const std::string& data, const std::shared_ptr<TcpConnection>& conn)
{
    //{"username": "13917043329", "password": "123", "clienttype": 1, "status": 1}
    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value jsonRoot;
    JSONCPP_STRING errs;
    bool ok = reader->parse(data.c_str(), data.c_str() + data.length(), &jsonRoot, &errs);
    if (!ok || errs.size() != 0)
    {
        LOGE("invalid json: %s, sessionId: %d, client: %s", data.c_str(), m_id, conn->peerAddress().toIpPort().c_str());
        delete reader;
        return;
    }
    delete reader;

    if (!jsonRoot["username"].isString() || !jsonRoot["password"].isString() || !jsonRoot["clienttype"].isInt() || !jsonRoot["status"].isInt())
    {
        LOGE("invalid json: %s, sessionId: %d, client: %s", data.c_str(), m_id, conn->peerAddress().toIpPort().c_str());
        return;
    }

    string username = jsonRoot["username"].asString();
    string password = jsonRoot["password"].asString();
    int clientType = jsonRoot["clienttype"].asInt();
    std::ostringstream os;
    User cachedUser;
    cachedUser.userid = 0;
    Singleton<UserManager>::Instance().GetUserInfoByUsername(username, cachedUser);
    ChatServer& imserver = Singleton<ChatServer>::Instance();
    if (cachedUser.userid == 0)
    {
        //TODO: 锟斤拷些硬锟斤拷锟斤拷锟斤拷址锟接︼拷锟酵骋伙拷诺锟侥筹拷锟斤拷胤锟酵骋伙拷锟斤拷锟�
        os << "{\"code\": 102, \"msg\": \"not registered\"}";
    }
    else
    {
        if (cachedUser.password != password)
            os << "{\"code\": 103, \"msg\": \"incorrect password\"}";
        else
        {
            //锟斤拷锟斤拷锟斤拷撕锟斤拷丫锟斤拷锟铰硷拷锟斤拷锟角耙伙拷锟斤拷撕锟斤拷锟斤拷锟斤拷锟�
            std::shared_ptr<ChatSession> targetSession;
            //锟斤拷锟节凤拷锟斤拷锟斤拷锟斤拷支锟街讹拷锟斤拷锟斤拷锟秸端碉拷录锟斤拷锟斤拷锟斤拷只锟斤拷同一锟斤拷锟酵碉拷锟秸讹拷锟斤拷同一锟酵伙拷锟斤拷锟斤拷锟酵诧拷锟斤拷为锟斤拷同一锟斤拷session
            imserver.GetSessionByUserIdAndClientType(targetSession, cachedUser.userid, clientType);
            if (targetSession)
            {                              
                string dummydata;
                targetSession->Send(msg_type_kickuser, m_seq, dummydata);
                //锟斤拷锟斤拷锟斤拷锟竭碉拷Session锟斤拷锟轿拷锟叫э拷锟�
                targetSession->MakeSessionInvalid();

                LOGI("Response to client, userid: %d, cmd=msg_type_kickuser", targetSession->GetUserId());

                //锟截憋拷锟斤拷锟斤拷
                //targetSession->GetConnectionPtr()->forceClose();
            }           
            
            //锟斤拷录锟矫伙拷锟斤拷息
            m_userinfo.userid = cachedUser.userid;
            m_userinfo.username = username;
            m_userinfo.nickname = cachedUser.nickname;
            m_userinfo.password = password;
            m_userinfo.clienttype = jsonRoot["clienttype"].asInt();
            m_userinfo.status = jsonRoot["status"].asInt();

            os << "{\"code\": 0, \"msg\": \"ok\", \"userid\": " << m_userinfo.userid << ",\"username\":\"" << cachedUser.username << "\", \"nickname\":\"" 
               << cachedUser.nickname << "\", \"facetype\": " << cachedUser.facetype << ", \"customface\":\"" << cachedUser.customface << "\", \"gender\":" << cachedUser.gender
               << ", \"birthday\":" << cachedUser.birthday << ", \"signature\":\"" << cachedUser.signature << "\", \"address\": \"" << cachedUser.address
               << "\", \"phonenumber\": \"" << cachedUser.phonenumber << "\", \"mail\":\"" << cachedUser.mail << "\"}";            
        }
    }
   
    //锟斤拷录锟斤拷息应锟斤拷
    Send(msg_type_login, m_seq, os.str());

    LOGI("Response to client: cmd=msg_type_login, data=%s, userid=", os.str().c_str(), m_userinfo.userid);

    //锟斤拷锟斤拷锟窖撅拷锟斤拷录锟侥憋拷志
    m_isLogin = true;

    //锟斤拷锟斤拷锟斤拷锟斤拷通知锟斤拷息
    std::list<NotifyMsgCache> listNotifyCache;
    Singleton<MsgCacheManager>::Instance().GetNotifyMsgCache(m_userinfo.userid, listNotifyCache);
    for (const auto &iter : listNotifyCache)
    {
        Send(iter.notifymsg);
    }

    //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷息
    std::list<ChatMsgCache> listChatCache;
    Singleton<MsgCacheManager>::Instance().GetChatMsgCache(m_userinfo.userid, listChatCache);
    for (const auto &iter : listChatCache)
    {
        Send(iter.chatmsg);
    }

    //锟斤拷锟斤拷锟斤拷锟矫伙拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷息
    std::list<User> friends;
    Singleton<UserManager>::Instance().GetFriendInfoByUserId(m_userinfo.userid, friends);
    for (const auto& iter : friends)
    {
        //锟斤拷为锟斤拷锟斤拷一锟斤拷锟矫伙拷id锟斤拷锟斤拷锟斤拷斩耍锟斤拷锟斤拷裕锟酵伙拷锟絬serid锟斤拷锟杰讹拷应锟斤拷锟絪ession
        std::list<std::shared_ptr<ChatSession>> sessions;
        imserver.GetSessionsByUserId(sessions, iter.userid);
        for (auto& iter2 : sessions)
        {
            if (iter2)
            {
                iter2->SendUserStatusChangeMsg(m_userinfo.userid, 1, m_userinfo.status);

                LOGI("SendUserStatusChangeMsg to user(userid: %d): user go online, online userid: %d, status: %d", iter2->GetUserId(), m_userinfo.userid, m_userinfo.status);
            }
        }
    }  
}

void ChatSession::OnGetFriendListResponse(const std::shared_ptr<TcpConnection>& conn)
{
    std::string friendlist;
    MakeUpFriendListInfo(friendlist, conn);
    std::ostringstream os;
    os << "{\"code\": 0, \"msg\": \"ok\", \"userinfo\":" << friendlist << "}";
    Send(msg_type_getofriendlist, m_seq, os.str());

    LOGI("Response to client: userid: %d, cmd=msg_type_getofriendlist, data: %s", m_userinfo.userid, os.str().c_str());    
}

void ChatSession::OnChangeUserStatusResponse(const std::string& data, const std::shared_ptr<TcpConnection>& conn)
{
    //{"type": 1, "onlinestatus" : 1}
    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value jsonRoot;
    JSONCPP_STRING errs;
    bool ok = reader->parse(data.c_str(), data.c_str() + data.length(), &jsonRoot, &errs);
    if (!ok || errs.size() != 0)
    {
        LOGE("invalid json: %s, userid: %d, client: %s", data.c_str(), m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
        delete reader;
        return;
    }
    delete reader;

    if (!jsonRoot["type"].isInt() || !jsonRoot["onlinestatus"].isInt())
    {
        LOGE("invalid json: %s, userid: %d, client: %s", data.c_str(), m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
        return;
    }

    int newstatus = jsonRoot["onlinestatus"].asInt();
    if (m_userinfo.status == newstatus)
        return;

    //锟斤拷锟斤拷锟铰碉拷前锟矫伙拷锟斤拷状态
    m_userinfo.status = newstatus;

    //TODO: 应锟斤拷锟斤拷锟皆硷拷锟斤拷锟竭客伙拷锟斤拷锟睫改成癸拷

    ChatServer& imserver = Singleton<ChatServer>::Instance();
    std::list<User> friends;
    Singleton<UserManager>::Instance().GetFriendInfoByUserId(m_userinfo.userid, friends);
    for (const auto& iter : friends)
    {
        //锟斤拷为锟斤拷锟斤拷一锟斤拷锟矫伙拷id锟斤拷锟斤拷锟斤拷斩耍锟斤拷锟斤拷裕锟酵伙拷锟絬serid锟斤拷锟杰讹拷应锟斤拷锟絪ession
        std::list<std::shared_ptr<ChatSession>> sessions;
        imserver.GetSessionsByUserId(sessions, iter.userid);
        for (auto& iter2 : sessions)
        {
            if (iter2)
                iter2->SendUserStatusChangeMsg(m_userinfo.userid, 1, newstatus);
        }
    }
}

void ChatSession::OnFindUserResponse(const std::string& data, const std::shared_ptr<TcpConnection>& conn)
{
    //{ "type": 1, "username" : "zhangyl" }
    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value jsonRoot;
    JSONCPP_STRING errs;
    bool ok = reader->parse(data.c_str(), data.c_str() + data.length(), &jsonRoot, &errs);
    if (!ok || errs.size() != 0)
    {
        LOGE("invalid json: %s, userid: %d, client: %s", data.c_str(), m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
        delete reader;
        return;
    }
    delete reader;
   
    if (!jsonRoot["type"].isInt() || !jsonRoot["username"].isString())
    {
        LOGE("invalid json: %s, userid: %d, client: %s", data.c_str(), m_userinfo.userid, conn->peerAddress().toIpPort().c_str());       
        return;
    }

    string retData;
    //TODO: 目前只支锟街诧拷锟揭碉拷锟斤拷锟矫伙拷
    string username = jsonRoot["username"].asString();
    User cachedUser;
    if (!Singleton<UserManager>::Instance().GetUserInfoByUsername(username, cachedUser))
        retData = "{ \"code\": 0, \"msg\": \"ok\", \"userinfo\": [] }";
    else
    {
        //TODO: 锟矫伙拷锟饺较讹拷锟绞憋拷锟接︼拷锟绞癸拷枚锟教瑂tring
        char szUserInfo[256] = { 0 };
        snprintf(szUserInfo, 256, "{ \"code\": 0, \"msg\": \"ok\", \"userinfo\": [{\"userid\": %d, \"username\": \"%s\", \"nickname\": \"%s\", \"facetype\":%d}] }", cachedUser.userid, cachedUser.username.c_str(), cachedUser.nickname.c_str(), cachedUser.facetype);
        retData = szUserInfo;
    } 

    Send(msg_type_finduser, m_seq, retData);

    LOGI("Response to client: userid: %d, cmd=msg_type_finduser, data: %s", m_userinfo.userid, retData.c_str());
}

void ChatSession::OnOperateFriendResponse(const std::string& data, const std::shared_ptr<TcpConnection>& conn)
{
    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value jsonRoot;
    JSONCPP_STRING errs;
    bool ok = reader->parse(data.c_str(), data.c_str() + data.length(), &jsonRoot, &errs);
    if (!ok || errs.size() != 0)
    {
        LOGE("invalid json: %s, userid: %d, client: %s", data.c_str(), m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
        delete reader;
        return;
    }
    delete reader;

    if (!jsonRoot["type"].isInt() || !jsonRoot["userid"].isInt())
    {
        LOGE("invalid json: %s, userid: %d, client: %s", data.c_str(), m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
        return;
    }

    int type = jsonRoot["type"].asInt();
    int32_t targetUserid = jsonRoot["userid"].asInt();
    if (targetUserid >= GROUPID_BOUBDARY)
    {
        if (type == 4)
        {
            //锟斤拷群
            DeleteFriend(conn, targetUserid);
            return;
        }

        if (Singleton<UserManager>::Instance().IsFriend(m_userinfo.userid, targetUserid))
        {            
            LOGE("In group already, unable to join in group, groupid: %d, , userid: %d, , client: %s",  targetUserid, m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
            //TODO: 通知锟铰客伙拷锟斤拷
            return;
        }

        //锟斤拷群直锟斤拷同锟斤拷
        OnAddGroupResponse(targetUserid, conn);
        return;
    }

    char szData[256] = { 0 };
    //删锟斤拷锟斤拷锟斤拷
    if (type == 4)
    {
        DeleteFriend(conn, targetUserid);
        return;
    }
    //锟斤拷锟斤拷锟接猴拷锟斤拷锟斤拷锟斤拷
    if (type == 1)
    {
        if (Singleton<UserManager>::Instance().IsFriend(m_userinfo.userid, targetUserid))
        {
            LOGE("Friendship already, unable to add friend, friendid: %d, userid: %d, client: %s", targetUserid, m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
            //TODO: 通知锟铰客伙拷锟斤拷
            return;
        }
        
        //{"userid": 9, "type": 1, }        
        snprintf(szData, 256, "{\"userid\":%d, \"type\":2, \"username\": \"%s\"}", m_userinfo.userid, m_userinfo.username.c_str());
    }
    //应锟斤拷雍锟斤拷锟�
    else if (type == 3)
    {
        if (!jsonRoot["accept"].isInt())
        {
            LOGE("invalid json: %s, userid: %d, client: %s", data.c_str(), m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
            return;
        }

        int accept = jsonRoot["accept"].asInt();
        //锟斤拷锟杰加猴拷锟斤拷锟斤拷锟斤拷螅锟斤拷锟斤拷锟斤拷压锟较�
        if (accept == 1)
        {
            if (!Singleton<UserManager>::Instance().MakeFriendRelationshipInDB(targetUserid, m_userinfo.userid))
            {
                LOGE("make relationship error: %s, userid: %d, client:  %s", data.c_str(), m_userinfo.userid,  conn->peerAddress().toIpPort().c_str());
                return;
            }

            if (!Singleton<UserManager>::Instance().UpdateUserRelationshipInMemory(m_userinfo.userid, targetUserid, FRIEND_OPERATION_ADD))
            {
                LOGE("UpdateUserTeamInfo error: %s, , userid: %d, client: %s", data.c_str(), m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
                return;
            }
        }

        //{ "userid": 9, "type" : 3, "userid" : 9, "username" : "xxx", "accept" : 1 }
        snprintf(szData, 256, "{\"userid\": %d, \"type\": 3, \"username\": \"%s\", \"accept\": %d}", m_userinfo.userid, m_userinfo.username.c_str(), accept);

        //锟斤拷示锟皆硷拷锟斤拷前锟矫伙拷锟接猴拷锟窖成癸拷
        User targetUser;
        if (!Singleton<UserManager>::Instance().GetUserInfoByUserId(targetUserid, targetUser))
        {
            LOGE("Get Userinfo by id error, targetuserid: %d, userid: %d, data: %s, client: %s", targetUserid, m_userinfo.userid, data.c_str(), conn->peerAddress().toIpPort().c_str());
            return;
        }
        char szSelfData[256] = { 0 };
        snprintf(szSelfData, 256, "{\"userid\": %d, \"type\": 3, \"username\": \"%s\", \"accept\": %d}", targetUser.userid, targetUser.username.c_str(), accept);
        Send(msg_type_operatefriend, m_seq, szSelfData, strlen(szSelfData));
        LOGI("Response to client: userid: %d, cmd=msg_type_addfriend, data: %s", m_userinfo.userid, szSelfData);
    }

    //锟斤拷示锟皆凤拷锟接猴拷锟窖成癸拷
    std::string outbuf;
    BinaryWriteStream writeStream(&outbuf);
    writeStream.WriteInt32(msg_type_operatefriend);
    writeStream.WriteInt32(m_seq);
    writeStream.WriteCString(szData, strlen(szData));
    writeStream.Flush();

    //锟饺匡拷目锟斤拷锟矫伙拷锟角凤拷锟斤拷锟斤拷
    std::list<std::shared_ptr<ChatSession>> sessions;
    Singleton<ChatServer>::Instance().GetSessionsByUserId(sessions, targetUserid);
    //目锟斤拷锟矫伙拷锟斤拷锟斤拷锟竭ｏ拷锟斤拷锟斤拷锟斤拷锟斤拷锟较�
    if (sessions.empty())
    {
        Singleton<MsgCacheManager>::Instance().AddNotifyMsgCache(targetUserid, outbuf);
        LOGI("userid: %d, is not online, cache notify msg, msg: %s", targetUserid, outbuf.c_str());
        return;
    }

    for (auto& iter : sessions)
    {
        iter->Send(outbuf);
    }

    LOGI("Response to client: userid: %d, cmd=msg_type_addfriend, data: %s", targetUserid, data.c_str());
}

void ChatSession::OnAddGroupResponse(int32_t groupId, const std::shared_ptr<TcpConnection>& conn)
{
    if (!Singleton<UserManager>::Instance().MakeFriendRelationshipInDB(m_userinfo.userid, groupId))
    {
        LOGE("make relationship error, groupId: %d, userid: %d, client: %s", groupId, m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
        return;
    }
    
    User groupUser;
    if (!Singleton<UserManager>::Instance().GetUserInfoByUserId(groupId, groupUser))
    {
        LOGE("Get group info by id error, targetuserid: %d, userid: %d, client: %s", groupId, m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
        return;
    }
    char szSelfData[256] = { 0 };
    snprintf(szSelfData, 256, "{\"userid\": %d, \"type\": 3, \"username\": \"%s\", \"accept\": 3}", groupUser.userid, groupUser.username.c_str());
    Send(msg_type_operatefriend, m_seq, szSelfData, strlen(szSelfData));
    LOGI("Response to client: cmd=msg_type_addfriend, data: %s, userid: %d", szSelfData, m_userinfo.userid);

    if (!Singleton<UserManager>::Instance().UpdateUserRelationshipInMemory(m_userinfo.userid, groupId, FRIEND_OPERATION_ADD))
    {
        LOGE("UpdateUserTeamInfo error, targetUserid: %d, userid: %d, client: %s", groupId, m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
        return;
    }

    //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷群锟斤拷员锟斤拷锟斤拷群锟斤拷息锟斤拷锟斤拷锟戒化锟斤拷锟斤拷息
    std::list<User> friends;
    Singleton<UserManager>::Instance().GetFriendInfoByUserId(groupId, friends);
    ChatServer& imserver = Singleton<ChatServer>::Instance();
    for (const auto& iter : friends)
    {
        //锟饺匡拷目锟斤拷锟矫伙拷锟角凤拷锟斤拷锟斤拷
        std::list< std::shared_ptr<ChatSession>> targetSessions;
        imserver.GetSessionsByUserId(targetSessions, iter.userid);
        for (auto& iter2 : targetSessions)
        {
            if (iter2)
                iter2->SendUserStatusChangeMsg(groupId, 3);
        }
    }
}

void ChatSession::OnUpdateUserInfoResponse(const std::string& data, const std::shared_ptr<TcpConnection>& conn)
{
    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value jsonRoot;
    JSONCPP_STRING errs;
    bool ok = reader->parse(data.c_str(), data.c_str() + data.length(), &jsonRoot, &errs);
    if (!ok || errs.size() != 0)
    {
        LOGE("invalid json: %s, userid: %d, client: %s", data.c_str(), m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
        delete reader;
        return;
    }
    delete reader;
    
    if (!jsonRoot["nickname"].isString() || !jsonRoot["facetype"].isInt() || 
        !jsonRoot["customface"].isString() || !jsonRoot["gender"].isInt() || 
        !jsonRoot["birthday"].isInt() || !jsonRoot["signature"].isString() || 
        !jsonRoot["address"].isString() || !jsonRoot["phonenumber"].isString() || 
        !jsonRoot["mail"].isString())
    {
        LOGE("invalid json: %s, userid: %d, client: %s", data.c_str(), m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
        return;
    }

    User newuserinfo;
    newuserinfo.nickname = jsonRoot["nickname"].asString();
    newuserinfo.facetype = jsonRoot["facetype"].asInt();
    newuserinfo.customface = jsonRoot["customface"].asString();
    newuserinfo.gender = jsonRoot["gender"].asInt();
    newuserinfo.birthday = jsonRoot["birthday"].asInt();
    newuserinfo.signature = jsonRoot["signature"].asString();
    newuserinfo.address = jsonRoot["address"].asString();
    newuserinfo.phonenumber = jsonRoot["phonenumber"].asString();
    newuserinfo.mail = jsonRoot["mail"].asString();
    
    ostringstream retdata;
    ostringstream currentuserinfo;
    if (!Singleton<UserManager>::Instance().UpdateUserInfoInDb(m_userinfo.userid, newuserinfo))
    {
        retdata << "{ \"code\": 104, \"msg\": \"update user info failed\" }";
    }
    else
    {
        /*
        { "code": 0, "msg" : "ok", "userid" : 2, "username" : "xxxx", 
         "nickname":"zzz", "facetype" : 26, "customface" : "", "gender" : 0, "birthday" : 19900101, 
         "signature" : "xxxx", "address": "", "phonenumber": "", "mail":""}
        */
        currentuserinfo << "\"userid\": " << m_userinfo.userid << ",\"username\":\"" << m_userinfo.username
                        << "\", \"nickname\":\"" << newuserinfo.nickname
                        << "\", \"facetype\": " << newuserinfo.facetype << ", \"customface\":\"" << newuserinfo.customface
                        << "\", \"gender\":" << newuserinfo.gender
                        << ", \"birthday\":" << newuserinfo.birthday << ", \"signature\":\"" << newuserinfo.signature
                        << "\", \"address\": \"" << newuserinfo.address
                        << "\", \"phonenumber\": \"" << newuserinfo.phonenumber << "\", \"mail\":\""
                        << newuserinfo.mail;
        retdata << "{\"code\": 0, \"msg\": \"ok\"," << currentuserinfo.str()  << "\"}";
    }

    //应锟斤拷突锟斤拷锟�
    Send(msg_type_updateuserinfo, m_seq, retdata.str());

    LOGI("Response to client: userid: %d, cmd=msg_type_updateuserinfo, data: %s", m_userinfo.userid, retdata.str().c_str());

    //锟斤拷锟斤拷锟斤拷锟斤拷锟竭猴拷锟斤拷锟斤拷锟酵革拷锟斤拷锟斤拷息锟斤拷锟斤拷锟侥憋拷锟斤拷息
    std::list<User> friends;
    Singleton<UserManager>::Instance().GetFriendInfoByUserId(m_userinfo.userid, friends);
    ChatServer& imserver = Singleton<ChatServer>::Instance();
    for (const auto& iter : friends)
    {
        //锟饺匡拷目锟斤拷锟矫伙拷锟角凤拷锟斤拷锟斤拷
        std::list<std::shared_ptr<ChatSession>> targetSessions;
        imserver.GetSessionsByUserId(targetSessions, iter.userid);
        for (auto& iter2 : targetSessions)
        {
            if (iter2)
                iter2->SendUserStatusChangeMsg(m_userinfo.userid, 3);
        }
    }
}

void ChatSession::OnModifyPasswordResponse(const std::string& data, const std::shared_ptr<TcpConnection>& conn)
{    
    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value jsonRoot;
    JSONCPP_STRING errs;
    bool ok = reader->parse(data.c_str(), data.c_str() + data.length(), &jsonRoot, &errs);
    if (!ok || errs.size() != 0)
    {
        LOGE("invalid json: %s, userid: %d, client: %s", data.c_str(), m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
        delete reader;
        return;
    }
    delete reader;
    
    if (!jsonRoot["oldpassword"].isString() || !jsonRoot["newpassword"].isString())
    {
        LOGE("invalid json: %s, userid: %d, client: %s", data.c_str(), m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
        return;
    }

    string oldpass = jsonRoot["oldpassword"].asString();
    string newPass = jsonRoot["newpassword"].asString();

    string retdata;
    User cachedUser;
    if (!Singleton<UserManager>::Instance().GetUserInfoByUserId(m_userinfo.userid, cachedUser))
    {
        LOGE("get userinfo error, userid: %d, data: %s, client: %s", m_userinfo.userid, data.c_str(), conn->peerAddress().toIpPort().c_str());
        return;
    }

    if (cachedUser.password != oldpass)
    {
        retdata = "{\"code\": 103, \"msg\": \"incorrect old password\"}";
    }
    else
    {       
        if (!Singleton<UserManager>::Instance().ModifyUserPassword(m_userinfo.userid, newPass))
        {
            retdata = "{\"code\": 105, \"msg\": \"modify password error\"}";
            LOGE("modify password error, userid: %d, data:%s, client: %s", m_userinfo.userid, data.c_str(), conn->peerAddress().toIpPort().c_str());
        }
        else
            retdata = "{\"code\": 0, \"msg\": \"ok\"}";
    }

    //应锟斤拷突锟斤拷锟�
    Send(msg_type_modifypassword, m_seq, retdata);

    LOGI("Response to client: userid: %d, cmd=msg_type_modifypassword, data: %s", m_userinfo.userid, data.c_str());
}

void ChatSession::OnCreateGroupResponse(const std::string& data, const std::shared_ptr<TcpConnection>& conn)
{
    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value jsonRoot;
    JSONCPP_STRING errs;
    bool ok = reader->parse(data.c_str(), data.c_str() + data.length(), &jsonRoot, &errs);
    if (!ok || errs.size() != 0)
    {
        LOGE("invalid json: %s, userid: %d, client: %s", data.c_str(), m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
        delete reader;
        return;
    }
    delete reader;

    if (!jsonRoot["groupname"].isString())
    {
        LOGE("invalid json: %s, userid: %d, client: %s", data.c_str(), m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
        return;
    }

    ostringstream retdata;
    string groupname = jsonRoot["groupname"].asString();
    int32_t groupid;
    if (!Singleton<UserManager>::Instance().AddGroup(groupname.c_str(), m_userinfo.userid, groupid))
    {
        LOGE("Add group error, data: %s, userid: %d, client: %s", data.c_str(), m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
        retdata << "{ \"code\": 106, \"msg\" : \"create group error\"}";
    }
    else
    {
        retdata << "{\"code\": 0, \"msg\": \"ok\", \"groupid\":" << groupid << ", \"groupname\": \"" << groupname << "\"}";
    }

    //TODO: 锟斤拷锟斤拷锟斤拷锟�1锟缴癸拷锟剿ｏ拷锟斤拷锟斤拷2失锟斤拷锟斤拷锟斤拷么锟届？
    //锟斤拷锟斤拷1
    //锟斤拷锟斤拷锟缴癸拷锟皆猴拷锟斤拷没锟斤拷远锟斤拷锟饺�
    if (!Singleton<UserManager>::Instance().MakeFriendRelationshipInDB(m_userinfo.userid, groupid))
    {
        LOGE("join in group, errordata: %s, userid: %d, client: %s", data.c_str(), m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
        return;
    }

    //锟斤拷锟斤拷锟节达拷锟叫的猴拷锟窖癸拷系
    //锟斤拷锟斤拷2
    if (!Singleton<UserManager>::Instance().UpdateUserRelationshipInMemory(m_userinfo.userid, groupid, FRIEND_OPERATION_ADD))
    {
        LOGE("UpdateUserTeamInfo error, data: %s, userid: %d, client: %s", data.c_str(), m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
        return;
    }
    
    //if (!Singleton<UserManager>::Instance().UpdateUserTeamInfo(groupid, m_userinfo.userid, FRIEND_OPERATION_ADD))
    //{
    //    LOGE << "UpdateUserTeamInfo error, data: " << data << ", userid: " << m_userinfo.userid << ", client: " << conn->peerAddress().toIpPort();
    //    return;
    //}


    //应锟斤拷突锟斤拷耍锟斤拷锟饺猴拷晒锟�
    Send(msg_type_creategroup, m_seq, retdata.str());

    LOGI("Response to client: userid: %d, cmd=msg_type_creategroup, data: %s", m_userinfo.userid, retdata.str().c_str());

    //应锟斤拷突锟斤拷耍锟斤拷晒锟斤拷锟饺�
    {
        char szSelfData[256] = { 0 };
        snprintf(szSelfData, 256, "{\"userid\": %d, \"type\": 3, \"username\": \"%s\", \"accept\": 1}", groupid, groupname.c_str());
        Send(msg_type_operatefriend, m_seq, szSelfData, strlen(szSelfData));
        LOGI("Response to client, userid: %d, cmd=msg_type_addfriend, data: %s", m_userinfo.userid, szSelfData);
    }
}

void ChatSession::OnGetGroupMembersResponse(const std::string& data, const std::shared_ptr<TcpConnection>& conn)
{
    //{"groupid": 群id}
    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value jsonRoot;
    JSONCPP_STRING errs;
    bool ok = reader->parse(data.c_str(), data.c_str() + data.length(), &jsonRoot, &errs);
    if (!ok || errs.size() != 0)
    {
        LOGE("invalid json: %s, userid: %d, client: %s", data.c_str(), m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
        delete reader;
        return;
    }
    delete reader;
    
    if (!jsonRoot["groupid"].isInt())
    {
        LOGE("invalid json: %s, userid: %d, client: %s", data.c_str(), m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
        return;
    }

    int32_t groupid = jsonRoot["groupid"].asInt();
    
    std::list<User> friends;
    Singleton<UserManager>::Instance().GetFriendInfoByUserId(groupid, friends);
    std::string strUserInfo;
    int userOnline = 0;
    ChatServer& imserver = Singleton<ChatServer>::Instance();
    for (const auto& iter : friends)
    {
        userOnline = imserver.GetUserStatusByUserId(iter.userid);
        /*
        {"code": 0, "msg": "ok", "members":[{"userid": 1,"username":"qqq,
        "nickname":"qqq, "facetype": 0, "customface":"", "gender":0, "birthday":19900101,
        "signature":", "address": "", "phonenumber": "", "mail":", "clienttype": 1, "status":1"]}
        */
        ostringstream osSingleUserInfo;
        osSingleUserInfo << "{\"userid\": " << iter.userid << ", \"username\":\"" << iter.username << "\", \"nickname\":\"" << iter.nickname
            << "\", \"facetype\": " << iter.facetype << ", \"customface\":\"" << iter.customface << "\", \"gender\":" << iter.gender
            << ", \"birthday\":" << iter.birthday << ", \"signature\":\"" << iter.signature << "\", \"address\": \"" << iter.address
            << "\", \"phonenumber\": \"" << iter.phonenumber << "\", \"mail\":\"" << iter.mail << "\", \"clienttype\": 1, \"status\":"
            << userOnline << "}";

        strUserInfo += osSingleUserInfo.str();
        strUserInfo += ",";
    }
    //去锟斤拷锟斤拷锟斤拷锟斤拷亩锟斤拷锟�
    strUserInfo = strUserInfo.substr(0, strUserInfo.length() - 1);
    std::ostringstream os;
    os << "{\"code\": 0, \"msg\": \"ok\", \"groupid\": " << groupid << ", \"members\":[" << strUserInfo << "]}";
    Send(msg_type_getgroupmembers, m_seq, os.str());

    LOGI("Response to client: userid: %d, cmd=msg_type_getgroupmembers, data: %s", m_userinfo.userid, os.str().c_str());
}

void ChatSession::SendUserStatusChangeMsg(int32_t userid, int type, int status/* = 0*/)
{
    string data; 
    //锟矫伙拷锟斤拷锟斤拷
    if (type == 1)
    {
        int32_t clientType = Singleton<ChatServer>::Instance().GetUserClientTypeByUserId(userid);
        char szData[64];
        memset(szData, 0, sizeof(szData));
        sprintf(szData, "{ \"type\": 1, \"onlinestatus\": %d, \"clienttype\": %d}", status, clientType);
        data = szData;
    }
    //锟矫伙拷锟斤拷锟斤拷
    else if (type == 2)
    {
        data = "{\"type\": 2, \"onlinestatus\": 0}";
    }
    //锟斤拷锟斤拷锟角称★拷头锟斤拷签锟斤拷锟斤拷锟斤拷息锟斤拷锟斤拷
    else if (type == 3)
    {
        data = "{\"type\": 3}";
    }

    std::string outbuf;
    BinaryWriteStream writeStream(&outbuf);
    writeStream.WriteInt32(msg_type_userstatuschange);
    writeStream.WriteInt32(m_seq);
    writeStream.WriteString(data);
    writeStream.WriteInt32(userid);
    writeStream.Flush();

    Send(outbuf);

    LOGI("Send to client: userid: %d, cmd=msg_type_userstatuschange, data: %s", m_userinfo.userid, data.c_str());
}

void ChatSession::MakeSessionInvalid()
{
    m_userinfo.userid = 0;
}

bool ChatSession::IsSessionValid()
{
    return m_userinfo.userid > 0;
}

void ChatSession::OnChatResponse(int32_t targetid, const std::string& data, const std::shared_ptr<TcpConnection>& conn)
{
    std::string modifiedChatData;
    if (!ModifyChatMsgLocalTimeToServerTime(data, modifiedChatData))
    {
        LOGE("invalid chat json, chatjson: %s, senderid: %d, targetid: %d, chatmsg: %s, client: %s", data.c_str(), m_userinfo.userid, targetid, data.c_str(), conn->peerAddress().toIpPort().c_str());
        return;
    }
    
    std::string outbuf;
    BinaryWriteStream writeStream(&outbuf);
    writeStream.WriteInt32(msg_type_chat);
    writeStream.WriteInt32(m_seq);
    writeStream.WriteString(modifiedChatData);
    //锟斤拷息锟斤拷锟斤拷锟斤拷
    writeStream.WriteInt32(m_userinfo.userid);
    //锟斤拷息锟斤拷锟斤拷锟斤拷
    writeStream.WriteInt32(targetid);
    writeStream.Flush();

    UserManager& userMgr = Singleton<UserManager>::Instance();
    //写锟斤拷锟斤拷息锟斤拷录
    if (!userMgr.SaveChatMsgToDb(m_userinfo.userid, targetid, data))
    {
        LOGE("Write chat msg to db error, senderid: %d, targetid: %d, chatmsg: %s, client: %s", m_userinfo.userid, targetid, data.c_str(), conn->peerAddress().toIpPort().c_str());
    }

    ChatServer& imserver = Singleton<ChatServer>::Instance();
    MsgCacheManager& msgCacheMgr = Singleton<MsgCacheManager>::Instance();
    //锟斤拷锟斤拷锟斤拷息
    if (targetid < GROUPID_BOUBDARY)
    {
        //锟饺匡拷目锟斤拷锟矫伙拷锟角凤拷锟斤拷锟斤拷
        std::list<std::shared_ptr<ChatSession>> targetSessions;
        imserver.GetSessionsByUserId(targetSessions, targetid);
        //目锟斤拷锟矫伙拷锟斤拷锟斤拷锟竭ｏ拷锟斤拷锟斤拷锟斤拷锟斤拷锟较�
        if (targetSessions.empty())
        {
            msgCacheMgr.AddChatMsgCache(targetid, outbuf);
        }
        else
        {
            for (auto& iter : targetSessions)
            {
                if (iter)
                    iter->Send(outbuf);
            }
        }
    }
    //群锟斤拷锟斤拷息
    else
    {       
        std::list<User> friends;
        userMgr.GetFriendInfoByUserId(targetid, friends);
        std::string strUserInfo;
        bool userOnline = false;
        for (const auto& iter : friends)
        {
            //锟脚筹拷群锟斤拷员锟叫碉拷锟皆硷拷
            if (iter.userid == m_userinfo.userid)
                continue;

            //锟饺匡拷目锟斤拷锟矫伙拷锟角凤拷锟斤拷锟斤拷
            std::list<std::shared_ptr<ChatSession>> targetSessions;
            imserver.GetSessionsByUserId(targetSessions, iter.userid);
            //目锟斤拷锟矫伙拷锟斤拷锟斤拷锟竭ｏ拷锟斤拷锟斤拷锟斤拷锟斤拷锟较�
            if (targetSessions.empty())
            {
                msgCacheMgr.AddChatMsgCache(iter.userid, outbuf);
                continue;
            }
            else
            {
                for (auto& iter2 : targetSessions)
                {
                    if (iter2)
                        iter2->Send(outbuf);
                }
            }
        }
    }   
}

void ChatSession::OnMultiChatResponse(const std::string& targets, const std::string& data, const std::shared_ptr<TcpConnection>& conn)
{
    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value jsonRoot;
    JSONCPP_STRING errs;
    bool ok = reader->parse(targets.c_str(), targets.c_str() + targets.length(), &jsonRoot, &errs);
    if (!ok || errs.size() != 0)
    {
        LOGE("invalid targets string: targets: %s, data: %s, userid: %d, , client: %s", targets.c_str(), data.c_str(), m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
        delete reader;
        return;
    }
    delete reader;    

    if (!jsonRoot["targets"].isArray())
    {
        LOGE("[targets] node is not array in targets string: targets: %s, data: %s, userid: %d, client: %s", targets.c_str(), data.c_str(), m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
        return;
    }

    for (uint32_t i = 0; i < jsonRoot["targets"].size(); ++i)
    {
        OnChatResponse(jsonRoot["targets"][i].asInt(), data, conn);
    }

    LOGI("Send to client, cmd=msg_type_multichat, targets: %s, data: %s, from userid: %d, from client: %s", targets.c_str(), data.c_str(), m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
}

void ChatSession::OnScreenshotResponse(int32_t targetid, const std::string& bmpHeader, const std::string& bmpData, const std::shared_ptr<TcpConnection>& conn)
{
    std::string outbuf;
    BinaryWriteStream writeStream(&outbuf);
    writeStream.WriteInt32(msg_type_remotedesktop);
    writeStream.WriteInt32(m_seq);
    std::string dummy;
    writeStream.WriteString(dummy);
    writeStream.WriteString(bmpHeader);
    writeStream.WriteString(bmpData);
    //锟斤拷息锟斤拷锟斤拷锟斤拷
    writeStream.WriteInt32(targetid);
    writeStream.Flush();

    ChatServer& imserver = Singleton<ChatServer>::Instance();
    //锟斤拷锟斤拷锟斤拷息
    if (targetid >= GROUPID_BOUBDARY)
        return;

    std::list<std::shared_ptr<ChatSession>> targetSessions;
    imserver.GetSessionsByUserId(targetSessions, targetid);
    //锟饺匡拷目锟斤拷锟矫伙拷锟斤拷锟竭诧拷转锟斤拷
    if (!targetSessions.empty())
    {
        for (auto& iter : targetSessions)
        {
            if (iter)
                iter->Send(outbuf);
        }
    }
}

void ChatSession::OnUpdateTeamInfoResponse(int32_t operationType, const std::string& newTeamName, const std::string& oldTeamName, const std::shared_ptr<TcpConnection>& conn)
{
    if (operationType < updateteaminfo_operation_add || operationType > updateteaminfo_operation_modify)
    {
        LOGE("invalid teaminfo, userid: %d, , client: %s", m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
        return;
    }
    
    string teaminfo;
    if (!Singleton<UserManager>::Instance().GetTeamInfoByUserId(m_userinfo.userid, teaminfo))
    {
        LOGE("GetTeamInfoByUserId failed, userid: %d, client: %s", m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
        //TODO: 应锟斤拷应锟斤拷一锟铰客伙拷锟斤拷
        return;
    }

    if (teaminfo.empty())
    {
        teaminfo = "[{\"teamname\": \"";
        teaminfo += DEFAULT_TEAMNAME;
        teaminfo += "\", \"members\":[]}]";
    }

    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value jsonRoot;
    JSONCPP_STRING errs;
    bool ok = reader->parse(teaminfo.c_str(), teaminfo.c_str() + teaminfo.length(), &jsonRoot, &errs);
    if (!ok || errs.size() != 0)
    {
        //TODO: 应锟斤拷应锟斤拷一锟铰客伙拷锟斤拷
        LOGE("parse teaminfo json failed, userid: %d, client: %s", m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
        delete reader;
        return;
    }
    delete reader;

    string newTeamInfo;

    //锟斤拷锟斤拷锟斤拷锟斤拷
    if (operationType == updateteaminfo_operation_add)
    {
        uint32_t teamCount = jsonRoot.size();
        for (uint32_t i = 0; i < teamCount; ++i)
        {
            if (!jsonRoot[i]["teamname"].isNull() && jsonRoot[i]["teamname"].asString() == newTeamName)
            {
                //TODO: 锟斤拷示锟酵伙拷锟剿凤拷锟斤拷锟窖撅拷锟斤拷锟斤拷
                LOGE("teamname not exist, userid: %d, client: %s", m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
                return;
            }
        }
        
        jsonRoot[teamCount]["teamname"] = newTeamName;
        Json::Value emptyArrayValue(Json::arrayValue);
        jsonRoot[teamCount]["members"] = emptyArrayValue;

        //Json::FastWriter writer;
        //newTeamInfo = writer.write(JsonRoot);

        Json::StreamWriterBuilder streamWriterBuilder;
        //锟斤拷锟斤拷json锟叫碉拷\t锟斤拷\n锟斤拷锟斤拷
        streamWriterBuilder.settings_["indentation"] = "";
        newTeamInfo = Json::writeString(streamWriterBuilder, jsonRoot);      
    }
    else if (operationType == updateteaminfo_operation_delete)
    {
        if (oldTeamName == DEFAULT_TEAMNAME)
        {
            //默锟较凤拷锟介不锟斤拷锟斤拷删锟斤拷
            //TODO: 锟斤拷示锟酵伙拷锟斤拷
            return;
        }
        
        bool found = false;
        uint32_t teamCount = jsonRoot.size();
        for (uint32_t i = 0; i < teamCount; ++i)
        {
            if (!jsonRoot[i]["teamname"].isNull() && jsonRoot[i]["teamname"].asString() == oldTeamName)
            {
                found = true;
                //TODO锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
                jsonRoot.removeIndex(i, &jsonRoot[i]["teamname"]);

                //锟斤拷锟斤拷锟捷匡拷锟叫革拷锟斤拷暮锟斤拷锟斤拷贫锟斤拷锟侥拷戏锟斤拷锟�
                if (!Singleton<UserManager>::Instance().DeleteTeam(m_userinfo.userid, oldTeamName))
                {
                    LOGE("Delete team error, oldTeamName: %s, userid: %s, client: %s", oldTeamName.c_str(), m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
                    return;
                }
                          
                break;
            }
        }

        if (!found)
        {
            //锟斤拷示锟酵伙拷锟剿凤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
            LOGE("teamname not exist, userid: %d, client: %s", m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
        }

        //Json::FastWriter writer;
        //newTeamInfo = writer.write(JsonRoot);

        Json::StreamWriterBuilder streamWriterBuilder;
        //锟斤拷锟斤拷json锟叫碉拷\t锟斤拷\n锟斤拷锟斤拷
        streamWriterBuilder.settings_["indentation"] = "";
        newTeamInfo = Json::writeString(streamWriterBuilder, jsonRoot);
    }
    //锟睫改凤拷锟斤拷锟斤拷
    else
    {
        if (oldTeamName == DEFAULT_TEAMNAME)
        {
            //默锟较凤拷锟介不锟斤拷锟斤拷锟睫革拷
            //TODO: 锟斤拷示锟酵伙拷锟斤拷
            return;
        }
        
        //锟睫改凤拷锟斤拷锟斤拷
        bool found = false;
        uint32_t teamCount = jsonRoot.size();
        for (uint32_t i = 0; i < teamCount; ++i)
        {
            if (!jsonRoot[i]["teamname"].isNull() && jsonRoot[i]["teamname"].asString() == oldTeamName)
            {
                found = true;
                jsonRoot[i]["teamname"] = newTeamName;
              
                break;
            }
        }

        if (!found)
        {
            //锟斤拷示锟酵伙拷锟剿凤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
        }

        if (!Singleton<UserManager>::Instance().ModifyTeamName(m_userinfo.userid, newTeamName, oldTeamName))
        {
            LOGE("Update team info failed, userid: %d, newTeamInfo: %s, oldTeamInfo: %s, client: %s", m_userinfo.userid, newTeamInfo.c_str(), oldTeamName.c_str(), conn->peerAddress().toIpPort().c_str());
            return;
        }

        //Json::FastWriter writer;
        //newTeamInfo = writer.write(JsonRoot);

        Json::StreamWriterBuilder streamWriterBuilder;
        streamWriterBuilder.settings_["indentation"] = "";
        newTeamInfo = Json::writeString(streamWriterBuilder, jsonRoot);
    }
 
    //锟斤拷锟芥到锟斤拷锟捷匡拷锟斤拷锟斤拷去锟斤拷锟斤拷锟斤拷锟斤拷息锟斤拷锟斤拷锟酵革拷锟斤拷锟节达拷锟叫的凤拷锟斤拷锟斤拷息
    if (!Singleton<UserManager>::Instance().UpdateUserTeamInfoInDbAndMemory(m_userinfo.userid, newTeamInfo))
    {
        //TODO: 失锟斤拷应锟斤拷突锟斤拷锟�
        LOGE("Update team info failed, userid: %d, , newTeamInfo: %s, , client: %s", m_userinfo.userid, newTeamInfo.c_str(), conn->peerAddress().toIpPort().c_str());
        return;
    }

    std::string friendinfo;
    MakeUpFriendListInfo(friendinfo, conn);

    std::ostringstream os;
    os << "{\"code\": 0, \"msg\": \"ok\", \"userinfo\":" << friendinfo << "}";
    Send(msg_type_getofriendlist, m_seq, os.str());

    LOGI("Response to client, userid: %d, cmd=msg_type_getofriendlist, data: %s", m_userinfo.userid, os.str().c_str());
}

void ChatSession::OnModifyMarknameResponse(int32_t friendid, const std::string& newmarkname, const std::shared_ptr<TcpConnection>& conn)
{
    if (!Singleton<UserManager>::Instance().UpdateMarknameInDb(m_userinfo.userid, friendid, newmarkname))
    {
        //TODO: 失锟斤拷应锟斤拷突锟斤拷锟�
        LOGE("Update markname failed, userid: %d, friendid: %d, client: %s", m_userinfo.userid, friendid, conn->peerAddress().toIpPort().c_str());
        return;
    }

    std::string friendinfo;
    MakeUpFriendListInfo(friendinfo, conn);

    std::ostringstream os;
    os << "{\"code\": 0, \"msg\": \"ok\", \"userinfo\":" << friendinfo << "}";
    Send(msg_type_getofriendlist, m_seq, os.str());

    LOGI("Response to client, userid: %d, cmd=msg_type_getofriendlist, data: %s", m_userinfo.userid, os.str().c_str());
}

void ChatSession::OnMoveFriendToOtherTeamResponse(int32_t friendid, const std::string& newteamname, const std::string& oldteamname, const std::shared_ptr<TcpConnection>& conn)
{
    if (newteamname.empty() || oldteamname.empty() || newteamname == oldteamname)
    {
        LOGE("Failed to move to other team, newteamname or oldteamname is invalid, userid: %d, friendid:%d, client: %s", m_userinfo.userid, friendid, conn->peerAddress().toIpPort().c_str());
        //TODO: 通知锟酵伙拷锟斤拷
        return;
    }
    
    //锟斤拷锟斤拷锟斤拷暮锟斤拷眩锟斤拷锟斤拷懿锟斤拷锟�
    if (!Singleton<UserManager>::Instance().IsFriend(m_userinfo.userid, friendid))
    {
        LOGE("Failed to move to other team, not your friend, userid: %d, friendid: %d, client: %s", m_userinfo.userid, friendid, conn->peerAddress().toIpPort().c_str());
        //TODO: 通知锟酵伙拷锟斤拷
        return;
    }

    User currentUser;
    if (!Singleton<UserManager>::Instance().GetUserInfoByUserId(m_userinfo.userid, currentUser))
    {
        LOGE("User not exist in memory, userid: %d", m_userinfo.userid);
        //TODO: 通知锟酵伙拷锟斤拷
        return;
    }

    string teaminfo = currentUser.teaminfo;
    if (teaminfo.empty())
    {
        teaminfo = "[\"teamname\":\"";
        teaminfo += DEFAULT_TEAMNAME;
        teaminfo += "\"]";
    }

    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value jsonRoot;
    JSONCPP_STRING errs;
    bool ok = reader->parse(teaminfo.c_str(), teaminfo.c_str() + teaminfo.length(), &jsonRoot, &errs);
    if (!ok || errs.size() != 0)
    {
        LOGE("parse teaminfo json failed, userid: %d, teaminfo: %s, client: %s", m_userinfo.userid, teaminfo.c_str(), conn->peerAddress().toIpPort().c_str());
        delete reader;
        return;
    }
    delete reader;

    if (!jsonRoot.isArray())
    {
        LOGE("parse teaminfo json failed, userid: %d, teaminfo: %s, client: %s",  m_userinfo.userid, teaminfo.c_str(), conn->peerAddress().toIpPort().c_str());
        return;
    }

    bool foundNewTeam = false;
    bool foundOldTeam = false;
    for (uint32_t i = 0; i < jsonRoot.size(); ++i)
    {
        if (jsonRoot[i]["teamname"].isString())
        {
            if (jsonRoot[i]["teamname"].asString() == newteamname)
            {
                foundNewTeam = true;
                continue;
            }
            else if (jsonRoot[i]["teamname"].asString() == oldteamname)
            {
                foundOldTeam = true;
                continue;
            }
        }
    }

    if (!foundNewTeam || !foundOldTeam)
    {
        LOGE("Failed to move to other team, oldTeamName or newTeamName not exist, userid: %d, friendid: %d, oldTeamName: %s, newTeamName: %s, client: %s", 
            m_userinfo.userid, friendid, oldteamname.c_str(), newteamname.c_str(), conn->peerAddress().toIpPort().c_str());       
        return;
    }

    if (!Singleton<UserManager>::Instance().MoveFriendToOtherTeam(m_userinfo.userid, friendid, newteamname))
    {
        LOGE("Failed to MoveFriendToOtherTeam, db operation error, userid: %d, friendid: %d, client: %s", m_userinfo.userid, friendid, conn->peerAddress().toIpPort().c_str());
        return;
    }
    
    std::string friendinfo;
    MakeUpFriendListInfo(friendinfo, conn);

    std::ostringstream os;
    os << "{\"code\": 0, \"msg\": \"ok\", \"userinfo\":" << friendinfo << "}";
    Send(msg_type_getofriendlist, m_seq, os.str());

    LOGI("Response to client: userid: %d, cmd=msg_type_getofriendlist, data: %s", m_userinfo.userid, os.str().c_str());
}

void ChatSession::DeleteFriend(const std::shared_ptr<TcpConnection>& conn, int32_t friendid)
{
    /**
    *  锟斤拷锟斤拷锟斤拷锟窖ｏ拷锟斤拷锟斤拷锟接猴拷锟窖★拷删锟斤拷锟斤拷锟斤拷
    **/
    /*
    //type为1锟斤拷锟斤拷锟接猴拷锟斤拷锟斤拷锟斤拷 2 锟秸碉拷锟接猴拷锟斤拷锟斤拷锟斤拷(锟斤拷锟酵伙拷锟斤拷使锟斤拷) 3应锟斤拷雍锟斤拷锟� 4删锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷 5应锟斤拷删锟斤拷锟斤拷锟斤拷
    //锟斤拷type=3时锟斤拷accept锟角憋拷锟斤拷锟街段ｏ拷0锟皆凤拷锟杰撅拷锟斤拷1锟皆凤拷锟斤拷锟斤拷
    cmd = 1005, seq = 0, {"userid": 9, "type": 1}
    cmd = 1005, seq = 0, {"userid": 9, "type": 2, "username": "xxx"}
    cmd = 1005, seq = 0, {"userid": 9, "type": 3, "username": "xxx", "accept": 1}

    //锟斤拷锟斤拷
    cmd = 1005, seq = 0, {"userid": 9, "type": 4}
    //应锟斤拷
    cmd = 1005, seq = 0, {"userid": 9, "type": 5, "username": "xxx"}
    **/

    if (!Singleton<UserManager>::Instance().ReleaseFriendRelationshipInDBAndMemory(friendid, m_userinfo.userid))
    {
        LOGE("Delete friend error, friendid: %d, userid: %d, client: %d", friendid, m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
        return;
    }

    //锟斤拷锟斤拷一锟铰碉拷前锟矫伙拷锟侥凤拷锟斤拷锟斤拷息
    User cachedUser;
    if (!Singleton<UserManager>::Instance().GetUserInfoByUserId(friendid, cachedUser))
    {
        LOGE("Delete friend - Get user error, friendid: %d, userid: %d, client: %s", friendid, m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
        return;
    }

    if (!Singleton<UserManager>::Instance().UpdateUserRelationshipInMemory(m_userinfo.userid, friendid, FRIEND_OPERATION_DELETE))
    {
        LOGE("UpdateUserTeamInfo failed, friendid: %d, userid: %d, client: %s", friendid, m_userinfo.userid, conn->peerAddress().toIpPort().c_str());
        return;
    }
    
    char szData[256] = { 0 };
    //锟斤拷锟斤拷锟斤拷锟斤拷删锟斤拷锟斤拷一锟斤拷
    //{"userid": 9, "type": 1, }        
    snprintf(szData, 256, "{\"userid\":%d, \"type\":5, \"username\": \"%s\"}", friendid, cachedUser.username.c_str());
    Send(msg_type_operatefriend, m_seq, szData, strlen(szData));

    LOGI("Send to client: userid锟斤拷 %d, cmd=msg_type_operatefriend, data: %s", m_userinfo.userid, szData);

    //锟斤拷锟斤拷锟斤拷删锟斤拷锟斤拷一锟斤拷
    //删锟斤拷锟斤拷锟斤拷锟斤拷息
    if (friendid < GROUPID_BOUBDARY)
    {
        //锟饺匡拷目锟斤拷锟矫伙拷锟角凤拷锟斤拷锟斤拷
        std::list<std::shared_ptr<ChatSession>>targetSessions;
        Singleton<ChatServer>::Instance().GetSessionsByUserId(targetSessions, friendid);
        //锟斤拷锟斤拷锟斤拷锟斤拷锟矫伙拷锟斤拷锟斤拷锟斤拷锟斤拷锟较�
        if (!targetSessions.empty())
        {
            memset(szData, 0, sizeof(szData));
            snprintf(szData, 256, "{\"userid\":%d, \"type\":5, \"username\": \"%s\"}", m_userinfo.userid, m_userinfo.username.c_str());
            for (auto& iter : targetSessions)
            {
                if (iter)
                    iter->Send(msg_type_operatefriend, m_seq, szData, strlen(szData));
            }

            LOGI("Send to client: userid: %d, cmd=msg_type_operatefriend, data: %s", friendid, szData);
        }

        return;
    }
    
    //锟斤拷群锟斤拷息
    //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷群锟斤拷员锟斤拷锟斤拷群锟斤拷息锟斤拷锟斤拷锟戒化锟斤拷锟斤拷息
    std::list<User> friends;
    Singleton<UserManager>::Instance().GetFriendInfoByUserId(friendid, friends);
    ChatServer& imserver = Singleton<ChatServer>::Instance();
    for (const auto& iter : friends)
    {
        //锟饺匡拷目锟斤拷锟矫伙拷锟角凤拷锟斤拷锟斤拷
        std::list<std::shared_ptr<ChatSession>> targetSessions;
        imserver.GetSessionsByUserId(targetSessions, iter.userid);
        if (!targetSessions.empty())
        {
            for (auto& iter2 : targetSessions)
            {
                if (iter2)
                    iter2->SendUserStatusChangeMsg(friendid, 3);
            }
        }
    }

}

void ChatSession::MakeUpFriendListInfo(std::string& friendinfo, const std::shared_ptr<TcpConnection>& conn)
{
    std::string teaminfo;
    UserManager& userManager = Singleton<UserManager>::Instance();
    ChatServer& imserver = Singleton<ChatServer>::Instance();
    userManager.GetTeamInfoByUserId(m_userinfo.userid, teaminfo);

    /*
    [
    {
    "teamindex": 0,
    "teamname": "锟揭的猴拷锟斤拷",
    "members": [
    {
    "userid": 1,
    
    },
    {
    "userid": 2,
    "markname": "锟斤拷xx"
    }
    ]
    }
    ]
    */

    string markname = "";
    if (teaminfo.empty())
    {
        teaminfo = "[{\"teamname\": \"";
        teaminfo += DEFAULT_TEAMNAME;
        teaminfo += "\", \"members\": []}]";
    }
           
    Json::Value emptyArrayValue(Json::arrayValue);

    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value jsonRoot;
    JSONCPP_STRING errs;
    bool ok = reader->parse(teaminfo.c_str(), teaminfo.c_str() + teaminfo.length(), &jsonRoot, &errs);
    if (!ok || errs.size() != 0)
    {
        LOGE("parse teaminfo json failed, userid: %d, teaminfo: %s, client: %s", m_userinfo.userid, teaminfo.c_str(), conn->peerAddress().toIpPort().c_str());
        delete reader;
        return;
    }
    delete reader;

    if (!jsonRoot.isArray())
    {
        LOGE("parse teaminfo json failed, userid: %d, teaminfo: %s, client: %s", m_userinfo.userid, teaminfo.c_str(),  conn->peerAddress().toIpPort().c_str());
        return;
    }

    // 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷息锟斤拷锟斤拷锟接猴拷锟斤拷锟斤拷锟斤拷锟斤拷息
    uint32_t teamCount = jsonRoot.size();
    int32_t userid = 0;

    //std::list<User> friends;
    User currentUserInfo;
    userManager.GetUserInfoByUserId(m_userinfo.userid, currentUserInfo);
    User u;
    for (auto& friendinfo : currentUserInfo.friends)
    {
        for (uint32_t i = 0; i < teamCount; ++i)
        {
            if (jsonRoot[i]["members"].isNull() || !(jsonRoot[i]["members"]).isArray())
            {
                jsonRoot[i]["members"] = emptyArrayValue;
            }

            if (jsonRoot[i]["teamname"].isNull() || jsonRoot[i]["teamname"].asString() != friendinfo.teamname)
                continue;
            
            uint32_t memberCount = jsonRoot[i]["members"].size();
                                            
            if (!userManager.GetUserInfoByUserId(friendinfo.friendid, u))
                continue;

            if (!userManager.GetFriendMarknameByUserId(m_userinfo.userid, friendinfo.friendid, markname))
                continue;

            jsonRoot[i]["members"][memberCount]["userid"] = u.userid;
            jsonRoot[i]["members"][memberCount]["username"] = u.username;
            jsonRoot[i]["members"][memberCount]["nickname"] = u.nickname;
            jsonRoot[i]["members"][memberCount]["markname"] = markname;
            jsonRoot[i]["members"][memberCount]["facetype"] = u.facetype;
            jsonRoot[i]["members"][memberCount]["customface"] = u.customface;
            jsonRoot[i]["members"][memberCount]["gender"] = u.gender;
            jsonRoot[i]["members"][memberCount]["birthday"] = u.birthday;
            jsonRoot[i]["members"][memberCount]["signature"] = u.signature;
            jsonRoot[i]["members"][memberCount]["address"] = u.address;
            jsonRoot[i]["members"][memberCount]["phonenumber"] = u.phonenumber;
            jsonRoot[i]["members"][memberCount]["mail"] = u.mail;
            jsonRoot[i]["members"][memberCount]["clienttype"] = imserver.GetUserClientTypeByUserId(friendinfo.friendid);
            jsonRoot[i]["members"][memberCount]["status"] = imserver.GetUserStatusByUserId(friendinfo.friendid);;
       }// end inner for-loop
        
    }// end outer for - loop

    //JsonRoot.toStyledString()锟斤拷锟截碉拷锟角革拷式锟斤拷锟矫碉拷json锟斤拷锟斤拷实锟斤拷
    //friendinfo = JsonRoot.toStyledString();
    //Json::FastWriter writer;
    //friendinfo = writer.write(JsonRoot); 

    Json::StreamWriterBuilder streamWriterBuilder;
    streamWriterBuilder.settings_["indentation"] = "";
    friendinfo = Json::writeString(streamWriterBuilder, jsonRoot);
}

bool ChatSession::ModifyChatMsgLocalTimeToServerTime(const std::string& chatInputJson, std::string& chatOutputJson)
{
    /*
        锟斤拷息锟斤拷式锟斤拷
        {
            "msgType": 1, //锟斤拷息锟斤拷锟斤拷 0未知锟斤拷锟斤拷 1锟侥憋拷 2锟斤拷锟节讹拷锟斤拷 3锟侥硷拷
            "time": 2434167,
            "clientType": 0,		//0未知 1pc锟斤拷 2苹锟斤拷锟斤拷 3锟斤拷卓锟斤拷
            "font":["fontname", fontSize, fontColor, fontBold, fontItalic, fontUnderline],
            "content":
            [
                {"msgText": "text1"},
                {"msgText": "text2"},
                {"faceID": 101},
                {"faceID": 102},
                {"pic": ["name", "server_path", 400, w, h]},
                {"remotedesktop": 1},
                {"shake": 1},
                {"file":["name", "server_path", 400, onlineflag]}		//onlineflag为0锟斤拷锟斤拷锟斤拷锟侥硷拷锟斤拷锟斤拷为0为锟斤拷锟斤拷锟侥硷拷
            ]
        }
    */
    if (chatInputJson.empty())
        return false;
    
    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value jsonRoot;
    JSONCPP_STRING errs;
    bool ok = reader->parse(chatInputJson.c_str(), chatInputJson.c_str() + chatInputJson.length(), &jsonRoot, &errs);
    if (!ok || errs.size() != 0)
    {
        LOGE("parse chatInputJson json failed, userid: %d, chatInputJson: %s", m_userinfo.userid, chatInputJson.c_str());
        delete reader;
        return false;
    }
    delete reader;

    unsigned int now = (unsigned int)time(NULL);
    //if (JsonRoot["time"].isNull())
    jsonRoot["time"] = now;

    //Json::FastWriter writer;
    //chatOutputJson = writer.write(JsonRoot);
    Json::StreamWriterBuilder streamWriterBuilder;
    //锟斤拷锟斤拷json锟叫碉拷\t锟斤拷\n锟斤拷锟斤拷
    streamWriterBuilder.settings_["indentation"] = "";
    chatOutputJson = Json::writeString(streamWriterBuilder, jsonRoot);

    return true;
}

void ChatSession::EnableHearbeatCheck()
{
    std::shared_ptr<TcpConnection> conn = GetConnectionPtr();
    if (conn)
    {        
        //每15锟斤拷锟接硷拷锟揭伙拷锟斤拷欠锟斤拷械锟斤拷锟斤拷锟斤拷锟�
        m_checkOnlineTimerId = conn->getLoop()->runEvery(15000000, std::bind(&ChatSession::CheckHeartbeat, this, conn));
    }
}

void ChatSession::DisableHeartbeatCheck()
{
    std::shared_ptr<TcpConnection> conn = GetConnectionPtr();
    if (conn)
    {
        LOGI("remove check online timerId, userid: %d, clientType: %d, client address: %s", m_userinfo.userid, m_userinfo.clienttype, conn->peerAddress().toIpPort().c_str());        
        conn->getLoop()->cancel(m_checkOnlineTimerId, true);
    }
}

void ChatSession::CheckHeartbeat(const std::shared_ptr<TcpConnection>& conn)
{   
    if (!conn)
        return;
    
    //LOGI("check heartbeat, userid: %d, clientType: %d, client address: %s", m_userinfo.userid, m_userinfo.clienttype, conn->peerAddress().toIpPort().c_str());

    if (time(NULL) - m_lastPackageTime < MAX_NO_PACKAGE_INTERVAL)
        return;
    
    conn->forceClose();
    //LOGI("in max no-package time, no package, close the connection, userid: %d, clientType: %d, client address: %s", m_userinfo.userid, m_userinfo.clienttype, conn->peerAddress().toIpPort().c_str());
}