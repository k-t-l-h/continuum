#include "DataBase.h"

DataBase::DataBase() {
    sql::connection_config config;
    config.password = "";
    config.path_to_database = "/home/evgeny/temp.db";
    config.flags = SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE;
    config.debug = false;
    DB = new sql::connection(config);
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
    delete DB;
}

void DataBase::Insert(std::string report) {
    auto i = insert_into(Reporters).columns(Reporters.report);
    i.values.add(Reporters.report = report);
    (*DB)(i);
}

bool DataBase::Select(int id, std::string &report) {
    for (const auto& row : (*DB)(select(Reporters.report).from(Reporters).where(Reporters.id == id))) {
        if (row.report.is_null()) {
            return false;
        }
        report = row.report;
        return true;
    }
}