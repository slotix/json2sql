//
// Created by sn0w1eo on 23.02.18.
//

#ifndef JSON2SQL_CONVERTER_CONFIG_HPP
#define JSON2SQL_CONVERTER_CONFIG_HPP


#include <cstdint>

namespace COLUMN_TITLES {
    const char * const REFERENCE_FIELD = "DBC_REF_ID";
    const char * const PRIMARY_KEY_FIELD = "DBC_ID";
    const char * const ENUM_FIELD = "DBC_ENUM";

}


namespace MAIN_TABLE {
    const char * const TITLE = "DBC_MAIN_TABLE";
    const char * const KEY_FIELD = "TABLE_KEY";
    const char * const GUID_FIELD = "TABLE_GUID";
    const char * const DEPTH_FIELD = "DEPTH";

}

enum class DIALECT : uint8_t {
    SQLite = 1
    //,
    //MySQL = 2
};

enum FIELD_TYPE: uint8_t {
    UNDEFINED = 0x00,
    TEXT = 0x01,
    DOUBLE = 0x02,
    NUMBER = 0x04,
    BOOLEAN = 0x08,
    NULLS = 0x10
};

enum ERROR_CODES: uint8_t  {
    FIELD__VALUE_TYPE_UNDEFINED = 0x01
};
#endif //JSON2SQL_CONVERTER_CONFIG_HPP
