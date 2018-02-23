//
// Created by sn0w1eo on 23.02.18.
//

#ifndef JSON2SQL_CONVERTER_FIELD_HPP
#define JSON2SQL_CONVERTER_FIELD_HPP

#include <cstdint>
#include "config.hpp"
#include "document.h"

using rapidjson::Value;

class Field {
private:
    const char * title_;
    uint64_t length_;
    uint8_t type_;
public:
    explicit Field(const char * title) : title_(title), length_(0), type_(FIELD_TYPE::UNDEFINED) {};

    ~Field();

    const char * get_title() const { return title_; };
    uint64_t get_length() const { return length_; };
    uint8_t get_type() const;
    void update(Value * value);
};

#endif
