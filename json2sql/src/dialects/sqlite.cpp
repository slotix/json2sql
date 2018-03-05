//
// Created by sn0w1eo on 04.03.18.
//

#include "dialects/sqlite.hpp"
#include <algorithm>

namespace DBConvert {
    namespace Structures {
        namespace Dialect {

            SQLite::~SQLite() = default;

            void SQLite::sql_main_table()
            {
                *out_stream_ << "CREATE TABLE " << sq << MAIN_TABLE::TITLE << sq
                             << " ( ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                             << enc(MAIN_TABLE::GUID_FIELD) << " INTEGER, "
                             << enc(MAIN_TABLE::KEY_FIELD) << " TEXT, "
                             << enc(MAIN_TABLE::DEPTH_FIELD) << " INTEGER); \n";
                for (auto table : json_to_sql_->tables_)
                {
                    *out_stream_ << "INSERT INTO " << enc(MAIN_TABLE::TITLE) << " ( "
                                 << "ID, "
                                 << enc(MAIN_TABLE::GUID_FIELD) << ", "
                                 << enc(MAIN_TABLE::KEY_FIELD) << ", "
                                 << enc(MAIN_TABLE::DEPTH_FIELD) << " ) "
                                 << "VALUES ( "
                                 << table->get_guid() << ", "
                                 << table->get_guid() << ", "
                                 << enc( (table->get_title() ? table->get_title()->GetString() : nullptr) ) << ", "
                                 << table->get_depth()
                                 << " );\n";
                }
                *out_stream_ << "\n";
            }

            void SQLite::sql_table_to_ddl(Table* table)
            {
                const auto fields = table->get_record_set()->get_fields();
                uint8_t id_found_flag = 0;

                *out_stream_ << "CREATE TABLE " << sq << table->get_guid() << sq << " (\n";

                for (auto field = fields->begin(); field != fields->end(); ++field)
                {
                    *out_stream_ << enc((*field)->get_title()) << " " << sqlite_type((*field)->get_type());
                    if (!id_found_flag && (strcmp(COLUMN_TITLES::PRIMARY_KEY_FIELD, (*field)->get_title()) == 0))
                    {
                        *out_stream_ << " PRIMARY KEY AUTOINCREMENT";
                        id_found_flag = 1;
                    }
                    if (std::next(field) == fields->end())
                    {
                        if (table->get_parent())
                        {
                            *out_stream_ << ",\n" << "FOREIGN KEY (" << enc(COLUMN_TITLES::REFERENCE_FIELD)
                                         << ") REFERENCES " << sq << table->get_parent()->get_guid() << sq << " (" << enc(COLUMN_TITLES::PRIMARY_KEY_FIELD)
                                         << ")";
                        }
                    }
                    else
                    {
                        *out_stream_ << ",";
                    }
                    *out_stream_ << std::endl;
                }
                *out_stream_ << ");" << std::endl << std::endl;
            }

            void SQLite::sql_table_to_dml(Table* table)
            {
                const auto records = table->get_record_set()->get_records();

                for (auto record = records->begin(); record != records->end(); ++record)
                {
                    std::vector<std::string> fields;
                    std::vector<std::string> values;
                    for (auto field : *table->get_record_set()->get_fields())
                    {
                        const auto buff_value_ptr = (*record)->get_value(field);
                        if (buff_value_ptr)
                        {
                            fields.push_back(enc(field->get_title()));
                            values.push_back(p_value(field, buff_value_ptr));
                        };
                    }
                    *out_stream_ << "INSERT INTO " << sq << table->get_guid() << sq
                                 << " (" << vector_to_string(fields) << ") VALUES (" << vector_to_string(values) << ");" << std::endl;
                }
                *out_stream_ << std::endl;
            }

            std::string SQLite::vector_to_string(std::vector<std::string> &vec)
            {
                std::string result;
                for (auto str = vec.begin(); str != vec.end(); ++str)
                {
                    if (std::next(str) != vec.end())
                    {
                        result.append(*str);
                        result.append(", ");
                    }
                    else
                    {
                        result.append(*str);
                    }
                }
                return result;
            }

            std::string SQLite::enc(const char* str)
            {
                std::string result;
                result += sq;
                if (str) result.append(str);
                result += sq;
                return result;
            }

            void SQLite::raw_sql(std::ostream& output)
            {
                out_stream_ = &output;
                sql_main_table();
                for(Table * table : json_to_sql_->tables_)
                {
                    sql_table_to_ddl(table);
                    sql_table_to_dml(table);
                }

                out_stream_ = nullptr;
            }

            std::string SQLite::value_to_string(const rapidjson::Value * value) {
                std::string result;
                const int i = value->GetType();
                switch (i) {
                    case rapidjson::kNullType:
                        result = "NULL";
                        break;
                    case rapidjson::kFalseType:
                        result = "0";
                        break;
                    case rapidjson::kTrueType:
                        result = "1";
                        break;
                    case rapidjson::kStringType:
                        result = value->GetString();
                        if (result.length()>0) {
                            replace_all_sq(result);
                        }
                        break;
                    case rapidjson::kNumberType:
                        if (value->IsFloat()) {
                            result = std::to_string(value->GetFloat());
                        }
                        else {
                            result = std::to_string(value->GetInt64());
                        }
                        break;
                    default:
                        result = "UNDEFINED";
                }
                return result;
            }

            std::string SQLite::p_value(const Field * field, const rapidjson::Value * value)
            {
                auto result = value_to_string(value);
                switch(field->get_type())
                {
                    case FIELD_TYPE::NULLS:
                        return result;
                    case FIELD_TYPE::BOOLEAN:
                        return result;
                    default:
                        return (SQLite::sq + result + SQLite::sq);
                }
            }

            std::string& SQLite::replace_all_sq(std::string& context)
            {
                std::size_t lookHere = 0;
                std::size_t foundHere;
                while((foundHere = context.find(find_sq, lookHere)) != std::string::npos)
                {
                    context.replace(foundHere, find_sq.size(), replace_sq);
                    lookHere = foundHere + replace_sq.size();
                }
                return context;
            }
        }
    }
}