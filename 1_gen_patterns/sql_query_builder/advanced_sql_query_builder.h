#pragma once

#include "sql_select_query_builder.h"
#include <tuple>
#include <set>

class AdvancedSqlSelectQueryBuilder : public SqlSelectQueryBuilder {

private:
    std::set<std::tuple<std::string, std::string, std::string>> _conditions_advanced;

public:

    using SqlSelectQueryBuilder::AddWhere;
    AdvancedSqlSelectQueryBuilder& AddWhere(const std::string& column, const std::string& relation, const std::string& value) {
        _conditions_advanced.insert(std::tuple(column, relation, value));
        return *this;
    }

    std::string BuildQuery() const {
        std::string query_string = SqlSelectQueryBuilder::BuildQuery();

        if (_conditions_advanced.size() == 0) {
            return query_string;
        }

        std::string advanced_conditions_str;

        if (query_string.find("WHERE") != std::string::npos) {
            advanced_conditions_str += " AND ";
        }
        else {
            advanced_conditions_str += " WHERE ";
        }

        for (auto cond_it = _conditions_advanced.begin(); cond_it != _conditions_advanced.end(); ++cond_it) {
            if (cond_it != _conditions_advanced.begin()) {
                advanced_conditions_str += " AND ";
            }
            advanced_conditions_str += std::get<0>(*cond_it) + std::get<1>(*cond_it) + std::get<2>(*cond_it);
        }

        query_string.insert(query_string.size() - 1, advanced_conditions_str);

        return query_string;
    }
};