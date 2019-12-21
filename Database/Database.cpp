#include "Database.h"

Database::Database() {
    sql::connection_config config;
    config.password = "";
    config.path_to_database = "ex.db";
    config.flags = SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE;
    config.debug = false;
    db = new sql::connection(config);
    try {
        db->execute("CREATE TABLE reporters (\
            id INTEGER PRIMARY KEY AUTOINCREMENT,\
            key INTEGER UNIQUE DEFAULT NULL,\
            report varchar(255) DEFAULT NULL\
        )");
    }
    catch (sqlpp::exception e) {
        std::cerr << e.what() << std::endl;
    }
}

Database::~Database() {
    delete db;
}

bool Database::insert(int key, std::string& report) {
    try {
        auto i = insert_into(reporters).columns(reporters.key, reporters.report);
        i.values.add(reporters.key = key, reporters.report = report);
        (*db)(i);
    }
    catch (sqlpp::exception e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

bool Database::select(int key, std::string& report) {
    try {
        for (const auto &row : (*db)(sqlpp::select(reporters.report).from(reporters).where(reporters.key == key))) {
            if (row.report.is_null()) {
                return false;
            }
            report = row.report;
            return true;
        }
    }
    catch (sqlpp::exception e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
}