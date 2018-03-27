#include <iostream>
#include "document.h"
#include <fstream>
#include "third-party/argparse/argparse.hpp"
#include <chrono>
#include "json2sql.hpp"

using namespace rapidjson;

int main(int argc, const char** argv)
{
    ArgumentParser parser;
    parser.addArgument("-j", 1, true);
    parser.addArgument("-o", 1, true);
    parser.parse(argc, argv);

    if (!parser.count("j"))  {
        std::cout << "USAGE: " << std::endl << "  -j - json filepath" << std::endl << "  -o - output file (IF NOT SPECIFIED: will be printed to console)" << std::endl << "Example: example3 -j myjson.txt -o sqlite.sql" <<std::endl;
        return 0;
    }

    auto json_file = parser.retrieve<std::string>("j");
    auto out_file  = parser.retrieve<std::string>("o");

    {
        FILE* fp = fopen(json_file.c_str(), OPEN_MODE);
        if (!fp)
        {
            std::cout << "Unable to open JSON file: " << json_file << std::endl;
            return 0 ;
        }
        DBConvert::json2sql obj{ fp };
        const auto start_time = clock();
        std::cout << "Parsing..." << std::endl;
        obj.parse();
        fclose(fp);
        const auto parse_finished_time = clock();
        std::cout << "Parse completed: " << ((parse_finished_time - start_time)/1000) << "sec" << std::endl;
        std::cout << "Output..." << std::endl;
        if (out_file.length()> 0)
        {
            std::fstream fs;
            fs.open(out_file.c_str(), std::fstream::out);
            if (!fs.is_open())
            {
                std::cout << "Unable to open OUT file: " << out_file << std::endl;
                return 0;
            }
            fs << obj;
            fs.close();
        } else
        {
            std::cout << obj << std::endl;
        }
        const auto output_finished_time = clock();
        std::cout << "Output completed: " << ((output_finished_time - parse_finished_time) / 1000) << "sec" << std::endl;

    }
    std::cout << "Finished!";
    return 0;
}