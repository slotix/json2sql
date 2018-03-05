//
// Created by sn0w1eo on 04.03.18.
//

#ifndef JSON2SQL_SQLITE_HPP
#define JSON2SQL_SQLITE_HPP

#include <ostream>
#include "json2sql.hpp"
#include <config.hpp>
#include <vector>
#include <dialect.hpp>
#include "table.hpp"

namespace DBConvert {
    class json2sql;
}

namespace DBConvert {
    namespace Structures {
        namespace Dialect {

            class SQLite : public SQLDialect {
                friend class DBConvert::json2sql;
            private:
                std::ostream *out_stream_ = nullptr;
                void sql_main_table();
                void sql_table_to_ddl(Table *);
                void sql_table_to_dml(Table *);
                std::string enc(const char *str);
                std::string value_to_string(const rapidjson::Value *);
                std::string sqlite_type(uint8_t type);
                std::string p_value(const Field *field, const rapidjson::Value *value);
                std::string vector_to_string(std::vector<std::string> &vec);
                const char sq = '"'; //Syntax Quotes ' or "
                std::string find_sq = "\"";
                std::string replace_sq = "\"\"";
                std::string& replace_all_sq(std::string&);
                //static const char fd = '.'; //Float delimiter for SQLite is dot( . )
            public:
                explicit SQLite(DBConvert::json2sql *json_to_sql) : SQLDialect(json_to_sql) {}
                ~SQLite() override;
                void raw_sql(std::ostream &) override;
            };
            inline std::string SQLite::sqlite_type(uint8_t type) {
                switch (type) {
                    case FIELD_TYPE::TEXT:
                        return "TEXT";
                    case FIELD_TYPE::BOOLEAN:
                        return "NUMERIC";
                    case FIELD_TYPE::DOUBLE:
                        return "REAL";
                    case FIELD_TYPE::NUMBER:
                        return "INTEGER";
                    case FIELD_TYPE::NULLS:
                        return "BLOB";
                    default:
                        return "BLOB";
                }
            }
        }
    }
}

#endif //JSON2SQL_SQLITE_HPP
