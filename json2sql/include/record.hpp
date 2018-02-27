//
// Created by sn0w1eo on 25.02.18.
//

#ifndef JSON2SQL_RECORD_HPP
#define JSON2SQL_RECORD_HPP

#include <cstdint>
#include <map>
#include "field.hpp"
#include "document.h"

namespace DBConvert {
    namespace Structures {

        class Record {
        private:
            std::map<Field*, rapidjson::Value*> value_;  //stores Value for each Field in map structure
            rapidjson::Value * id_;  // integer ID field number represented as Value
            rapidjson::Value * reference_id_; // integer REF_ID field number represented as Value
        public:
            explicit Record(Field *id_field, Field *ref_id_field, uint64_t id, uint64_t ref_id);
            ~Record();
            void add(Field *field, rapidjson::Value *value);
            std::map<Field*, rapidjson::Value*> * get_values()            { return &value_; }
            rapidjson::Value                    * get_value(Field *field) { return value_[field]; }
        };
    }
}

#endif //JSON2SQL_RECORD_HPP
