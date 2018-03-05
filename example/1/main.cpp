//
// Created by sn0w1eo on 03.03.18.
//

#include <iostream>
#include "json2sql.hpp"

int main() {
    const char * json = R"([ { "key2" : "value1", "pow" : [1,2] }, { "key" : "value2", "pow3" : [3,4] } ])";
    DBConvert::json2sql obj(json);   // second parameter is DIALECT::SQLite as default
    obj.parse();                     // rapidjson parse then json2sql parse
    std::cout << obj << std::endl;   // result output
}
