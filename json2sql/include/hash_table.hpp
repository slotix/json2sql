//
// Created by sn0w1eo on 25.02.18.
//

#ifndef JSON2SQL_HASH_TABLE_HPP
#define JSON2SQL_HASH_TABLE_HPP

#include "table.hpp"
#include "hash_record_set.hpp"
#include <cstdint>

namespace DBConvert {
    namespace Structures {

        class HashTable : public Table {
        private:
            HashRecordSet * hash_record_set_;
        public:
            explicit HashTable(const uint32_t &guid, rapidjson::Value *title, const uint16_t &depth, const Table *parent)
                    : Table(guid, title, depth, parent), hash_record_set_(new HashRecordSet(this)) {};
            ~HashTable() final;
            RecordSet   * get_record_set() const override { return hash_record_set_; }
            uint32_t      get_guid()       const override { return guid_; }
            uint16_t      get_depth()      const override { return depth_; }
            const Table * get_parent()     const override { return parent_; }
            rapidjson::Value * get_title() const override { return title_; }
        };
        inline HashTable::~HashTable() { delete hash_record_set_; }
    }
}

#endif //JSON2SQL_HASH_TABLE_HPP
