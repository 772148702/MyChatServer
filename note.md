# 学习flamingo过程中的笔记

## Singleton模板的实现，利用模板和static来实现了单例工厂模式，没有使用锁来进行约束。

## ChatServer的实现原理，设置好ConnectionCallback。利用ConnectionCallback中传递的connection来设置MessageCallback,得到读的消息。而写的消息通过Session里面保存的weakptr在逻辑处理结束后进行发送。

## cmake的写法也是很厉害,直接将src全部包含在了一起利用add_executable打包成可执行文件，然后Target_LINK_LIBRARIIES即可。

## ChatServer
### LoginIn
1. 利用Json进行解码，判断输入是否合法
2. 从数据库中按照用户名得到cacheUer信息比较
3.  登录成功，返回cacheUer给客户端。
4. 在session中缓存用户的信息。
5. 返回NotifySession中用户的信息(猜测应该是添加为好友等通知）。
6. 返回CacheMsg中用户的信息，未发送到用户的信息(比如用户下线的时候，其他用户对该用户发送的信息)。
7.  查询数据库得到朋友的列表，然后得到朋友的session，向朋友发送该用户上线。



### SendUserStatusChangeMsg(int32_t userid,int type,int status)
1. status 1 应该是上线， status 2 不清楚， status 3不清楚。

### void ChatSession::MakeSessionInvalid()
m_userinfo.userid=0,使其session无效。

### bool ChatSession::IsSessionValid()
判断m_userinfo.userid是否大于0

### bool ChatSession::ModifyChatMsgLocalTimeToServerTime(const std::string& chatInputJson, std::string& chatOutputJson)
1. 解析输入的Json字符串
2. 将本机的时间输入到json中，并返回字符串。


### OnChatResponse
1. 给要发送的信息添加上时间。
2. 在数据库中保存要发送的信息。
3. 若是群聊
     得到群聊session的list,遍历list发送消息。
4.  若是个人聊天
    从target得到list<session_ptr> ???

### OnMultiChatResponse
#### 一条同样信息多发，多次调用OnChatResponse


## #OnScreenshotResponse

### OnUpdateTeamInfoResponse

### OnUpdateTeamInfoResponse
 这个功能的实现也非常复杂。

### ChatSession::MakeUpFriendListInfo(std::string& friendinfo, const std::shared_ptr<TcpConnection>& conn)
 读了半天终于读懂了，该函数的作用是通过userId，从数据库加载friendinfo, 然后根据friendinfo中friendid加载friend的信息，并加载friend的化名。最终返回。

 ### DeleteFriend
 需要调试才能够弄清楚GROUNP_BOUNDARY的含义。
 