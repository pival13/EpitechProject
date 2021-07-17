/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** Json
*/

#pragma once

#include "json.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <functional>
#include <initializer_list>
#include <algorithm>

class Json {
    public:
        ///@brief Construct a new null-like Json.
        Json();
        ///@brief Construct a new bool-like Json.
        Json(bool b);
        ///@brief Construct a new number-like Json.
        Json(int nb);
        ///@brief Construct a new number-like Json.
        Json(size_t nb);
        ///@brief Construct a new number-like Json.
        Json(double nb);
        ///@brief Construct a new string-like Json.
        Json(const std::string &str);
        ///@brief Construct a new string-like Json.
        Json(const char *str);

        ///@brief Construct a new list-like or object-like Json.
        ///@details Construct an object-like Json when:
        /// - Each values of the initializer-list are object-like Json.
        /// - The initializer-list has two elements, the first one being a string-like Json.
        ///
        ///In all other cases, construct a list-like Json.
        ///
        ///Exemple: The following code
        ///```{
        ///Json json = {
        ///    {"Key1", 0},
        ///    {"Key2", {
        ///        1,
        ///        2,
        ///        false
        ///    }},
        ///};
        ///}```
        /// will create a json similar to:
        ///```{
        ///{
        ///  "Key1": 0,
        ///  "Key2": [
        ///    1,
        ///    2,
        ///    false
        ///  ]
        ///} }```
        ///
        ///You can use `Json::asList` and `Json::asObject` to explicitly create a list-like Json and an object-like Json respectively.
        ///@param list A list of Json. Implicit constructor can be called.
        Json(const std::initializer_list<Json> &list);

        ///@brief Create a new Json with a C `json_t`.
        ///@details The new Json will not release its content when it will be release.
        Json(json_t *json);
        ///@brief Copy constructor.
        Json(const Json &other);
        ~Json();

        ///@brief Return a new Json with a json file.
        ///@details Read a file and try to convert its content to a Json.
        ///
        ///If \@filepath is not a valid path, or the file does not contain a valid json, throw a `std::invalid_argument`.
        ///@param filepath Path to a file describing a json.
        static Json fromFile(const std::string &filepath);
        ///@brief Return a new Json with a string describing a json.
        ///@details If the string does not contain a valid json, throw a `std::invalid_argument`.
        static Json fromStringifyJson(const std::string &content);
        ///@brief Return a new list-like Json.
        static Json asList(const std::initializer_list<Json> &list);
        ///@brief Return a new object-like Json.
        ///@details Similar to the `Json::Json(const std::initializer_list<Json> &)`, but will throw a `std::invalid_argument` if it fail to convert to an object.
        static Json asObject(const std::initializer_list<Json> &list);

        ///@brief Convert a `Json` to a valid json, understandable by any standart Json lib.
        std::string toString(size_t indentLevel=JSON_INDENT);

        ///@brief Return true if Json is a null-like Json.
        inline bool isNone() const { return json_get_type(_json) == JSON_NONE; }
        ///@brief Return true if Json is a bool-like Json.
        inline bool isBool() const { return isNone() || json_get_type(_json) == JSON_BOOL; }
        ///@brief Return true if Json is a number-like Json.
        inline bool isNumber() const { return isNone() || json_get_type(_json) == JSON_NUMBER; }
        ///@brief Return true if Json is a string-like Json.
        inline bool isString() const { return isNone() || json_get_type(_json) == JSON_STRING; }
        ///@brief Return true if Json is a list-like Json.
        inline bool isList() const { return isNone() || json_get_type(_json) == JSON_LIST; }
        ///@brief Return true if Json is an object-like Json.
        inline bool isObject() const { return isNone() || json_get_type(_json) == JSON_DICT; }

        bool operator==(const Json &other) const;
        bool operator!=(const Json &other) const;

        ///@brief Return true if the index if lower to a list-like json's size.
        bool contain(size_t index) const;
        ///@brief Return true if an object-like json contain the key.
        bool contain(const std::string &key) const;
        ///@brief Return true if a list-like json contain the value.
        bool contain(const Json &json) const;
        ///@brief Return true if the predicate is true for any member of an object-like json.
        bool contain(std::function<bool(const std::string &key)> predicate) const;
        ///@brief Return true if the predicate is true for any member of an object-like json.
        bool contain(std::function<bool(const std::string &key, const Json &value)> predicate) const;
        ///@brief Return true if the predicate is true for any member of a list-like json.
        bool contain(std::function<bool(const Json &value)> predicate) const;
        ///@brief Return true if the predicate is true for any member of a list-like json.
        bool contain(std::function<bool(size_t index, const Json &value)> predicate) const;
        ///@brief Return the size of a list-like json.
        size_t size() const;
        ///@brief Return a vector with all the keys of an object-like json.
        std::vector<std::string> keys() const;

        ///@brief Return the first value of an object-like Json for which the predicate is true, or a null-like json.
        Json find(std::function<bool(const std::string &key)>);
        ///@brief Return the first value of an object-like Json for which the predicate is true, or a null-like json.
        Json find(std::function<bool(Json value)>);
        ///@brief Return the first value of a list-like Json for which the predicate is true, or a null-like json.
        Json find(std::function<bool(const std::string &key, Json value)>);
        ///@brief Return the first value of a list-like Json for which the predicate is true, or a null-like json.
        Json find(std::function<bool(size_t index, Json value)>);

        ///@brief Return the element at a given index of a list-like json.
        ///@details If index is greater than the list's size, add as many new elements as needed and return it.
        ///
        ///If use on a non list-like json, throw a std::invalid_argument.
        Json operator[](size_t index);
        ///@brief Return the element at a given index of a list-like json.
        ///@details If use on a non list-like json or if index is greater to its size, throw a std::invalid_argument.
        Json operator[](size_t index) const;
        ///@brief Return the element at a given key of an object-like json.
        ///@details If the object does not contain the key, add it and return the new value at the key.
        ///
        ///If use on a non object-like json, throw a std::invalid_argument.
        Json operator[](const std::string &key);
        ///@brief Return the element at a given index of a list-like json.
        ///@details If use on a non object-like json or if it does not contain the key, throw a std::invalid_argument.
        Json operator[](const std::string &key) const;

        ///@brief Insert a new element at a given position on a list-like json.
        ///@details If use on a non list-like json, or with an out-of-range index, throw a std::invalid_argument.
        void insert(size_t position, const Json &json);
        void insert(size_t position, Json &&json);
        void insert(size_t position, int nb);
        void insert(size_t position, size_t nb);
        void insert(size_t position, double nb);
        void insert(size_t position, bool nb);
        void insert(size_t position, const std::string &json);
        void insert(size_t position, const char *json);

        ///@brief Inset a new element at the end of a list-like json.
        ///@details If use on a non list-like json, convert it to one.
        void append(const Json &json);
        void append(Json &&json);
        void append(int nb);
        void append(size_t nb);
        void append(double nb);
        void append(bool nb);
        void append(const std::string &json);
        void append(const char *json);

        ///@brief Insert a new pair key-value on an object-like json, or update an existing key with the given value. Same as operator[].
        void update(const std::string &key, const Json &value);
        void update(const std::string &key, Json &&value);
        void update(const std::string &key, int value);
        void update(const std::string &key, size_t value);
        void update(const std::string &key, double value);
        void update(const std::string &key, bool value);
        void update(const std::string &key, const std::string &value);
        void update(const std::string &key, const char *value);
        /* Add each pair of key-value of @value or replace them if they already exist.
           If the same key is present several time, the last one will be eventually assign.
           If @value or this is not an object like json, throw an invalid_argument exception. */
        //void update(const Json &value);
        /* Add each pair of key-value of @value or replace them if they already exist.
           If the same key is present several time, the last one will be eventually assign.
           If @value or this is not an object like json, throw an invalid_argument exception. */
        //void update(Json &&value);

        Json &operator=(const Json &json);
        Json &operator=(Json &&json);

        Json &operator=(int nb);
        Json &operator=(size_t nb);
        Json &operator=(double nb);
        Json &operator=(bool nb);
        Json &operator=(const std::string &nb);
        Json &operator=(const char *nb);

        //Json &operator-
        //Json &operator-=
        //Json &operator+
        //Json &operator+=

        /* Add each element of @value at the end of the list.
           If @value or this is not an list like json, throw an invalid_argument exception. */
        //void merge(const Json &json);
        /* Add each element of @value at the end of the list.
           If @value or this is not an list like json, throw an invalid_argument exception. */
        //void merge(Json &&json);

        ///@brief Get the content of a json.
        ///@details If the json does not hold a value of the wandered kind, try to perform a conversion, or throw a std::system_error.
        template<typename T> T get() const;
        ///@brief Return the contain `json_t` struct.
        inline const json_t *data() const { return _json; }

        ///@brief Dump the json to the standart output.
        ///@details If \@indentLevel is 0, dump it without any trailing space.
        void dump(size_t indentLevel=JSON_INDENT) const;
        ///@brief Dump the json to an ostream.
        ///@details If \@indentLevel is 0, dump it without any trailing space.
        void dump(std::ostream &os, size_t indentLevel=JSON_INDENT) const;

    private:
        json_t *_json;
        bool _delete;
};

std::ostream &operator<<(std::ostream &os, const Json &json);