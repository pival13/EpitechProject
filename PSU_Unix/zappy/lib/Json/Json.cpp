/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** Json
*/

#include "Json.hpp"

/*****************************/
/*        Ctor / Dtor        */
/*****************************/

Json::Json() : _json(new_json()), _delete(true) {}
Json::Json(json_t *json) : _json(json), _delete(false) {}
Json::~Json() { if (_delete && _json) free_json(_json); }

Json::Json(const Json &json) : Json() { *this = json; }
Json::Json(const std::string &str) : Json() { *this = str; }
Json::Json(const char *str) : Json() { *this = str; }
Json::Json(bool nb) : Json() { *this = nb; }
Json::Json(double nb) : Json() { *this = nb; }
Json::Json(int nb) : Json() { *this = nb; }
Json::Json(size_t nb) : Json() { *this = nb; }

Json::Json(const std::initializer_list<Json> &list) : Json()
{
    if (list.size() == 2 && list.begin()->isString() && !list.begin()->isNone()) {
        auto it = list.begin();
        json_add_key_value(_json, json_get_string(it->_json), json_copy_new_json((it+1)->_json));
    } else if (std::all_of(list.begin(), list.end(), [](const Json &j) { return j.isObject() && !j.data()->next && !j.data()->prev; })) {
        json_set_as_dict(_json, nullptr, nullptr);
        for (const Json &j : list)
            json_add_key_value(_json, j._json->key, json_copy_new_json(j._json->dict_value));
    } else {
        json_set_as_list(_json, nullptr);
        for (const Json &j : list)
            json_add_value_at_end(_json, json_copy_new_json(j._json));
    }
}

Json Json::fromFile(const std::string &filepath)
{
    Json json;

    free(json._json);
    json._json = read_json_from_file(filepath.c_str());
    if (!json._json)
        throw std::invalid_argument("Error with " + filepath);
    json._delete = true;
    return json;
}

Json Json::fromStringifyJson(const std::string &content)
{
    Json json;

    if (!json_is_valid(content.c_str()))
        throw std::invalid_argument("invalid json: " + content.substr(0, -1) + (content.length() > 15? "...": ""));
    
    char *cpy = new char[content.size()+1];
    content.copy(cpy, content.size()+1);
    cpy[content.size()] = '\0';
    const char *tmp = json_clean_str(cpy);
    parse_json(&tmp, json._json);
    delete[] cpy;

    json._delete = true;
    return json;
}

Json Json::asList(const std::initializer_list<Json> &list)
{
    Json json;

    json_set_as_list(json._json, nullptr);
    for (const Json &j : list)
        json_add_value_at_end(json._json, json_copy_new_json(j._json));
    return json;
}

Json Json::asObject(const std::initializer_list<Json> &list)
{
    Json json;

    json_set_as_dict(json._json, nullptr, nullptr);
    if (list.size() == 2 && list.begin()->isString() && !list.begin()->isNone()) {
        auto it = list.begin();
        json_add_key_value(json._json, json_get_string(it->_json), json_copy_new_json((it+1)->_json));
    } else if (std::all_of(list.begin(), list.end(), [](const Json &j) { return j.isObject(); })) {
        for (const Json &j : list)
            json_add_key_value(json._json, j._json->key, json_copy_new_json(j._json->dict_value));
    } else {
        throw std::invalid_argument("Json::asObject required a list or a single instance of two elements, with the first one being a string");
    }
    return json;
}

/*******************************/
/*         Const info          */
/*******************************/

bool Json::operator==(const Json &other) const
{
    if (_json->type != other._json->type)
        return false;
    if (_json->type == JSON_BOOL) return _json->bool_value == other._json->bool_value;
    else if (_json->type == JSON_NUMBER) return _json->int_value == other._json->int_value;
    else if (_json->type == JSON_STRING) return !strcmp(_json->string_value, other._json->string_value);
    else if (_json->type == JSON_LIST && size() == other.size()) {
        for (size_t i = size(); i != 0; i--)
            if ((*this)[i-1] != other[i-1]) return false;
        return true;
    } else if (_json->type == JSON_DICT && keys().size() && other.keys().size()) {
        for (const auto &k : keys())
            if (!other.contain(k) || (*this)[k] != other[k]) return false;
        return true;
    }
    return false;
}

bool Json::operator!=(const Json &other) const { return !this->operator==(other); }

bool Json::contain(size_t index) const { return json_get_list_size(_json) > index; }
bool Json::contain(const std::string &key) const { return json_has_key(_json, key.c_str()); }

bool Json::contain(const Json &json) const { return contain(std::function<bool(const Json &)>([&json](const Json &value) { return value == json; })); }

bool Json::contain(std::function<bool(const std::string &key)> predicate) const
{
    if (isNone() || !isObject()) return false;
    json_t *tmp = this->_json;
    while (tmp->prev) tmp = tmp->prev;
    for (; tmp; tmp = tmp->next)
        if (tmp->key != nullptr && predicate(tmp->key))
            return true;
    return false;
}

bool Json::contain(std::function<bool(const std::string &key, const Json &value)> predicate) const
{
    if (isNone() || !isObject()) return false;
    json_t *tmp = this->_json;
    while (tmp->prev) tmp = tmp->prev;
    for (; tmp; tmp = tmp->next)
        if (tmp->key != nullptr && predicate(tmp->key, tmp->list_value))
            return true;
    return false;
}

bool Json::contain(std::function<bool(const Json &value)> predicate) const
{
    if (isNone() || !isList()) return false;
    json_t *tmp = this->_json;
    while (tmp->prev) tmp = tmp->prev;
    for (; tmp; tmp = tmp->next)
        if (predicate(tmp->list_value))
            return true;
    return false;
}

bool Json::contain(std::function<bool(size_t index, const Json &value)> predicate) const
{
    if (isNone() || !isList()) return false;
    json_t *tmp = this->_json;
    while (tmp->prev) tmp = tmp->prev;
    for (size_t i = 0; tmp; tmp = tmp->next, ++i)
        if (predicate(i, tmp->list_value))
            return true;
    return false;
}
        
size_t Json::size() const { if (!isList()) throw std::invalid_argument(""); return json_get_list_size(_json); }

std::vector<std::string> Json::keys() const
{
    if (!isObject())
        throw std::invalid_argument("Cannot get keys of a non-object json");
    else if (isNone())
        return {};
    std::vector<std::string> list;
    Json tmp(this->_json);
    while (tmp._json->prev)
        tmp._json = tmp._json->prev;
    while (tmp._json) {
        list.emplace_back(tmp._json->key);
        tmp._json = tmp._json->next;
    }
    return list;
}

/*******************************/
/*           Getter            */
/*******************************/

template<> std::string Json::get<std::string>() const
{
    if (isNone())
        return std::string();
    else if (isString())
        return _json->string_value;
    else if (isBool())
        return _json->bool_value ? "True" : "False";
    else if (isNumber()) {
        std::stringstream s;
        s.precision(10);
        s << _json->int_value;
        return s.str();
    } else
        throw std::system_error();
}

template<> size_t Json::get<size_t>() const { if (!isNumber()) throw std::system_error(); return (isNone() ? 0 : size_t(_json->int_value)); }
template<> int Json::get<int>() const { if (!isNumber()) throw std::system_error(); return (isNone() ? 0 : int(_json->int_value)); }
template<> float Json::get<float>() const { if (!isNumber()) throw std::system_error(); return (isNone() ? 0 : float(_json->int_value)); }
template<> double Json::get<double>() const { if (!isNumber()) throw std::system_error(); return (isNone() ? 0 : double(_json->int_value)); }
template<> long double Json::get<long double>() const { if (!isNumber()) throw std::system_error(); return (isNone() ? 0 : _json->int_value); }

template<> bool Json::get<bool>() const
{
    if (json_get_type(_json) == JSON_NONE)
        return 0;
    else if (isBool())
        return _json->bool_value;
    else if (isNumber())
        return _json->int_value != 0;
    else if (isString())
        return !std::string(_json->string_value).empty() &&
               strcmp(_json->string_value, "0") &&
               strcasecmp(_json->string_value, "false") &&
               strcasecmp(_json->string_value, "null") &&
               strcasecmp(_json->string_value, "none");
    else
        throw std::system_error();
}

Json Json::operator[](size_t index)
{
    if (!isList())
        throw std::invalid_argument("");
    while (index >= size())
        json_add_value_at_end(_json, new_json());
    return json_get_at_index(_json, index);
}

Json Json::operator[](size_t index) const
{
    if (!contain(index))
        throw std::invalid_argument("");
    return json_get_at_index(_json, index);
}

Json Json::operator[](const std::string &key)
{
    if (!isObject())
        throw std::invalid_argument("");
    if (!contain(key))
        json_add_key(_json, key.c_str());
    return json_get_with_key(_json, key.c_str());
}

Json Json::operator[](const std::string &key) const
{
    if (!contain(key))
        throw std::invalid_argument("");
    return json_get_with_key(_json, key.c_str());
}

Json Json::find(std::function<bool(const std::string &key)> predicate)
{
    if (isNone() || !isObject()) return Json();
    json_t *tmp = this->_json;
    while (tmp->prev) tmp = tmp->prev;
    for (; tmp; tmp = tmp->next)
        if (tmp->key != nullptr && predicate(tmp->key))
            return tmp->dict_value;
    return Json();
}

Json Json::find(std::function<bool(const std::string &key, Json value)> predicate)
{
    if (isNone() || !isObject()) return Json();
    json_t *tmp = this->_json;
    while (tmp->prev) tmp = tmp->prev;
    for (; tmp; tmp = tmp->next)
        if (tmp->key != nullptr && predicate(tmp->key, tmp->dict_value))
            return tmp->dict_value;
    return Json();
}

Json Json::find(std::function<bool(Json value)> predicate)
{
    if (isNone() || !isList()) return Json();
    json_t *tmp = this->_json;
    while (tmp->prev) tmp = tmp->prev;
    for (; tmp; tmp = tmp->next)
        if (predicate(tmp->list_value))
            return tmp->list_value;
    return Json();
}

Json Json::find(std::function<bool(size_t index, Json value)> predicate)
{
    if (isNone() || !isList()) return Json();
    json_t *tmp = this->_json;
    while (tmp->prev) tmp = tmp->prev;
    for (size_t i = 0; tmp; tmp = tmp->next, i++)
        if (predicate(i, tmp->list_value))
            return tmp->list_value;
    return Json();
}

std::string Json::toString(size_t indentLevel) { std::stringstream ss; dump(ss, indentLevel); return ss.str(); }

/***************************************/
/*               Setter                */
/***************************************/

Json &Json::operator=(const Json &json)
{
    _json = json_copy(_json, json._json);
    return *this;
}

Json &Json::operator=(Json &&json)
{
    _json = json_move(_json, json._json);
    memset(json._json, 0, sizeof(json_t));
    json._json->type = JSON_NONE;
    return *this;
}

Json &Json::operator=(int nb)
{
    json_set_as_number(_json, nb);
    return *this;
}

Json &Json::operator=(size_t nb)
{
    json_set_as_number(_json, nb);
    return *this;
}

Json &Json::operator=(double nb)
{
    json_set_as_number(_json, nb);
    return *this;
}

Json &Json::operator=(bool nb)
{
    json_set_as_bool(_json, nb);
    return *this;
}

Json &Json::operator=(const char *str) { return *this = std::string(str); }
Json &Json::operator=(const std::string &str)
{
    json_set_as_string(_json, str.c_str());
    return *this;
}

void Json::insert(size_t position, Json &&value)
{
    if (!isList())
        throw std::invalid_argument("Cannot insert element to a non-list json.");
    else if (!json_add_value_at_index(_json, position, new_json()))
        throw std::invalid_argument("Failed to insert element at index " + std::to_string(position));
    operator[](position) = value;
}

void Json::insert(size_t position, const Json &value) { insert(position, Json(value)); }
void Json::insert(size_t position, int value) { insert(position, Json(value)); }
void Json::insert(size_t position, size_t value) { insert(position, Json(value)); }
void Json::insert(size_t position, double value) { insert(position, Json(value)); }
void Json::insert(size_t position, bool value) { insert(position, Json(value)); }
void Json::insert(size_t position, const std::string &value) { insert(position, Json(value)); }
void Json::insert(size_t position, const char *value) { insert(position, Json(value)); }

void Json::append(const Json &value) { operator[](size()) = value; }
void Json::append(Json &&value) { operator[](size()) = value; }
void Json::append(int value) { operator[](size()) = value; }
void Json::append(size_t value) { operator[](size()) = value; }
void Json::append(double value) { operator[](size()) = value; }
void Json::append(bool value) { operator[](size()) = value; }
void Json::append(const std::string &value) { operator[](size()) = value; }
void Json::append(const char *value) { operator[](size()) = value; }

void Json::update(const std::string &key, const Json &value) { operator[](key) = value; }
void Json::update(const std::string &key, Json &&value) { operator[](key) = value; }
void Json::update(const std::string &key, int value) { operator[](key) = value; }
void Json::update(const std::string &key, size_t value) { operator[](key) = value; }
void Json::update(const std::string &key, double value) { operator[](key) = value; }
void Json::update(const std::string &key, bool value) { operator[](key) = value; }
void Json::update(const std::string &key, const std::string &value) { operator[](key) = value; }
void Json::update(const std::string &key, const char *value) { operator[](key) = value; }

/************************/
/*        Trivia        */
/************************/

void Json::dump(size_t indentLevel) const { dump(std::cout, indentLevel); }
void Json::dump(std::ostream &os, size_t indentLevel) const
{
    static size_t initIndent = 0;

    if (!_json || _json->type == JSON_NONE)
        os << "null";
    else if (_json->type == JSON_BOOL)
        os << (_json->bool_value ? "true": "false");
    else if (_json->type == JSON_NUMBER) {
        auto save = os.precision();
        os.precision(10);
        os << _json->int_value;
        os.precision(save);
    } else if (_json->type == JSON_STRING)
        os << "\"" << _json->string_value << "\"";
    else if (_json->type == JSON_LIST) {
        json_t *tmp = _json;
        while (tmp->prev) tmp = tmp->prev;
        if (!tmp->list_value) {
            os << "[]";
        } else {
            os << "[" << (indentLevel != 0? "\n": "");
            initIndent += indentLevel;
            while (tmp != NULL) {
                os << std::string(initIndent, ' ');
                Json(tmp->list_value).dump(os, indentLevel);
                if (tmp->next) os << "," << (indentLevel != 0? "\n": "");
                tmp = tmp->next;
            }
            initIndent -= indentLevel;
            os << (indentLevel != 0? "\n": "") << std::string(initIndent, ' ') << "]";
        }
    } else if (_json->type == JSON_DICT) {
        json_t *tmp = _json;
        while (tmp->prev) tmp = tmp->prev;
        if (!tmp->dict_value) {
            os << "{}";
        } else {
            os << "{" << (indentLevel != 0? "\n": "");
            initIndent += indentLevel;
            while (tmp != NULL) {
                os << std::string(initIndent, ' ') << "\"" << tmp->key << "\": ";
                Json(tmp->dict_value).dump(os, indentLevel);
                if (tmp->next) os << "," << (indentLevel != 0? "\n": "");
                tmp = tmp->next;
            }
            initIndent -= indentLevel;
            os << (indentLevel != 0? "\n": "") << std::string(initIndent, ' ') << "}";
        }
    }
}

std::ostream &operator<<(std::ostream &os, const Json &js)
{
    js.dump(os);
    return os;
}
