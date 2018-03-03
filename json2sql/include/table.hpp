//
// Created by sn0w1eo on 25.02.18.
//

#ifndef JSON2SQL_TABLE_HPP
#define JSON2SQL_TABLE_HPP

#include <cstdint>
#include <document.h>
#include "record_set.hpp"

namespace DBConvert {
    namespace Structures {

        class Table {
        protected:
            explicit Table(const uint32_t guid, rapidjson::Value *title, const uint16_t depth, const Table *parent)
                    : title_(title), guid_(guid), depth_(depth), parent_(parent) {};
            const Table * parent_;
            uint32_t      guid_;
            uint16_t      depth_;
            rapidjson::Value * title_;
        public:
            virtual ~Table();
            virtual uint32_t      get_guid()       const = 0;
            virtual uint16_t      get_depth()      const = 0;
            virtual const Table * get_parent()     const = 0;
            virtual RecordSet   * get_record_set() const = 0;
            virtual rapidjson::Value * get_title() const = 0;
        };
        inline Table::~Table() {
            title_ = nullptr;
            parent_ = nullptr;
        }
    }
}

#endif //JSON2SQL_TABLE_HPP
