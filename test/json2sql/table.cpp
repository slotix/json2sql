//
// Created by sn0w1eo on 26.02.18.
//

#include <gtest/gtest.h>
#include "document.h"
#include "table.hpp"
#include "hash_table.hpp"
#include "enum_table.hpp"

namespace {
    using namespace Structures;
    class TableTest : public ::testing::Test {
    protected:
        void SetUp() {
            hash_table_title_ptr = new rapidjson::Value;
            hash_table_title_ptr->SetString("Hash Table Title");
            enum_table_title_ptr = new rapidjson::Value;
            enum_table_title_ptr->SetString("Enum Table Title");
        }
        void TearDown() {
            delete hash_table_title_ptr;
            delete enum_table_title_ptr;
        }
        rapidjson::Value * hash_table_title_ptr;
        rapidjson::Value * enum_table_title_ptr;
        uint32_t hash_table_guid = 1;
        uint32_t enum_table_guid = 2;
        uint16_t hash_table_depth = 3;
        uint16_t enum_table_depth = 4;
    };

    TEST_F(TableTest, RecordSetAllocated) {
        HashTable h_table(hash_table_guid, hash_table_title_ptr, hash_table_depth, nullptr);
        EnumTable e_table(enum_table_guid, enum_table_title_ptr, enum_table_depth, nullptr);
        EXPECT_TRUE(h_table.get_record_set() != nullptr);
        EXPECT_TRUE(e_table.get_record_set() != nullptr);
    }


    TEST_F(TableTest, HashTableCanAcceptEnumTableAsParent) {
        EnumTable e_table(enum_table_guid, enum_table_title_ptr, enum_table_depth, nullptr);
        HashTable h_table(hash_table_guid, hash_table_title_ptr, hash_table_depth, &e_table);
        EXPECT_EQ(h_table.get_parent(), &e_table);
        EXPECT_EQ(h_table.get_parent()->get_title(), enum_table_title_ptr->GetString());
        EXPECT_EQ(h_table.get_parent()->get_guid(), enum_table_guid);
        EXPECT_EQ(h_table.get_parent()->get_depth(), enum_table_depth);
    }

    TEST_F(TableTest, EnumTableCanAcceptHashTableAsParent) {
        HashTable h_table(hash_table_guid, hash_table_title_ptr, hash_table_depth, nullptr);
        EnumTable e_table(enum_table_guid, enum_table_title_ptr, enum_table_depth, &h_table);
        EXPECT_EQ(e_table.get_parent(), &h_table);
        EXPECT_EQ(e_table.get_parent()->get_title(), hash_table_title_ptr->GetString());
        EXPECT_EQ(e_table.get_parent()->get_guid(), hash_table_guid);
        EXPECT_EQ(e_table.get_parent()->get_depth(), hash_table_depth);
    }
}