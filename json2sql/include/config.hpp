//
// Created by sn0w1eo on 23.02.18.
//

#ifndef JSON2SQL_CONVERTER_CONFIG_HPP
#define JSON2SQL_CONVERTER_CONFIG_HPP


#include <cstdint>
#include "document.h"

namespace COLUMN_TITLES {
    const char * const REFERENCE_FIELD = "DBC_REF_ID";  // title for REFERENCE field
    const char * const PRIMARY_KEY_FIELD = "DBC_ID";  // title for PRIMARY_KEY field
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
    Field_ValueTypeUndefined = 0x01,
    Record_IdFieldUndefined = 0x02,
    EnumRecordSet_HashTableMethodCalled = 0x03,
    HashRecordSet_EnumTableMethodCalled = 0x04,
    HashRecordSet_Add_TitleUndefined = 0x06,
    EnumRecordSet_Ctor_OwnerTableUndefined = 0x07,
    EnumRecordSet_AddRecord_ValueUndefined = 0x08,
    HashRecordSet_Ctor_OwnerTableUndefined = 0x09,
    HashRecordSet_Add_ValueUndefined = 0x0A,
    EnumRecordSet_AddRecord_ParentTableCurrentIdRecordIsZero = 0x0B,
    HashRecordSet_Add_RecordUndefined = 0x0C,
    HashRecordSet_Add_TitleNotString = 0x0D
};

#endif //JSON2SQL_CONFIG_HPP
