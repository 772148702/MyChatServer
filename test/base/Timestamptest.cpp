#include "../../third_party/gmock/gtest/gtest.h"
#include "../../base/Timestamp.h"
#include <iostream>
#include <time.h>


TEST(TimestampTest,UnitTest) {
    Timestamp s(time(NULL));
    std::cout<<s.now().toFormattedString()<<std::endl;
}



