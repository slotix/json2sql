//
// Created by sn0w1eo on 02.03.18.
//

#ifndef JSON2SQL_JSON2SQL_HPP
#define JSON2SQL_JSON2SQL_HPP

#include <document.h>
#include "config.hpp"
#include "table.hpp"

namespace DBConvert {

    class json2sql {
        static const unsigned int buffer_read_size = 65536;
        static bool find_table_by_title(const Structures::Table *table, const rapidjson::Value *title);
    private:
        rapidjson::Document document_json_;
        const char * text_json_;
        FILE * file_json_;
        uint32_t guid_ = 0;

        std::vector<Structures::Table*> tables_;
        void hash_entry(rapidjson::Value &entry, rapidjson::Value *title, uint16_t depth, Structures::Table *parent);
        void enum_entry(rapidjson::Value &entry, rapidjson::Value *title, uint16_t depth, Structures::Table *parent);
        Structures::Table * add_table(rapidjson::Value *title, uint16_t depth, Structures::Table *parent, bool isHashTable);
    public:
        explicit json2sql(const char *text_json)
                : text_json_(text_json), file_json_(nullptr) { if (text_json == nullptr) throw Json2Sql_TextJsonNullPtr; };
        explicit json2sql(FILE *file)
                : text_json_(nullptr), file_json_(file) { if (file == nullptr) throw Json2Sql_FileNullPtr; };
        ~json2sql();
        void parse();
    };
}

#endif //JSON2SQL_JSON2SQL_HPP
