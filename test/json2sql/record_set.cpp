//
// Created by sn0w1eo on 26.02.18.
//

#include <gtest/gtest.h>
#include "enum_table.hpp"
#include "hash_table.hpp"

namespace {
    using namespace rapidjson;
    using namespace DBConvert::Structures;

    class RecordSetTest : public ::testing::Test {
    protected:
        void SetUp() {
            h_title = new Value; h_title->SetString("HashTable Title");
            e_title = new Value; e_title->SetString("EnumTable Title");
            hash_table = new HashTable(1, h_title, 0, nullptr);
            enum_table = new EnumTable(1, e_title, 0, nullptr);
        }
        void TearDown() {
            delete h_title;
            delete e_title;
            delete hash_table;
            delete enum_table;
        }
        Value * h_title;
        Value * e_title;
        HashTable * hash_table;
        EnumTable * enum_table;
    };
}

TEST_F(RecordSetTest, RecordsVectorAllocated) {
    EXPECT_TRUE(hash_table->get_record_set()->get_records());
    EXPECT_TRUE(hash_table->get_record_set()->get_records());
}

TEST_F(RecordSetTest, FieldsVectorAllocated) {
    EXPECT_TRUE(hash_table->get_record_set()->get_fields());
    EXPECT_TRUE(hash_table->get_record_set()->get_fields());
}

TEST_F(RecordSetTest, InitializationOfRecordSetCurrentIdIsZero) {
    EXPECT_TRUE(hash_table->get_record_set()->get_current_id() == 0 );
    EXPECT_TRUE(enum_table->get_record_set()->get_current_id() == 0 );
}

