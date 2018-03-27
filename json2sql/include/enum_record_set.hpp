//
// Created by sn0w1eo on 26.02.18.
//

#ifndef JSON2SQL_ENUM_RECORD_SET_HPP
#define JSON2SQL_ENUM_RECORD_SET_HPP

#include "record_set.hpp"
#include "table.hpp"

namespace DBConvert {
    namespace Structures {

        class EnumRecordSet : public RecordSet {
        private:
            rapidjson::Value * null_value; // temporary NullValue for add_null_record
            Table * owner_table_ = nullptr;
            Field * enum_field_ = nullptr;  // ENUM field
        public:
            explicit EnumRecordSet(Table *owner_table);
            ~EnumRecordSet() final;
            void add_record(rapidjson::Value *value) final;
            void add_null_record() final;

            // HashTable only
            void new_record_begin() final { throw EnumRecordSet_HashTableMethodCalled; }
            void add(const rapidjson::Value *title, rapidjson::Value *value) final { throw EnumRecordSet_HashTableMethodCalled; }
        };
    }
}

#endif //JSON2SQL_ENUM_RECORD_SET_HPP
