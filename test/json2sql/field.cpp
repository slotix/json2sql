//
// Created by sn0w1eo on 23.02.18.
//

#include <gtest/gtest.h>
#include "field.hpp"

namespace {
    using rapidjson::Value;
    using namespace DBConvert::Structures;

    class FieldTest : public ::testing::Test {
    protected:
        void SetUp() {
            value.SetString("TestTitle");
            field = new Field(value.GetString());
        }
        void TearDown() {
            delete field;
        }
        Field * field;
        rapidjson::Value value;
    };

    TEST_F(FieldTest, TitlePtrEqualsToValueStringPtr) {
        EXPECT_EQ(value.GetString(), field->get_title());
    }

    TEST_F(FieldTest, UpdateInteger) {
        Value intVal;
        intVal.SetInt(11);
        field->update(&intVal);
        EXPECT_EQ(field->get_type(), FIELD_TYPE::NUMBER);
        EXPECT_EQ(field->get_length(), sizeof(uint32_t));
    }

    TEST_F(FieldTest, UpdateInteger64) {
        Value intVal;
        intVal.SetUint64(10000000000);
        field->update(&intVal);
        EXPECT_EQ(field->get_type(), FIELD_TYPE::NUMBER);
        EXPECT_EQ(field->get_length(), sizeof(uint64_t));
    }

    TEST_F(FieldTest, UpdateDouble) {
        Value doubleVal;
        doubleVal.SetDouble(11.12);
        field->update(&doubleVal);
        EXPECT_EQ(field->get_type(), FIELD_TYPE::DOUBLE);
        EXPECT_EQ(field->get_length(), sizeof(double));
    }

    TEST_F(FieldTest, UpdateTrue) {
        Value trueVal;
        trueVal.SetBool(true);
        field->update(&trueVal);
        EXPECT_EQ(field->get_type(), FIELD_TYPE::BOOLEAN);
        EXPECT_EQ(field->get_length(), sizeof(bool));
    }

    TEST_F(FieldTest, UpdateFalse) {
        Value falseVal;
        falseVal.SetBool(false);
        field->update(&falseVal);
        EXPECT_EQ(field->get_type(), FIELD_TYPE::BOOLEAN);
        EXPECT_EQ(field->get_length(), sizeof(bool));
    }

    TEST_F(FieldTest, UpdateString) {
        Value strVal;
        strVal.SetString("TestString");
        field->update(&strVal);
        EXPECT_EQ(field->get_type(), FIELD_TYPE::TEXT);
        EXPECT_EQ(field->get_length(), strlen(strVal.GetString()));
    }

    TEST_F(FieldTest, UpdateNull) {
        Value nullVal;
        nullVal.SetNull();
        field->update(&nullVal);
        EXPECT_EQ(field->get_type(), FIELD_TYPE::NULLS);
        EXPECT_EQ(field->get_length(), 0);
    }

    TEST_F(FieldTest, UpdateUnusedTypes) {
        Value unVal;
        unVal.SetObject();
        try {
            field->update(&unVal);
        } catch (ERROR_CODES & err) {
            EXPECT_EQ(err, ERROR_CODES::Field_ValueTypeUndefined);
        } catch(...) {
            FAIL();
        }
        unVal.SetArray();
        try {
            field->update(&unVal);
        } catch (ERROR_CODES & err) {
            EXPECT_EQ(err, ERROR_CODES::Field_ValueTypeUndefined);
        } catch(...) {
            FAIL();
        }
    }

    TEST_F(FieldTest, UpdateLengthOfField) {
        Value intVal(10);
        Value strVal("FIVE5");
        field->update(&intVal);
        field->update(&strVal);
        EXPECT_EQ(field->get_length(), 5);
    }
}

