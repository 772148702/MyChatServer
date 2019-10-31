# MyChatServer





##Net 
The Acceptor in TcpServer
The Channel of Acceptor is updated in loop, by the function EventLoop::update(Channel*)

the flow and call order of important event:
startListen:

TcpServer -> Acceptor::listen -> Channel::enableReading -> EventLoop::update -> poller->update

newConnection:

PollerPoll-> AcceptorChannel::handleRead->Acceptor::handleRead->TcpServer::newConnection->TcpConnection::connectEstablished -> Channel::enableReading ->EventLoop::update -

ReadData:
EventLoop::loop->PollerPoll::poller->Channel::handleEvent->Channel::readCallback

lifetime:

the callback function of channel is passed by the TcpConnection's function like handleRead handleWrite and handleError. These function can


##UserManager
init --> loadUserFromDb --> loadRelationshipFromDb 

loadRelationshipFromDb:: get the friends of userid 

##UserSession
receve data from client and send data to client.
logic procees lies in Session.

The proccess of UserSession of function begin with On:
1. decode the receive data
2. verify the format of json
3. process the data
4. send back and update state in other session.