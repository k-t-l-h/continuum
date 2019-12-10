#ifndef CONTINUUM_DATABASE_H
#define CONTINUUM_DATABASE_H
#include <iostream>
#include <sqlpp11/sqlite3/connection.h>
#include "../submodules/sqlpp11-connector-sqlite3/src/detail/connection_handle.h"
#include <sqlite3.h>
#include <sqlpp11/insert.h>
#include <sqlpp11/select.h>
#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/custom_query.h>
#include <sqlpp11/sqlite3/sqlite3.h>
#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace sql = sqlpp::sqlite3;



namespace Table_
{
    struct Id
    {
        struct _alias_t
        {
            static constexpr const char _literal[] = "id";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
            template <typename T>
            struct _member_t
            {
                T id;
                T& operator()()
                {
                    return id;
                }
                const T& operator()() const
                {
                    return id;
                }
            };
        };
        using _traits = ::sqlpp::make_traits<::sqlpp::integer, ::sqlpp::tag::can_be_null>;
    };

    struct Report
    {
        struct _alias_t
        {
            static constexpr const char _literal[] = "report";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
            template <typename T>
            struct _member_t
            {
                T report;
                T& operator()()
                {
                    return report;
                }
                const T& operator()() const
                {
                    return report;
                }
            };
        };
        using _traits = ::sqlpp::make_traits<::sqlpp::varchar,
                ::sqlpp::tag::can_be_null>;
    };

}

struct Table : sqlpp::table_t<Table, Table_::Id, Table_::Report>
{
    using _value_type = sqlpp::no_value_t;
    struct _alias_t
    {
        static constexpr const char _literal[] = "reporters";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template <typename T>
        struct _member_t
        {
            T reporters;
            T& operator()()
            {
                return reporters;
            }
            const T& operator()() const
            {
                return reporters;
            }
        };
    };
};

class Database {

public:

    Database();

    ~Database();

    void insert(std::string report);

    bool select(int id, std::string &report);

private:

    sql::connection *db;

    Table reporters;

};



#endif //TESTS_DATABASE_H
