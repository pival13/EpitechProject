/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** MySqlite
*/

#include "MySqlite.hpp"

MySqlite::MySqlite(const std::string path)
    : m_path(path)
{
    int rc = sqlite3_open(this->m_path.data(), &this->db);
    if (rc != SQLITE_OK)
        throw std::runtime_error(sqlite3_errmsg(db));
}

MySqlite::MySqlite()
{
}

MySqlite::~MySqlite()
{
    sqlite3_close(this->db);
}

bool MySqlite::excuteInsert(const std::string& request)
{
    if (this->m_path.empty() || request.empty())
        return false;
    if (sqlite3_exec(this->db, request.data(), NULL, NULL, NULL) == SQLITE_OK) {
        std::cout << "Sucess request" << std::endl;
        return true;
    } else {
        std::cerr << "Failed request : " << request << std::endl;
        return false;
    }
}

static int callback(void *data, int nbCol, char **colTabla, char **colName)
{
    std::map<std::string, std::deque<std::string>> *tbl =
            static_cast<std::map<std::string, std::deque<std::string>> *>(data);

    for (size_t i = 0; i != size_t(nbCol); ++i)
        tbl->operator[](colName[i]).push_back(colTabla[i]);
    return 0;
}

std::map<std::string, std::deque<std::string>> MySqlite::excuteSelect(const std::string &request)
{
    std::map<std::string, std::deque<std::string>> data;

    if (request.empty())
        throw std::invalid_argument("Empty request");
    int rc = sqlite3_exec(db, request.data(), &callback, &data, nullptr);
    if (rc != SQLITE_OK)
        throw std::runtime_error(sqlite3_errmsg(db));

    return data;
}
