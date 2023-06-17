#include "sql_select_query_builder.h"
#include <iostream>
#include <cassert>


int main() 
{
    {
        SqlSelectQueryBuilder query_builder;
        query_builder.AddColumn("name").AddColumn("phone");
        query_builder.AddFrom("students");
        query_builder.AddWhere("id", "42").AddWhere("name", "John");

        assert(query_builder.BuildQuery() == std::string("SELECT name, phone FROM students WHERE id=42 AND name=John;"));
    }

    {
        SqlSelectQueryBuilder query_builder;
        query_builder.AddColumn("*");
        query_builder.AddFrom("students");

        //std::cout << query_builder.BuildQuery();
        assert(query_builder.BuildQuery() == std::string("SELECT * FROM students;"));
    }

    {
        SqlSelectQueryBuilder query_builder;
        query_builder.AddFrom("students").AddFrom("teachers");

        //std::cout << query_builder.BuildQuery();
        assert(query_builder.BuildQuery() == std::string("SELECT * FROM teachers;"));
    }

    {
        SqlSelectQueryBuilder query_builder;
        query_builder.AddColumn("name").AddColumn("phone").AddFrom("students").AddWhere("id", "1");
        assert(query_builder.BuildQuery() == std::string("SELECT name, phone FROM students WHERE id=1;"));
    }

    {
        SqlSelectQueryBuilder query_builder;
        std::vector<std::string> columns_names = { "name", "phone" };
        query_builder.AddColumns(columns_names);
        query_builder.AddFrom("students");
        std::map<std::string, std::string> conditions = { {"id", "42"}, {"name", "John"} };
        query_builder.AddWhere(conditions);

        assert(query_builder.BuildQuery() == std::string("SELECT name, phone FROM students WHERE id=42 AND name=John;"));
    }

}