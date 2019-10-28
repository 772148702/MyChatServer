/** 
 * ChatSession.h
 * zhangyl, 2017.03.10
 **/

#pragma once
#include "../net/Buffer.h"
#include "../net/TimerId.h"
#include "TcpSession.h"
using namespace net;

struct OnlineUserInfo
{
    int32_t     userid;
    std::string username;
    std::string nickname;
    std::string password;
    int32_t     clienttype;     //閿熼叺浼欐嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�, 0鏈煡, pc=1, android/ios=2
    int32_t     status;         //閿熸枻鎷烽敓鏂ゆ嫹鐘舵€� 0閿熸枻鎷烽敓鏂ゆ嫹 1閿熸枻鎷烽敓鏂ゆ嫹 2蹇欑 3閿熻寮€ 4閿熸枻鎷烽敓鏂ゆ嫹
};

/**
 * 閿熸枻鎷烽敓鏂ゆ嫹宄勫府鎷烽敓锟�
 */
class ChatSession : public TcpSession
{
public:
    ChatSession(const std::shared_ptr<TcpConnection>& conn, int sessionid);
    virtual ~ChatSession();

    ChatSession(const ChatSession& rhs) = delete;
    ChatSession& operator =(const ChatSession& rhs) = delete;

    //閿熸枻鎷烽敓鏂ゆ嫹閿熸嵎鍙鎷�, 閿熺粨琚敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熺担oop閿熸枻鎷烽敓鏂ゆ嫹
    void OnRead(const std::shared_ptr<TcpConnection>& conn, Buffer* pBuffer, Timestamp receivTime);   
    
    int32_t GetSessionId()
    {
        return m_id;
    }

    int32_t GetUserId()
    {
        return m_userinfo.userid;
    }

    std::string GetUsername()
    {
        return m_userinfo.username;
    }

    std::string GetNickname()
    {
        return m_userinfo.nickname;
    }

    std::string GetPassword()
    {
        return m_userinfo.password;
    }

    int32_t GetClientType()
    {
        return m_userinfo.clienttype;
    }

    int32_t GetUserStatus()
    {
        return m_userinfo.status;
    }

    int32_t GetUserClientType()
    {
        return m_userinfo.clienttype;
    }

    /**
     *@param type 鍙栧€奸敓鏂ゆ嫹 1 閿熺煫浼欐嫹閿熸枻鎷烽敓绔綇鎷� 2 閿熺煫浼欐嫹閿熸枻鎷烽敓绔綇鎷� 3 閿熸枻鎷烽敓鏂ゆ嫹閿熻绉扳槄鎷峰ご閿熸枻鎷风閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷锋伅閿熸枻鎷烽敓鏂ゆ嫹
     */
    void SendUserStatusChangeMsg(int32_t userid, int type, int status = 0);

    //閿熸枻鎷稴ession澶辨晥閿熸枻鎷烽敓鏂ゆ嫹閿熻妭鎲嬫嫹閿熸枻鎷烽敓鏂ゆ嫹閿熺纰夋嫹閿熺煫浼欐嫹閿熸枻鎷穝ession
    void MakeSessionInvalid();
    bool IsSessionValid();

    void EnableHearbeatCheck();
    void DisableHeartbeatCheck();

    //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷锋寚閿熸枻鎷锋椂閿熸枻鎷烽敓鑺傦綇鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹30閿熻锛夋湭閿熺Ц纰夋嫹閿熸枻鎷烽敓鎹峰府鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓杈冨尅鎷烽敓鑺傚浼欐嫹閿熷壙纰夋嫹閿熸枻鎷烽敓鏂ゆ嫹
    void CheckHeartbeat(const std::shared_ptr<TcpConnection>& conn);

private:
    bool Process(const std::shared_ptr<TcpConnection>& conn, const char* inbuf, size_t buflength);
    
    void OnHeartbeatResponse(const std::shared_ptr<TcpConnection>& conn);
    void OnRegisterResponse(const std::string& data, const std::shared_ptr<TcpConnection>& conn);
    void OnLoginResponse(const std::string& data, const std::shared_ptr<TcpConnection>& conn);
    void OnGetFriendListResponse(const std::shared_ptr<TcpConnection>& conn);
    void OnFindUserResponse(const std::string& data, const std::shared_ptr<TcpConnection>& conn);
    void OnChangeUserStatusResponse(const std::string& data, const std::shared_ptr<TcpConnection>& conn);
    void OnOperateFriendResponse(const std::string& data, const std::shared_ptr<TcpConnection>& conn);
    void OnAddGroupResponse(int32_t groupId, const std::shared_ptr<TcpConnection>& conn);
    void OnUpdateUserInfoResponse(const std::string& data, const std::shared_ptr<TcpConnection>& conn);
    void OnModifyPasswordResponse(const std::string& data, const std::shared_ptr<TcpConnection>& conn);
    void OnCreateGroupResponse(const std::string& data, const std::shared_ptr<TcpConnection>& conn);
    void OnGetGroupMembersResponse(const std::string& data, const std::shared_ptr<TcpConnection>& conn);
    void OnChatResponse(int32_t targetid, const std::string& data, const std::shared_ptr<TcpConnection>& conn);
    void OnMultiChatResponse(const std::string& targets, const std::string& data, const std::shared_ptr<TcpConnection>& conn);
    void OnScreenshotResponse(int32_t targetid, const std::string& bmpHeader, const std::string& bmpData, const std::shared_ptr<TcpConnection>& conn);
    void OnUpdateTeamInfoResponse(int32_t operationType, const std::string& newTeamName, const std::string& oldTeamName, const std::shared_ptr<TcpConnection>& con);
    void OnModifyMarknameResponse(int32_t friendid, const std::string& newmarkname, const std::shared_ptr<TcpConnection>& conn);
    void OnMoveFriendToOtherTeamResponse(int32_t friendid, const std::string& newteamname, const std::string& oldteamname, const std::shared_ptr<TcpConnection>& conn);

    void DeleteFriend(const std::shared_ptr<TcpConnection>& conn, int32_t friendid);

    //閿熸枻鎷烽敓鏂ゆ嫹閿熺煫浼欐嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷锋伅閿熸枻鎷疯搴旈敓鏂ゆ嫹閿熸枻鎷风獊閿熸枻鎷疯鏆敓鏂ゆ嫹閿熸枻鎷锋枩閿熸枻鎷烽敓杈冿拷
    void MakeUpFriendListInfo(std::string& friendinfo, const std::shared_ptr<TcpConnection>& conn);

    //閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹鎭敓渚ユ唻鎷烽敓鏂ゆ嫹鏃堕敓鏂ゆ嫹鏌愮厼閿熸枻鎷烽敓鏂ゆ嫹閿熺粸鎲嬫嫹娲岊剨鎷疯柗鏌愭檼閿熸枻鎷烽敓鏂ゆ嫹閿熺但rue,澶遍敓鏉板嚖鎷烽敓鏂ゆ嫹false閿熸枻鎷�
    bool ModifyChatMsgLocalTimeToServerTime(const std::string& chatInputJson, std::string& chatOutputJson);

private:
    int32_t           m_id;                 //session id
    OnlineUserInfo    m_userinfo;
    int32_t           m_seq;                //閿熸枻鎷峰墠Session閿熸枻鎷烽敓鎹峰府鎷烽敓鏂ゆ嫹閿熷彨鐚存嫹
    bool              m_isLogin;            //閿熸枻鎷峰墠Session閿熸枻鎷峰簲閿熸枻鎷烽敓鐭紮鎷烽敓瑙掑嚖鎷烽敓绐栨拝鎷烽敓鏂ゆ嫹褰�
    time_t            m_lastPackageTime;    //閿熸枻鎷蜂竴閿熸枻鎷烽敓绉稿嚖鎷烽敓鏂ゆ嫹閿熸枻鎷锋椂閿熸枻鎷�
    TimerId           m_checkOnlineTimerId; //閿熸枻鎷烽敓鏂ゆ嫹娆犻敓鏂ゆ嫹閿熸枻鎷峰彥浜╅敓缁炴唻鎷烽敓绲燿
};