//
// Created by sn0w1eo on 26.02.18.
//

#include "hash_record_set.hpp"

namespace DBConvert {
    namespace Structures {

        HashRecordSet::HashRecordSet(Table *owner_table)
                : RecordSet(), owner_table_(owner_table) {
            if (owner_table_ == nullptr) throw HashRecordSet_Ctor_OwnerTableUndefined;
            fields_->push_back(new Field(COLUMN_TITLES::PRIMARY_KEY_FIELD));
            id_field_ = fields_->back();
            if (owner_table->get_parent() != nullptr) {
                fields_->push_back(new Field(COLUMN_TITLES::REFERENCE_FIELD));
                ref_id_field_ = fields_->back();
            }
        }

        HashRecordSet::~HashRecordSet() {
            owner_table_ = nullptr;
            id_field_ = nullptr;
            ref_id_field_ = nullptr;
        }

        void HashRecordSet::new_record_begin() {
            ++current_id_;
            uint64_t ref_id_value = 0;
            if (owner_table_->get_parent())
                ref_id_value = owner_table_->get_parent()->get_record_set()->get_current_id();
            records_->push_back(new Record(id_field_, ref_id_field_, current_id_, ref_id_value));
        }

        void HashRecordSet::add(const rapidjson::Value *title, rapidjson::Value *value) {
            if (title == nullptr) throw HashRecordSet_Add_TitleUndefined;
            if (value == nullptr) throw HashRecordSet_Add_ValueUndefined;
            if (current_id_ == 0) throw HashRecordSet_Add_RecordUndefined;
            if (!title->IsString()) throw HashRecordSet_Add_TitleNotString;
            Record *record = records_->back();
            Field *field = find_field_by_title(title, fields_);
            if (field == nullptr) {
                fields_->push_back(new Field(title->GetString()));
                field = fields_->back();
            }
            record->add(field, value);
            field->update(value);
        }
    }
}