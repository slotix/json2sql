//
// Created by sn0w1eo on 25.02.18.
//

#ifndef JSON2SQL_TABLE_HPP
#define JSON2SQL_TABLE_HPP
#include <cstdint>
#include <iostream>
#include <document.h>

namespace Structures {

    class Table {
    public:
        virtual ~Table() { title_ = nullptr; parent_ = nullptr; }
        virtual uint32_t get_guid() const = 0;
        virtual const char *get_title() const = 0;
        virtual uint16_t get_depth() const = 0;
        virtual const Table *get_parent() const = 0;
    protected:
        explicit Table(const uint32_t guid, const rapidjson::Value *title, const uint16_t depth, const Table *parent) :
                title_(title),
                guid_(guid),
                depth_(depth),
                parent_(parent) {};

        const rapidjson::Value *title_;
        const Table *parent_;
        uint32_t guid_;
        uint16_t depth_;
    };
}
#endif //JSON2SQL_TABLE_HPP
