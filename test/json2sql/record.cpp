//
// Created by sn0w1eo on 25.02.18.
//
#include "record.hpp"
#include <gtest/gtest.h>
#include "config.hpp"

namespace {
    using namespace Structures;

    class RecordConstructorTest : public ::testing::Test {
    protected:
        void SetUp() {
            id_field = new Field(COLUMN_TITLES::PRIMARY_KEY_FIELD);
            id_reference_field = new Field(COLUMN_TITLES::REFERENCE_FIELD);
        }
        void TearDown() {
            delete id_field;
            delete id_reference_field;
        }
        Record * record;
        Field * id_field;
        Field * id_reference_field;
    };

    TEST_F(RecordConstructorTest, IdFieldPtrCanNotBeNull) {
        try {
            record = new Record(nullptr, nullptr, 1, 0);
            delete record;
            FAIL();
        } catch (const ERROR_CODES & err) {
            EXPECT_EQ(err, RECORD__ID_FIELD_UNDEFINED);
        } catch (...) {
            FAIL();
        }
    }

    TEST_F(RecordConstructorTest, IdReferenceFieldPtrCanBeNull) {
        EXPECT_NO_THROW(record = new Record(id_field, nullptr, 1, 0));
        delete record;
    }

    TEST_F(RecordConstructorTest, IdStoresAsValueAssociatedWithIdFieldInMap) {
        uint64_t id = 10;
        uint64_t any_ref_id = 1;
        EXPECT_NO_THROW(record = new Record(id_field, id_reference_field, id, any_ref_id));
        EXPECT_EQ(record->get_value(id_field)->GetInt64(), id);
        delete record;
    }

    TEST_F(RecordConstructorTest, RefIdStoresAsValueAssociatedWithIdFieldInMap) {
        uint64_t ref_id = 1;
        uint64_t any_id = 0;
        EXPECT_NO_THROW(record = new Record(id_field, id_reference_field, any_id, ref_id));
        EXPECT_EQ(record->get_value(id_reference_field)->GetInt64(), ref_id);
        delete record;
    }



    class RecordTest : public ::testing::Test {
    protected:
        void SetUp() {
            id_field = new Field(COLUMN_TITLES::PRIMARY_KEY_FIELD);
            id_reference_field = new Field(COLUMN_TITLES::REFERENCE_FIELD);
            record = new Record(id_field, id_reference_field, 1, 1);
        }
        void TearDown() {
            delete record;
            delete id_field;
            delete id_reference_field;
        }
        Record * record;
        Field * id_field;
        Field * id_reference_field;
    };

    TEST_F(RecordTest, AddFieldPtrAndAssosiatedValuePtrIntoMap) {
        Field * field;
        field = new Field("Number");
        rapidjson::Value * value;
        value = new rapidjson::Value;
        value->SetInt(42);
        EXPECT_NO_THROW(record->add(field, value));
        EXPECT_EQ(record->get_value(field), value);
        delete field;
        delete value;
    }

}