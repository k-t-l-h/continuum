#include "DataBase.h"

DataBase::DataBase() {
    sql::connection_config config;
    config.password = "";
    config.path_to_database = "/home/evgeny/temp.db";
    config.flags = SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE;
    config.debug = false;
    db = new sql::connection(config);
    try {
        DB->execute("CREATE TABLE reporters (\
            id INTEGER PRIMARY KEY AUTOINCREMENT,\
            report varchar(255) DEFAULT NULL\
        )");
    }
    catch (sqlpp::exception e) {
        std::cerr << e.what() << std::endl;
    }
}

DataBase::~DataBase() {
    delete db;
}

void DataBase::insert(std::string report) {
    auto i = insert_into(reporters).columns(reporters.report);
    i.values.add(reporters.report = report);
    (*db)(i);
}

bool DataBase::select(int id, std::string &report) {
    for (const auto& row : (*db)(select(reporters.report).from(reporters).where(reporters.id == id))) {
        if (row.report.is_null()) {
            return false;
        }
        report = row.report;
        return true;
    }
}