//
// Created by sn0w1eo on 25.02.18.
//

#ifndef JSON2SQL_ENUM_TABLE_HPP
#define JSON2SQL_ENUM_TABLE_HPP

#include "table.hpp"
#include <cstdint>

namespace Structures {
    class EnumTable : public Table {
    public:
        explicit EnumTable(const uint32_t & guid, const rapidjson::Value * title, const uint16_t & depth, const Table * parent) :
                Table(guid, title, depth, parent) {};
        ~EnumTable() final;

        const char  * get_title()  const override { return title_->GetString(); }
        uint32_t      get_guid()   const override { return guid_; }
        uint16_t      get_depth()  const override { return depth_; }
        const Table * get_parent() const override { return parent_; }
    };

    inline EnumTable::~EnumTable() {}
}
#endif //JSON2SQL_ENUM_TABLE_HPP
