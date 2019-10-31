//
// Created by lzy on 10/29/19.
//

#include <third_party/gmock/gtest/gtest.h>
#include "../../base/AsyncLog.h"



TEST(Test,TestInitAndFun) {
        CAsyncLog::init("test.log");
        LOGI("start log info");
        LOGE("error %d %c %s",10,'a',"dsad");
        LOGW("warnning");
}