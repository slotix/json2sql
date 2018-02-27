//
// Created by sn0w1eo on 26.02.18.
//

#ifndef JSON2SQL_CONVERTER_HASH_RECORD_SET_HPP
#define JSON2SQL_CONVERTER_HASH_RECORD_SET_HPP

#include "record_set.hpp"
#include "table.hpp"

namespace DBConvert {
    namespace Structures {

        class HashRecordSet : public RecordSet {
        private:
            Table *owner_table_ = nullptr;
        public:
            explicit HashRecordSet(Table *owner_table);
            ~HashRecordSet() final;
            void new_record_begin() final;
            void add(const rapidjson::Value *title, rapidjson::Value *value) final;

            // EnumTable only
            void add_record(rapidjson::Value *value) final { throw HashRecordSet_EnumTableMethodCalled; }
            void add_null_record() final { throw HashRecordSet_EnumTableMethodCalled; }
        };
    }
}

#endif //JSON2SQL_HASH_RECORD_SET_HPP
