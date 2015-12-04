#ifndef CPP_DEMO_DATA_MODELS_TESTDATACENTER_H
#define CPP_DEMO_DATA_MODELS_TESTDATACENTER_H

#include "util/singleton.h"
#include <string>
#include <vector>

class TestDataItem
{
public:
    TestDataItem(const std::string &icon, const std::string &description, 
        const std::string &pageName) 
        : icon_(icon), description_(description), pageName_(pageName)
    {}

    std::string     icon_;
    std::string     description_;
    std::string     pageName_;
};

class LogicDirector;

class TestDataCenter : public Singleton<TestDataCenter>
{
    friend Singleton<TestDataCenter>;
    friend LogicDirector;
public:
    typedef std::vector<TestDataItem*> TestSet;

    void init(const std::string &cfg);

    TestDataItem* getTestDataItemByIndex(int index) const;

    int testDataCount() const 
    {
        return testSet_.size();
    }

    inline const TestSet& getDataSet() const 
    {
        return testSet_;
    }

protected:
    TestDataCenter();
    ~TestDataCenter();

private:
    TestSet     testSet_;
};

#endif