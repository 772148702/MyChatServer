//
// Created by lzy on 10/29/19.
//

#include <base/AsyncLog.h>
#include "net/Poller.h"
#include "net/EpollPoller.h"
#include "net/SelectPoller.h"
#include "net/PollPoller.h"
#include "net/TcpServer.h"
#include "net/EventLoop.h"
using namespace net;

void TcpMessageCallBack(const TcpConnectionPtr& ptr, Buffer* buffer, Timestamp t1)
{
    LOGI("recevie from %s:%s",ptr.get()->peerAddress().toIpPort().c_str(),buffer->retrieveAllAsString().c_str());
}
int main() {
    CAsyncLog::init("testServer.log");
    EventLoop *loop = new EventLoop() ;
    InetAddress inetAddress("127.0.0.1",9000);
    TcpServer server(loop,inetAddress,"testServer",TcpServer::Option::kReusePort);
    server.setMessageCallback(TcpMessageCallBack);
    server.start();
    loop->loop();
}
