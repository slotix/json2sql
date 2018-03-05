//
// Created by sn0w1eo on 04.03.18.
//

#ifndef JSON2SQL_DIALECT_HPP
#define JSON2SQL_DIALECT_HPP

#include <ostream>
#include "json2sql.hpp"

namespace DBConvert {
    class json2sql;
}

namespace DBConvert {
    namespace Structures {
        namespace Dialect {

            class SQLDialect {
                friend class DBConvert::json2sql;
            protected:
                DBConvert::json2sql *json_to_sql_;
                explicit SQLDialect(DBConvert::json2sql *json_to_sql) : json_to_sql_(json_to_sql) {};
            public:
                virtual ~SQLDialect() = default;
                virtual void raw_sql(std::ostream &) = 0;
            };
        }
    }
}

#endif //JSON2SQL_DIALECT_HPP
