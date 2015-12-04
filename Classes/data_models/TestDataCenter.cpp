#include "data_models/TestDataCenter.h"
#include "util/cocos_util.h"
#include "rapid_json/document.h"
#include "cocos2d.h"
#include <cassert>
USING_NS_CC;
using rapidjson::Document;
using rapidjson::Value;

void TestDataCenter::init(const std::string &cfg)
{
    unsigned long size(0);
    unsigned char *data = CCFileUtils::sharedFileUtils()->getFileData(
        cfg.c_str(), "rb", &size);
    if (data) 
    {
        Document d;
        std::string s((const char*)data, size);
        d.Parse<rapidjson::kParseDefaultFlags>(s.c_str());
        if (d.HasParseError()) 
        {
            CocosUtil::log("parse test cfg fail\n");
            return;
        }
        CCAssert(d["items"].IsArray(), "items should be array");
        Value &root = d["items"];
        for (int i=0; i<root.Size(); ++i) 
        {
            testSet_.push_back(new TestDataItem(root[i]["icon"].GetString(), 
                root[i]["description"].GetString(), root[i]["page"].GetString()));
        }
    }
}

TestDataCenter::TestDataCenter()
{

}

TestDataCenter::~TestDataCenter()
{
    for (auto & item : testSet_) 
    {
        if (item) 
        {
            delete item;
            item = nullptr;
        }
    }
    testSet_.clear();
    TestSet().swap(testSet_);
}

TestDataItem* TestDataCenter::getTestDataItemByIndex(int index) const
{
    if (index > -1 && index < testSet_.size()) 
    {
        return testSet_[index];
    }
    return nullptr;
}
