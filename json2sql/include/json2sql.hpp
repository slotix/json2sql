//
// Created by sn0w1eo on 02.03.18.
//

#ifndef JSON2SQL_JSON2SQL_HPP
#define JSON2SQL_JSON2SQL_HPP

#include <document.h>
#include "dialects/sqlite.hpp"
#include "config.hpp"
#include "table.hpp"

namespace DBConvert {
    namespace Structures {
        namespace Dialect {
            class SQLite;
        }
    }
}

namespace DBConvert {

    class json2sql {
        friend class DBConvert::Structures::Dialect::SQLite;
        static const unsigned int buffer_read_size = 65536;
        static bool find_table_by_title(const Structures::Table *table, const rapidjson::Value *title);
    private:
        rapidjson::Document   document_json_;
        const char          * text_json_;
        FILE                * file_json_;
        uint32_t              guid_;
        DIALECT               dialect_;

        std::vector<Structures::Table*> tables_;
        void hash_entry(rapidjson::Value &entry, rapidjson::Value *title, uint16_t depth, Structures::Table *parent);
        void enum_entry(rapidjson::Value &entry, rapidjson::Value *title, uint16_t depth, Structures::Table *parent);
        Structures::Table * add_table(rapidjson::Value *title, uint16_t depth, Structures::Table *parent, bool isHashTable);
    public:
        explicit json2sql(const char *text_json, DIALECT dialect = DIALECT::SQLite);
        explicit json2sql(FILE *file, DIALECT dialect = DIALECT::SQLite);
        ~json2sql();
        void parse();
        friend std::ostream & operator << (std::ostream &stream, json2sql &json_to_sql);
        void set_dialect(const DIALECT dialect) { dialect_ = dialect; };
        DIALECT get_dialect() { return dialect_; };
    };
}

#endif //JSON2SQL_JSON2SQL_HPP
