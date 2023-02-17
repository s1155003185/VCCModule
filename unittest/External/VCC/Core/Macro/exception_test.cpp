#include <gtest/gtest.h>

#include "base_exception.hpp"

using namespace std;
using namespace vcc;

class ExceptionTestException : public BaseException
{
    public:
        ExceptionTestException() : BaseException(ExceptionType::NA, L"Error Message") {}
        ~ExceptionTestException() {}
};

class ExceptionTest : public testing::Test 
{
    public:
        void ExceptionProcess()
        {
            throw ExceptionTestException();
        }

        void SetUp() override
        {
            
        }

        void TearDown() override
        {

        }
};

TEST_F(ExceptionTest, DeclareException)
{
    EXPECT_THROW(this->ExceptionProcess(), ExceptionTestException);
    
    bool exception = false;
    try 
    {
        this->ExceptionProcess();
    } 
    catch (ExceptionTestException ex) 
    {
        exception = true;
        EXPECT_EQ(ex.GetMessage(), L"Error Message");
        string whatStr(ex.what());
        EXPECT_EQ(whatStr, "Error Message");
    }
    EXPECT_TRUE(exception);
}
