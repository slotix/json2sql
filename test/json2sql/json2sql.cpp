//
// Created by sn0w1eo on 03.03.18.
//

#include <gtest/gtest.h>
#include "json2sql.hpp"

namespace {
    using rapidjson::Value;
    using namespace DBConvert;
    using namespace Structures;

    class Json2SqlTest : public ::testing::Test {
    protected:
        void SetUp() {
            json2sql_obj = new json2sql(json_text);
        }
        void TearDown() {
            delete json2sql_obj;
        }
        const char * json_text = R"([ { "key" : "value1" }, { "key" : "value2" } ])";
        json2sql * json2sql_obj;
    };

    TEST_F(Json2SqlTest, Parse) {
        EXPECT_NO_THROW(json2sql_obj->parse());
    }

}