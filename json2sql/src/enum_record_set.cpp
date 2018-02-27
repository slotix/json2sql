//
// Created by sn0w1eo on 26.02.18.
//

#include <enum_record_set.hpp>

namespace DBConvert {
    namespace Structures {

        EnumRecordSet::~EnumRecordSet() {
            enum_field_ = nullptr;
            owner_table_ = nullptr;
            id_field_ = nullptr;
            ref_id_field_ = nullptr;
            delete null_value;
        }

        EnumRecordSet::EnumRecordSet(Table *owner_table) : owner_table_(owner_table), null_value(new rapidjson::Value) {
            null_value->SetNull();
            if (owner_table_ == nullptr) throw EnumRecordSet_Ctor_OwnerTableUndefined;
            fields_->push_back(new Field(COLUMN_TITLES::PRIMARY_KEY_FIELD));
            id_field_ = fields_->back();
            if (owner_table->get_parent() != nullptr) {
                fields_->push_back(new Field(COLUMN_TITLES::REFERENCE_FIELD));
                ref_id_field_ = fields_->back();
            }
            fields_->push_back(new Field(COLUMN_TITLES::ENUM_FIELD));
            enum_field_ = fields_->back();
        }

        void EnumRecordSet::add_record(rapidjson::Value *value) {
            if (value == nullptr) throw EnumRecordSet_AddRecord_ValueUndefined;
            ++current_id_;
            uint64_t ref_id_value = 0;
            if (owner_table_->get_parent()) {
                ref_id_value = owner_table_->get_parent()->get_record_set()->get_current_id();
                if (!ref_id_value) throw EnumRecordSet_AddRecord_ParentTableCurrentIdRecordIsZero;
            }
            records_->push_back(new Record(id_field_, ref_id_field_, current_id_, ref_id_value));
            records_->back()->add(enum_field_, value);
            enum_field_->update(value);
        }

        void EnumRecordSet::add_null_record() {
            add_record(null_value);
        }
    }
}