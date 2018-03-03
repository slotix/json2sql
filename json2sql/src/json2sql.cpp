//
// Created by sn0w1eo on 02.03.18.
//

#include <filereadstream.h>
#include <enum_table.hpp>
#include <hash_table.hpp>
#include <iostream>
#include "json2sql.hpp"

namespace DBConvert {

    json2sql::~json2sql() {
        for (auto it = tables_.rbegin(); it != tables_.rend(); ++it)
        {
            delete *it;
        }
    }

    void json2sql::parse() {
        try {
            if (text_json_) {
                document_json_.Parse(text_json_);
            } else {
                char buffer[buffer_read_size];
                rapidjson::FileReadStream is(file_json_, buffer, sizeof(buffer));
                document_json_.ParseStream(is);
            }
        } catch (...) {
            throw ERROR_CODES::Parse_Error;
        }
        switch (document_json_.GetType()) {
            case rapidjson::kObjectType:
                hash_entry(document_json_, nullptr, 0, nullptr);
                break;
            case rapidjson::kArrayType:
                enum_entry(document_json_, nullptr, 0, nullptr);
                break;
        }
    }

    void json2sql::hash_entry(rapidjson::Value &entry, rapidjson::Value *title, uint16_t depth, Structures::Table *parent) {
        Structures::Table * table = add_table(title, depth, parent, true);
        table->get_record_set()->new_record_begin();
        for (auto & hash : entry.GetObject()) {
            switch (hash.value.GetType()) {
                case rapidjson::kObjectType:
                    hash_entry(hash.value, &hash.name, depth + 1, table);
                    break;
                case rapidjson::kArrayType:
                    enum_entry(hash.value, &hash.name, depth + 1, table);
                    break;
                default:
                    table->get_record_set()->add(&hash.name, &hash.value);
            }
        }
    }

    void json2sql::enum_entry(rapidjson::Value &entry, rapidjson::Value *title, uint16_t depth, Structures::Table *parent) {
        Structures::Table * table = add_table(title, depth, parent, false);
        for (auto & value : entry.GetArray()) {
            switch (value.GetType()) {
                case rapidjson::kObjectType:
                    table->get_record_set()->add_null_record();
                    hash_entry(value, nullptr, depth + 1, table);
                    break;
                case rapidjson::kArrayType:
                    table->get_record_set()->add_null_record();
                    enum_entry(value, nullptr, depth + 1, table);
                    break;
                default:
                    table->get_record_set()->add_record(&value);
            }
        }
    }

    Structures::Table * json2sql::add_table(rapidjson::Value *title, uint16_t depth, Structures::Table *parent, bool isHashTable = true) {
        for (auto * table : tables_) {
            if (find_table_by_title(table, title) && (table->get_depth() == depth))
                return table;
        }
        guid_++;
        if (isHashTable) tables_.push_back(new Structures::HashTable(guid_, title, depth, parent));
        else tables_.push_back(new Structures::EnumTable(guid_, title, depth, parent));
        return tables_.back();
    }

    bool json2sql::find_table_by_title(const Structures::Table *table, const rapidjson::Value *title) {
        if (table->get_title() == nullptr && title == nullptr) return true;
        if (table->get_title() != nullptr && title != nullptr) {
            if (std::strcmp(table->get_title()->GetString(), title->GetString()) == 0) return true;
        }
        return false;
    }
}