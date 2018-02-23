//
// Created by sn0w1eo on 23.02.18.
//

#include "field.hpp"

Field::~Field() {
    title_ = nullptr;
}

void Field::update(Value * value) {
    uint64_t new_length = 0;
    switch (value->GetType()) {
        case rapidjson::kNullType:
            type_ |= FIELD_TYPE::NULLS;
            break;
        case rapidjson::kFalseType:
            type_ |= FIELD_TYPE::BOOLEAN;
            new_length = sizeof(bool);
            break;
        case rapidjson::kTrueType:
            type_ |= FIELD_TYPE::BOOLEAN;
            new_length = sizeof(bool);
            break;
        case rapidjson::kStringType:
            type_ |= FIELD_TYPE::TEXT;
            new_length = strlen(value->GetString());
            break;
        case rapidjson::kNumberType:
            if (value->IsFloat()) {
                type_ |= FIELD_TYPE::DOUBLE;
                new_length = sizeof(double);
            }
            else {
                type_ |= FIELD_TYPE::NUMBER;
                new_length = (value->IsInt() ? sizeof(uint32_t) : sizeof(uint64_t));
            }
            break;
        default:
            throw(FIELD__VALUE_TYPE_UNDEFINED);
    }
    if (length_ < new_length) length_ = new_length;
}

uint8_t Field::get_type() const {
    if (type_ & FIELD_TYPE::TEXT) return FIELD_TYPE::TEXT;
    if ((type_ - (type_ & FIELD_TYPE::NUMBER) == 0) ||
        (type_ - (FIELD_TYPE::NUMBER + FIELD_TYPE::DOUBLE) == 0)) return FIELD_TYPE::NUMBER;
    if (type_ - (type_ & FIELD_TYPE::DOUBLE) == 0) return FIELD_TYPE::DOUBLE;
    if (type_ - (type_ & FIELD_TYPE::BOOLEAN) == 0) return FIELD_TYPE::BOOLEAN;
    if (type_ - (type_ & FIELD_TYPE::NULLS) == 0) return FIELD_TYPE::NULLS;
    return FIELD_TYPE::TEXT;
}