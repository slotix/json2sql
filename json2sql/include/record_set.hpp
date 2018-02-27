//
// Created by sn0w1eo on 26.02.18.
//

#ifndef JSON2SQL_RECORD_SET_HPP
#define JSON2SQL_RECORD_SET_HPP

#include <cstdint>
#include <vector>
#include "field.hpp"
#include "record.hpp"

namespace DBConvert {
    namespace Structures {

        class RecordSet {
        protected:
            std::vector<Field *>  * fields_;
            std::vector<Record *> * records_;
            uint64_t   current_id_;
            Field    * id_field_;
            Field    * ref_id_field_;
            static Field * find_field_by_title(const rapidjson::Value *title, std::vector<Field*> *fields);
        public:
            RecordSet() : fields_(new std::vector<Field *>), records_(new std::vector<Record *>),
                          current_id_(0), id_field_(nullptr), ref_id_field_(nullptr) {}
            virtual ~RecordSet();
            const std::vector<Field*>  * get_fields()     const { return fields_; }
            const std::vector<Record*> * get_records()    const { return records_; }
            uint64_t                     get_current_id() const { return current_id_; }

            // HashTable only
            virtual void new_record_begin() = 0;
            virtual void add(const rapidjson::Value *title, rapidjson::Value *value) = 0;

            // EnumTable only
            virtual void add_record(rapidjson::Value *value) = 0;
            virtual void add_null_record() = 0;
        };
    };
}

#endif //JSON2SQL_RECORD_SET_HPP
