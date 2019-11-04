cmake_minimum_required(VERSION 2.8)

project(SERVER)
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/third_party/gmock)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -g -Wall -O0 -Wno-unused-variable -pthread")

link_directories(
    ${PROJECT_SOURCE_DIR}/lib
	/usr/lib64/mysql/
)
find_library(MYSQL_LIB libmysqlclient.so /usr/lib64/mysql/)

#add_subdirectory(base)
#add_subdirectory(test)


set(net_srcs 
base/AsyncLog.cpp
base/ConfigFileReader.cpp
base/Platform.cpp
base/Timestamp.cpp

net/Acceptor.cpp
net/Buffer.cpp
net/Channel.cpp
net/Connector.cpp
net/EpollPoller.cpp
net/EventLoop.cpp
net/EventLoopThread.cpp
net/EventLoopThreadPool.cpp
net/InetAddress.cpp
net/Poller.cpp
net/PollPoller.cpp
net/ProtocolStream.cpp
net/SelectPoller.cpp
net/Sockets.cpp
net/TcpClient.cpp
net/TcpConnection.cpp
net/TcpServer.cpp
net/Timer.cpp
net/TimerQueue.cpp
)

set(mysqlapi_srcs
mysqlapi/DatabaseMysql.cpp
mysqlapi/Field.cpp
mysqlapi/QueryResult.cpp
)

set(mysqlmgr_srcs
mysqlmgr/MysqlManager.cpp
mysqlmgr/MysqlThrd.cpp
mysqlmgr/MysqlThrdMgr.cpp
mysqlmgr/TaskList.cpp
)

set(json_srcs
jsoncpp1.9.0/json_reader.cpp
jsoncpp1.9.0/json_value.cpp
jsoncpp1.9.0/json_writer.cpp
)
set(zlib_srcs
zlib1.2.11/zutil.c
zlib1.2.11/uncompr.c
zlib1.2.11/trees.c
zlib1.2.11/inftrees.c
zlib1.2.11/inflate.c
zlib1.2.11/inffast.c
zlib1.2.11/infback.c
zlib1.2.11/gzwrite.c
zlib1.2.11/gzread.c
zlib1.2.11/gzlib.c
zlib1.2.11/gzclose.c
zlib1.2.11/deflate.c
zlib1.2.11/crc32.c
zlib1.2.11/compress.c
zlib1.2.11/adler32.c
zlib1.2.11/ZlibUtil.cpp
)

set(utils_srcs
utils/StringUtil.cpp
utils/URLEncodeUtil.cpp
utils/MD5.cpp
utils/DaemonRun.cpp
)

set(chatserver_srcs
chatserversrc/main.cpp
chatserversrc/ChatServer.cpp
chatserversrc/ChatSession.cpp
chatserversrc/UserManager.cpp
chatserversrc/MsgCacheManager.cpp
chatserversrc/TcpSession.cpp
chatserversrc/MonitorSession.cpp
chatserversrc/MonitorServer.cpp
chatserversrc/HttpSession.cpp
chatserversrc/HttpServer.cpp
chatserversrc/BussinessLogic.cpp
)
set(mychatserver_srcs
myChatserver/chatserversrc/UserManager.cpp )

set(mymysqlmgr_srcs
		myChatserver/mysqlmgr/MysqlManager.cpp
		myChatserver/mysqlmgr/MysqlTask.h
		myChatserver/mysqlmgr/MysqlThrd.cpp
		myChatserver/mysqlmgr/MysqlThrd.h
		myChatserver/mysqlmgr/TaskList.cpp
		myChatserver/mysqlmgr/TaskList.h
		myChatserver/mysqlmgr/MysqlThrdMgr.cpp
		myChatserver/mysqlmgr/MysqlThrdMgr.h)


add_executable(chatserver ${net_srcs} ${json_srcs}  ${chatserver_srcs} ${mysqlapi_srcs} ${mysqlmgr_srcs} ${zlib_srcs} ${utils_srcs})
#光包含库目录是没用的，还必须使用TARGET_LINK_LIBRARIES链接该库
TARGET_LINK_LIBRARIES(chatserver mysqlclient)


set(testutils_srcs
		third_party/gmock/gmock-gtest-all.cc
		third_party/gmock/gmock_main.cc)

set(mysql_srcs
		test/sql/mysqlMgrtest.cpp
		test/chatserver/UserManagertest.cpp)

add_library(testlib ${testutils_srcs})
add_library(netlib ${net_srcs})
add_library(mysqllib  ${mymysqlmgr_srcs}  )
add_library(mysqlapilib ${mysqlapi_srcs})
add_library(mychat ${mychatserver_srcs} myChatserver/chatserversrc/MsgCacheManager.h myChatserver/chatserversrc/MsgCacheManager.cpp myChatserver/chatserversrc/ChatSession.cpp myChatserver/chatserversrc/ChatSession.h myChatserver/chatserversrc/TcpSession.cpp myChatserver/chatserversrc/TcpSession.h myChatserver/chatserversrc/ChatServer.cpp myChatserver/chatserversrc/ChatServer.h)

file(GLOB temp_src_temp ${PROJECT_SOURCE_DIR}/test/*/*test.cpp)
foreach(test_src_temp ${temp_src_temp})
	get_filename_component(test_bare_name ${test_src_temp} NAME)
	string(REPLACE ".cpp" "" test_bare_name_without_extension ${test_bare_name})
	string(REPLACE "\"" "" test_name ${test_bare_name_without_extension})

	add_executable(${test_name}   ${test_src_temp}  ${mychatserver_srcs})
	target_link_libraries(${test_name}  mysqllib mysqlapilib  netlib testlib  mysqlclient  )
endforeach(test_src_temp ${temp_src_temp})