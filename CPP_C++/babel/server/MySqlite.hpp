/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** MySqlite
*/

#ifndef MYSQLITE_HPP_
#define MYSQLITE_HPP_

#include <iostream>
#include <sqlite3.h>
#include <map>
#include <string>
#include <deque>

typedef std::map<std::string, std::deque<std::string>> sqltable;

class MySqlite {
    public:
        MySqlite(const std::string path);
        MySqlite();
        bool excuteInsert(const std::string& request);
        std::map<std::string, std::deque<std::string>> excuteSelect(const std::string &request);
        ~MySqlite();

    private:
        sqlite3 *db;
        const std::string m_path;
};

#endif /* !MYSQLITE_HPP_ */
