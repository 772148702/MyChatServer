#include "TcpConnection.h"

#include <functional>
#include <thread>
#include <sstream>
#include <errno.h>
#include "../base/Platform.h"
#include "../base/AsyncLog.h"
#include "Sockets.h"
#include "EventLoop.h"
#include "Channel.h"


using namespace net;

void net::defaultConnectionCallback(const TcpConnectionPtr& conn)
{
    LOGD("%s ->is %s",
        conn->localAddress().toIpPort().c_str(),
        conn->peerAddress().toIpPort().c_str(),
        (conn->connected()?"Up":"DOWN"));
}

void net::defaultConnectionCallback(const TcpConnectionPtr&, Buffer* buf, Timestamp)
{
    buf->retrieveAll();
}

TcpConection::TcpConnection(EventLoop* loop,const string& nameArg,int sockfd, const InetAddress& localAddr, const InetAddress& peerAddr)
:loop_(loop),
name_(nameArg),
socket_(new Socket(sockfd)),
channel_(new Channel(loop,sockfd)),
localAddr_(localAddr_),
peerAddr(peerAddr),
highWaterMark_(64*1024*1024)
{
     channel_->setReadCallback(std::bind(&TcpConnection::handleRead, this, std::placeholders::_1));
    channel_->setWriteCallback(std::bind(&TcpConnection::handleWrite, this));
    channel_->setCloseCallback(std::bind(&TcpConnection::handleClose, this));
    channel_->setErrorCallback(std::bind(&TcpConnection::handleError, this));
    LOGD("TcpConnection::ctor[%s] at 0x%x fd=%d", name_.c_str(), this, sockfd);
    socket_->setKeepAlive(true);
}

TcpConnection::~TcpConnection()
{
    LOGD("TcpConnection::dtor[%s] at 0x%x fd=%d state=%s", 
         name_.c_str(), this, channel_->fd(),stateToString());
    //assert(state_ == kDisconnected);
}
bool TcpConnection::getTcpInfo(struct tcp_info* tcpi) const
{
    //return socket_->getTcpInfo(tcpi);
    return false;
}

string TcpConnection::getTcpInfoString() const
{
    char buf[1024];
    buf[0] = '\0';
    socket_->getTcpInfoString(buf, sizeof buf);
    return buf;
}

void TcpConnection::send(const void* data, int len)
{
    if (state_ == kConnected)
    {
        if (loop_->isInLoopThread())
        {
            sendInLoop(data, len);
        }
        else
        {
            string message(static_cast<const char*>(data), len);
            loop_->runInLoop(
                std::bind(static_cast<void (TcpConnection::*)(const string&)>(&TcpConnection::sendInLoop),
                    this,     // FIXME
                    message));
        }
    }
}

void TcpConnection::send(const string & message)
{
    if (state_ == kConnected)
    {
        if (loop_->isInLoopThread())
        {
            sendInLoop(message);
        }
        else
        {
            loop_->runInLoop(
                std::bind(static_cast<void (TcpConnection::*)(const string&)>(&TcpConnection::sendInLoop),
                    this,     // FIXME
                    message));
            //std::forward<string>(message)));
        }
    }
}


void TcpConnection::send(Buffer* buf)
{
if (state_ == kConnected)
    {
        if (loop_->isInLoopThread())
        {
            sendInLoop(buf->peek(), buf->readableBytes());
            buf->retrieveAll();
        }
        else
        {
            loop_->runInLoop(
                std::bind(static_cast<void (TcpConnection::*)(const string&)>(&TcpConnection::sendInLoop),
                    this,     // FIXME
                    buf->retrieveAllAsString()));
            //std::forward<string>(message)));
        }
    }
}

void TcpConnection::sendInLoop(const string & message)
{
    sendInLoop(message.c_str(), message.size());
}

void TcpConnection::sendInLoop(const void* data, size_t len)
{
    loop_->assertInLoopThread();
    int32_t nwrote = 0;
    size_t remaining = len;
    bool faultError = false;
    if (state_ == kDisconnected)
    {
        LOGW("disconnected, give up writing");
        return;
    }
   // if no thing in output queue, try writing directly
    if (!channel_->isWriting() && outputBuffer_.readableBytes() == 0)
    {
        nwrote = sockets::write(channel_->fd(), data, len);
        //TODO: 锟斤拷印threadid锟斤拷锟节碉拷锟皆ｏ拷锟斤拷锟斤拷去锟斤拷
        //std::stringstream ss;
        //ss << std::this_thread::get_id();
        //LOGI << "send data in threadID = " << ss;

        if (nwrote >= 0)
        {
            remaining = len - nwrote;
            if (remaining == 0 && writeCompleteCallback_)
            {
                loop_->queueInLoop(std::bind(writeCompleteCallback_, shared_from_this()));
            }
        }
        else // nwrote < 0
        {
            nwrote = 0;
            if (errno != EWOULDBLOCK)
            {
                LOGSYSE("TcpConnection::sendInLoop");
                if (errno == EPIPE || errno == ECONNRESET) // FIXME: any others?
                {
                    faultError = true;
                }
            }
        }
    }

       if (remaining > len)
        return;

   if (!faultError && remaining > 0)
    {
        size_t oldLen = outputBuffer_.readableBytes();
        if (oldLen + remaining >= highWaterMark_
            && oldLen < highWaterMark_
            && highWaterMarkCallback_)
        {
            loop_->queueInLoop(std::bind(highWaterMarkCallback_, shared_from_this(), oldLen + remaining));
        }
        outputBuffer_.append(static_cast<const char*>(data) + nwrote, remaining);
        if (!channel_->isWriting())
        {
            channel_->enableWriting();
        }
    }
}

void TcpConnection::shutdown()
{
    if(state_ ==kConnected)
    {
        setState(kDisconnecting);
        loop_->runInLoop(std::bind(&TcpConnection::shutdownInLoop, this));
    }
}

void TcpConnection::shutdownInLoop()
{
    loop_->assertInLoopThread();
    if (!channel_->isWriting())
    {
        // we are not writing
        socket_->shutdownWrite();
    }
}

void TcpConnection::forceClose()
{
    if(state_==kConnected||state==kDisconnecting)
    {
        setState(kDisconnecting);
        loop_->queueInLoop(std::bind(&TcpConnection::forceCloseInLoop,shared_from_this()));
    }
}


void TcpConnection::forceCloseInLoop()
{
    loop_->assertInLoopThread();
    if(state_==kConnected||state_==kDisconnecting)
    {
        handleClose();
    }
}

const char* TcpConnection::stateToString() const
{
    switch (state_)
    {
    case kDisconnected:
        return "kDisconnected";
    case kConnecting:
        return "kConnecting";
    case kConnected:
        return "kConnected";
    case kDisconnecting:
        return "kDisconnecting";
    default:
        return "unknown state";
    }
 }
}

void TcpConnection::setTcpNoDelay(bool on)
{
    socket_->setTcpNoDelay(on);
}

void TcpConnection::connectEstablished()
{
    loop_->assertInLoopThread();
    if(state_!=kConnecting)
    {
        return;
    }
    setstate(kConnected);
    channel_->tie(shared_from_this());
    if(!channel_->enableReading())
    {
        LOGE("enableReading failed.");
        handleClose();
        return;
    }
    ConnectionCallback_(shared_from_this());
}

void TcpConnection::connectDestroyed()
{
    loop_->assertInLoopThread();
    if(state_ == kConnected)
    {
        setState(kDisconnected);
        channel_->disableAll();

        ConnectionCallback_(shared_from_this());
    }
    channel_->remove();
}

void TcpConnect::handleRead(Timestamp receiveTime)
{
    loop_->assertInLoopThread();
    int savedErrno = 0;
    int32_t n = inputBuffer_.readFd(channel_->fd(),&savedErrno);
    if(n>0)
    {
        messageCallback_(shared_from_this(),&inputBuffer_,receiveTime);
    } else if(n==0)
    {
        handleClose();
    } else {
        errno = savedErrno;
        LOGSYSE("TcpConnection::handleRead");
        handleError();
    }
}


void TcpConnection::handleWrite()
{
    loop_->assertInLoopThread();
    if(channel_->isWriting())
    {
        int32_t n = sockets::write(channel_->fd(),outputBuffer_.peek(),outputBuffer_.readableBytes());
        if(n>0)
        {
            outputBuffer_.retrieve(n);
            if(outputBuffer_.readableBytes()==0)
            {
                channel_->disableWriting();
                if(WriteCompleteCallback_)
                {
                    loop_->queueInLoop(std::bind(WriteCompleteCallback_,shared_from_this()));   
                }
                if(state_ == kDisconnecting)
                {
                    shutdownInLoop();
                }
            } 
        } 
        else
        {
            LOGSYSE("TcpConnection::handleWrite");
            handleClose();
        }
    }  else {
        LOGD("Connection fd = %d is down, no more writing",channel_->fd());
    }    
}

void TcpConnection::hanleClose()
{
    if(state_ ==kDisConnected)
        return;
    
    loop_->assertInLoopThread();
    LOGD("fd = %d state=%s",channel_->fd(),stateToString());

    setState(kDisconnected);
    channel_->disableAll();

    TcpConnectionPtr guardThis(shared_from_this());
    ConnectionCallback(guarThis);
    closeCallback_(guardThis);
}

void TcpConnection::handleError()
{
    int err = sockets::getSocketError(channel_->fd());
    LOGE("TcpConnection::%s handleError [%d]- SO_ERROR = %s", name_.c_str(), err , strerror(err));
}