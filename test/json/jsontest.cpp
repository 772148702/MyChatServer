//
// Created by lzy on 10/30/19.
//

#include "jsoncpp1.9.0/json.h"
#include "../../third_party/gmock/gtest/gtest.h"
#include "stdio.h"
#include "cstring"

TEST(jsonTest,UnitTest)
{
    std::string  data= "{\"user\":\"weqe\",\"password\":\"212\",\"friends\":[{\"user\":\"121\"},{\"user\":\"232\"}]}";
    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value jsonRoot;
    JSONCPP_STRING errs;
    bool ok = reader->parse(data.c_str(), data.c_str() + data.length(), &jsonRoot, &errs);

    std::string user = jsonRoot["user"].asString();

    std::string password = jsonRoot["password"].asString();

    //the following failed
    std::string username1= jsonRoot["friends"][0].asString();
    std::string username2= jsonRoot["friends"][1].asString();

    printf("%s %s %s %s",user.c_str(),password.c_str(),username1.c_str(),username2.c_str());
}

TEST(jsonTestArray,UnitTest)
{
    std::string  data= "{ \"temp\": [\"user\":\"weqe\",\"password\":\"212\"],[\"user\":\"weqe\",\"password\":\"212\"]}";
    Json::CharReaderBuilder b;
    Json::CharReader* reader(b.newCharReader());
    Json::Value jsonRoot;
    JSONCPP_STRING errs;
    bool ok = reader->parse(data.c_str(), data.c_str() + data.length(), &jsonRoot, &errs);

    J
    for(int i=0;i<jsonRoot["temp"].size();i++)
    {
        printf("%s %s",jsonRoot["temp"][i]["user"].asCString(),jsonRoot["temp"][i]["password"].asCString());
    }
}