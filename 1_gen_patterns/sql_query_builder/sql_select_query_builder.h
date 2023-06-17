#pragma once

#include<string>
#include<vector>
#include<map>

class SqlSelectQueryBuilder {

private:
    std::string _table_name;
    std::vector<std::string> _column_names;
    std::multimap<std::string, std::string> _conditions;

public:

    SqlSelectQueryBuilder& AddFrom(const std::string& table_name) {
        _table_name = table_name;
        return *this;
    }

    SqlSelectQueryBuilder& AddColumn(const std::string& column_name) {
        _column_names.push_back(column_name);
        return *this;
    }

    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept {
        for (const auto& column : columns) {
            _column_names.push_back(column);
        }
        return *this;
    }


    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept {
        for (const auto& cond : kv) {
            _conditions.insert(cond);
        }
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::string& column, const std::string& value) {
        _conditions.insert(make_pair(column, value));
        return *this;
    }

    std::string BuildQuery() const {
        std::string query_string;

        query_string += "SELECT ";

        if (_column_names.empty()) {
            query_string += "*";
        }

        for (auto col_it = _column_names.begin(); col_it != _column_names.end();  ++col_it) {
            if (col_it != _column_names.begin()) {
                query_string += ", ";
            }
            query_string += *col_it;
        }

        query_string += " FROM ";
        query_string += _table_name;

        if (_conditions.size() > 0) {
            query_string += " WHERE ";
        }

        for (auto cond_it = _conditions.begin(); cond_it != _conditions.end(); ++cond_it) {
            if (cond_it != _conditions.begin()) {
                query_string += " AND ";
            }
            query_string += cond_it->first + "=" + cond_it->second;
        }

        query_string += ";";

        return query_string;
    }
};