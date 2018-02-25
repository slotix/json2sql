//
// Created by sn0w1eo on 25.02.18.
//

#ifndef JSON2SQL_HASH_TABLE_HPP
#define JSON2SQL_HASH_TABLE_HPP

#include "table.hpp"
#include <cstdint>

namespace Structures {
    class HashTable : public Table {
    public:
        explicit HashTable(const uint32_t & guid, const rapidjson::Value * title, const uint16_t & depth, const Table * parent) :
                Table(guid, title, depth, parent) {};
        ~HashTable() final;

        const char  * get_title()  const override { return title_->GetString(); }
        uint32_t      get_guid()   const override { return guid_; }
        uint16_t      get_depth()  const override { return depth_; }
        const Table * get_parent() const override { return parent_; }
    };

    inline HashTable::~HashTable() { }
}

#endif //JSON2SQL_HASH_TABLE_HPP
