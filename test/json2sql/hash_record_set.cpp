//
// Created by sn0w1eo on 26.02.18.
//

#include <gtest/gtest.h>
#include <random>
#include "hash_table.hpp"
#include "hash_record_set.hpp"

#define TITLE_FOR_VALUE "Field Title"

namespace {
    using rapidjson::Value;
    using namespace DBConvert::Structures;

    class HashRecordSetTest : public ::testing::Test {
    protected:
        void SetUp() {
            any_title_ptr = new Value;  // for title of field
            any_title_ptr->SetString( TITLE_FOR_VALUE );

            any_value_ptr = new Value;
            any_value_ptr->SetString("Any Value");
            any_value_ptr2 = new Value;
            any_value_ptr2->SetDouble(42.42);

            parent_title = new Value;
            parent_title->SetString("Parent Table");
            child_title = new Value;
            child_title->SetString("Child Table");
            parent_table = new HashTable(1, parent_title, 0, nullptr);
            child_table = new HashTable(2, child_title, 0, parent_table);

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

            delete any_title_ptr;
        }
        Value * parent_title;
        Value * child_title;
        Table * parent_table;
        Table * child_table;
        RecordSet * parent_rs;
        RecordSet * child_rs;

        Value * any_title_ptr;
        Value * any_value_ptr;
        Value * any_value_ptr2;
    };

    TEST_F(HashRecordSetTest, CtorOwnerTableNullException) {
        try {
            HashRecordSet hrs(nullptr);
            FAIL();
        } catch (const ERROR_CODES & err) {
            EXPECT_EQ(err, ERROR_CODES::HashRecordSet_Ctor_OwnerTableUndefined);
        } catch(...) {
            FAIL();
        }
    }

    TEST_F(HashRecordSetTest, CtorCreatesAndPushesBackIdFieldInCtorAsFirstElement) {
        HashRecordSet hrs(parent_table);
        EXPECT_TRUE( strcmp(hrs.get_fields()->at(0)->get_title(), COLUMN_TITLES::PRIMARY_KEY_FIELD) == 0 );
    }

    TEST_F(HashRecordSetTest, CtorCreatesAndPushesBackRefIdFieldAsSecondElementIfParentExists) { ;
        HashRecordSet hrs(child_table);
        EXPECT_TRUE( strcmp(hrs.get_fields()->at(1)->get_title(), COLUMN_TITLES::REFERENCE_FIELD) == 0 );
    }

    TEST_F(HashRecordSetTest, AddExceptionIfNoRecordBeginCalled) {
        try {
            parent_rs->add(any_title_ptr, any_value_ptr);
            FAIL();
        } catch (const ERROR_CODES & err) {
            EXPECT_EQ(err, ERROR_CODES::HashRecordSet_Add_RecordUndefined);
        } catch (...) {
            FAIL();
        }
    }

    TEST_F(HashRecordSetTest, NewRecordBeginCreatesRecordAndIncrementsCurrentId) {
        EXPECT_EQ(parent_rs->get_current_id(), 0);
        parent_rs->new_record_begin();
        EXPECT_EQ(parent_rs->get_current_id(), 1);
        EXPECT_EQ(parent_rs->get_records()->size(), 1);
        Field * parent_id = parent_rs->get_fields()->at(0);
        EXPECT_EQ(parent_rs->get_records()->back()->get_value(parent_id)->GetUint64(), 1);
    }

    TEST_F(HashRecordSetTest, NewRecordBeginAddRefIdValueIfParentExists) {
        std::random_device r;
        std::default_random_engine eng(r());
        std::uniform_int_distribution<int> uni(1,10);
        int parent_records_count = uni(r);
        for (int i = 1; i<=parent_records_count; i++){
            parent_rs->new_record_begin();
        }
        child_rs->new_record_begin();
        Field * ref_id_field = child_rs->get_fields()->at(1);
        uint64_t child_ref_id_value = child_rs->get_records()->back()->get_value(ref_id_field)->GetUint64();
        EXPECT_EQ(child_ref_id_value, parent_records_count);
    }

    TEST_F(HashRecordSetTest, AddNullTitlePtrException) {
        parent_rs->new_record_begin();
        try {
            parent_rs->add(nullptr, any_value_ptr);
            FAIL();
        } catch(const ERROR_CODES err) {
            EXPECT_EQ(err, ERROR_CODES::HashRecordSet_Add_TitleUndefined);
        } catch(...) {
            FAIL();
        }
    }

    TEST_F(HashRecordSetTest, AddNullValuePtrException) {
        parent_rs->new_record_begin();
        try {
            parent_rs->add(any_title_ptr, nullptr);
            FAIL();
        } catch(const ERROR_CODES & err) {
            EXPECT_EQ(err, ERROR_CODES::HashRecordSet_Add_ValueUndefined);
        } catch(...) {
            FAIL();
        }
    }

    TEST_F(HashRecordSetTest, AddExceptionIfValueNotIsString) {
        Value not_stringable;
        not_stringable.SetInt(42);
        parent_rs->new_record_begin();
        try {
            parent_rs->add(&not_stringable, any_title_ptr);
            FAIL();
        } catch(const ERROR_CODES & err) {
            EXPECT_EQ(err, ERROR_CODES::HashRecordSet_Add_TitleNotString);
        } catch(...) {
            FAIL();
        }
    }

    TEST_F(HashRecordSetTest, AddIfFieldWithSameTitleExistsUsesIt) {
        parent_rs->new_record_begin();
        parent_rs->add(any_title_ptr, any_value_ptr);
        Field * before_field = parent_rs->get_fields()->back();

        parent_rs->new_record_begin();
        Value same_title;
        same_title.SetString( TITLE_FOR_VALUE );
        parent_rs->add(&same_title, any_value_ptr2);
        Field * after_field = parent_rs->get_fields()->back();
        EXPECT_EQ(before_field, after_field);
    }

    TEST_F(HashRecordSetTest, AddSkipChangesForValueAlreadyCreatedWithSameField ) {
        parent_rs->new_record_begin();
        parent_rs->add(any_title_ptr, any_value_ptr);
        parent_rs->add(any_title_ptr, any_value_ptr2);
        Field * record_field = parent_rs->get_fields()->back();
        EXPECT_EQ( parent_rs->get_records()->back()->get_value(record_field), any_value_ptr);
        EXPECT_NE( parent_rs->get_records()->back()->get_value(record_field), any_value_ptr2);
    }

    TEST_F(HashRecordSetTest, AddCreatesFieldWithTitleIfNotExists) {
        parent_rs->new_record_begin();
        Value new_field;
        new_field.SetString("New Field");
        parent_rs->add(&new_field, any_value_ptr);
        Field * last_field = parent_rs->get_fields()->back();
        const char * last_string = parent_rs->get_records()->back()->get_value(last_field)->GetString();
        EXPECT_TRUE(std::strcmp(new_field.GetString(), last_string ));
    }

    TEST_F(HashRecordSetTest, AddUpdatesFieldLength) {
        parent_rs->new_record_begin();
        Value v1; v1.SetInt(42);
        parent_rs->add(any_title_ptr, &v1);
        Field * field_for_values = parent_rs->get_fields()->back();
        EXPECT_EQ(field_for_values->get_length(), sizeof(uint32_t));

        parent_rs->new_record_begin();
        Value v2; v2.SetString("123456789");
        parent_rs->add(any_title_ptr, &v2);
        EXPECT_EQ(field_for_values->get_length(), strlen(v2.GetString()));
    }
}