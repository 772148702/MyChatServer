set(base_SRCS
  AsyncLog.cpp
  ConfigFileReader.cpp
  CountDownLatch.cpp
  Platform.cpp
  RAIIWrapper.h
  Singleton.h
  Timestamp.cpp
  )
  add_library(muduo_base ${base_SRCS})