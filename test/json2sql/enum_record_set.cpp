//
// Created by sn0w1eo on 26.02.18.
//

#include <gtest/gtest.h>
#include <hash_table.hpp>
#include <enum_table.hpp>
#include "enum_record_set.hpp"

namespace {
    using rapidjson::Value;
    using namespace Structures;
    class EnumRecordSetTest : public ::testing::Test {
    protected:
        void SetUp() {
            any_value_ptr = new Value;
            any_value_ptr->SetString("Any Value");
            any_value_ptr2 = new Value;
            any_value_ptr2->SetDouble(42.42);

            parent_title = new Value;
            parent_title->SetString("Parent Table");
            child_title = new Value;
            child_title->SetString("Child Table");
            parent_table = new EnumTable(1, parent_title, 0, nullptr);
            child_table = new EnumTable(2, child_title, 0, parent_table);

            parent_rs = parent_table->get_record_set();
            child_rs = child_table->get_record_set();
        }
        void TearDown() {
            parent_rs = nullptr;
            child_rs = nullptr;
            delete parent_table;
            delete child_table;
            delete parent_title;
            delete child_title;

            delete any_value_ptr;
            delete any_value_ptr2;
        }
        Value * parent_title;
        Value * child_title;
        Table * parent_table;
        Table * child_table;
        RecordSet * parent_rs;
        RecordSet * child_rs;

        Value * any_value_ptr;
        Value * any_value_ptr2;
    };

    TEST_F(EnumRecordSetTest, CtorOwnerTableNullException) {
        try {
            EnumRecordSet ers(nullptr);
            FAIL();
        } catch (const ERROR_CODES & err) {
            EXPECT_EQ(err, ERROR_CODES::EnumRecordSet_Ctor_OwnerTableUndefined);
        } catch(...) {
            FAIL();
        }
    }

    TEST_F(EnumRecordSetTest, CtorCreatesAndPushesBackIdFieldInCtorAsFirstElement) {
        EnumRecordSet ers(parent_table);
        EXPECT_TRUE( strcmp(ers.get_fields()->at(0)->get_title(), COLUMN_TITLES::PRIMARY_KEY_FIELD) == 0 );
    }

    TEST_F(EnumRecordSetTest, CtorCreatesAndPushesBackRefIdFieldAsSecondElementIfParentExists) { ;
        EnumRecordSet ers(child_table);
        EXPECT_TRUE( strcmp(ers.get_fields()->at(1)->get_title(), COLUMN_TITLES::REFERENCE_FIELD) == 0 );
    }

    TEST_F(EnumRecordSetTest, CtorCreatesAndPushesBackEnumFieldAsThirdElementIfParentExists) {
        EnumRecordSet child_rs(child_table);
        EXPECT_TRUE( strcmp(child_rs.get_fields()->at(2)->get_title(), COLUMN_TITLES::ENUM_FIELD) == 0 );

    }

    TEST_F(EnumRecordSetTest, CtorCreatesAndPushesBackEnumFieldAsSecondElementIfNoParent) {
        EnumRecordSet parent_rs(parent_table);
        EXPECT_TRUE( strcmp(parent_rs.get_fields()->at(1)->get_title(), COLUMN_TITLES::ENUM_FIELD) == 0 );
    }


    TEST_F(EnumRecordSetTest, AddRecordNullValuePtrException) {
        try {
            parent_rs->add_record(nullptr);
            FAIL();
        } catch (const ERROR_CODES err) {
            EXPECT_EQ(err, ERROR_CODES::EnumRecordSet_AddRecord_ValueUndefined);
        } catch(...) {
            FAIL();
        }
    }

    TEST_F(EnumRecordSetTest, AddRecordIncreaseCurrentIdEachTime) {
        parent_rs->add_record(any_value_ptr);
        EXPECT_EQ(parent_rs->get_current_id(), 1);
        parent_rs->add_record(any_value_ptr2);
        EXPECT_EQ(parent_rs->get_current_id(), 2);
        EXPECT_EQ(parent_rs->get_records()->size(), 2);
    }

    TEST_F(EnumRecordSetTest, AddRecordAddsNewRecordWithIdAndValueInEnumField) {
        Field * id_field = parent_rs->get_fields()->at(0);
        Field * enum_field = parent_rs->get_fields()->at(1);   // if ParentTable exists enum_field will be ->at(2) otherwise ->at(1)

        parent_rs->add_record(any_value_ptr);
        EXPECT_EQ(parent_rs->get_records()->back()->get_value(id_field)->GetInt64(), 1);
        EXPECT_EQ(parent_rs->get_records()->back()->get_value(enum_field), any_value_ptr);
        parent_rs->add_record(any_value_ptr2);
        EXPECT_EQ(parent_rs->get_records()->back()->get_value(id_field)->GetInt64(), 2);
        EXPECT_EQ(parent_rs->get_records()->back()->get_value(enum_field), any_value_ptr2);
    }

    TEST_F(EnumRecordSetTest, AddRecordAddsNewRecordWithIdRefIfParentTableExists) {
        parent_rs->add_record(any_value_ptr);
        child_rs->add_record(any_value_ptr2);

        Field * child_ref_id_field = child_rs->get_fields()->at(1);
        uint64_t parent_current_id = parent_rs->get_current_id();
        uint64_t child_ref_id = child_rs->get_records()->back()->get_value(child_ref_id_field)->GetUint64();
        EXPECT_EQ(child_ref_id, parent_current_id);
    }

    TEST_F(EnumRecordSetTest, AddRecordExceptionIfParentExistsButParentCurrentIdRecordIsZero) {
        try{
            child_rs->add_record(any_value_ptr);
            FAIL();
        } catch(const ERROR_CODES & err) {
            EXPECT_EQ(err, ERROR_CODES::EnumRecordSet_AddRecord_ParentTableCurrentIdRecordIsZero);
        } catch(...) {
            FAIL();
        }
    }

    TEST_F(EnumRecordSetTest, AddRecordUpdatesEnumField) {
        Field * enum_field = parent_rs->get_fields()->at(1); // 1 if parent table, 2 child if child table
        EXPECT_EQ(enum_field->get_length(), 0);
        Value v1; v1.SetInt(12);  // length is sizeof(uint32_t)
        parent_rs->add_record(&v1);
        EXPECT_EQ(enum_field->get_length(), sizeof(uint32_t));
        Value v2; v2.SetString("123456789"); // length is 9
        parent_rs->add_record(&v2);
        EXPECT_EQ(enum_field->get_length(), strlen(v2.GetString()));
    }

    TEST_F(EnumRecordSetTest, AddNullRecordAddsValueSetNullToRecords) {
        Field * enum_field = parent_rs->get_fields()->at(1); // 1 if parent table, 2 child if child table
        parent_rs->add_null_record();
        Record * added_record = parent_rs->get_records()->back();
        EXPECT_TRUE( added_record->get_value(enum_field)->IsNull() );
        parent_rs->add_null_record();
        added_record = parent_rs->get_records()->back();
        EXPECT_TRUE( added_record->get_value(enum_field)->IsNull() );
        EXPECT_EQ( parent_rs->get_records()->size(), 2);
    }

}