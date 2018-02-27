//
// Created by sn0w1eo on 26.02.18.
//

#include <record_set.hpp>

namespace Structures {

    RecordSet::~RecordSet() {
        id_field_ = nullptr;
        ref_id_field_ = nullptr;
        for (Record * record : *records_)
        {
            delete record;
        }
        delete records_;
        for (Field * field : *fields_)
        {
            delete field;
        }
        delete fields_;
    }

    Field* RecordSet::find_field_by_title(const rapidjson::Value *title, std::vector<Field*> *fields) {
        for (auto * field : *fields) {
            if (strcmp(title->GetString(), field->get_title()) == 0) return field;
        }
        return nullptr;
    }
}