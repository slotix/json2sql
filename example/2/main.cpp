//
// Created by sn0w1eo on 05.03.18.
//

#include <iostream>
#include "json2sql.hpp"

int main() {
    FILE * file = fopen("example.json", OPEN_MODE); // OPEN_MODE defined in CMakeLists.txt
    if (file) {
        DBConvert::json2sql obj(file);
        obj.parse();
        std::cout << obj << std::endl;              // result output
        fclose(file);
    } else {
        std::cout << "Unable to open example.json..." << std::endl;
    }
}