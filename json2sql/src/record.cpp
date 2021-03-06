//
// Created by sn0w1eo on 25.02.18.
//

#include "record.hpp"

namespace DBConvert {
    namespace Structures {

        Record::Record(Field *id_field, Field *ref_id_field, const uint64_t id, const uint64_t ref_id)
                : id_(new rapidjson::Value), reference_id_(new rapidjson::Value) {
            id_->SetUint64(id);
            if (!id_field) throw Record_IdFieldUndefined;
            add(id_field, id_);
            if (ref_id && ref_id_field) {
                reference_id_->SetUint64(ref_id);
                add(ref_id_field, reference_id_);
            }
        }

        Record::~Record() {
            value_.clear();
            delete id_;
            delete reference_id_;
        }

        void Record::add(Field *field, rapidjson::Value *value) {
            value_.emplace(field, value);
        }
    }
}