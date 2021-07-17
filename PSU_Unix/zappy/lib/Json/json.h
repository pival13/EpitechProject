/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** json
*/

#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <regex.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/// @file

#ifndef JSON_INDENT
#define JSON_INDENT 2   ///< Size of indentation use for display_json
#endif

enum json_type {
    JSON_NONE,   ///< None
    JSON_BOOL,   ///< Boolean
    JSON_NUMBER, ///< Number (`signed floating-point`)
    JSON_STRING, ///< String (`char*`)
    JSON_LIST,   ///< List of `json_t`
    JSON_DICT    ///< List of pair `String`-`json_t`
};

typedef struct json_s {
    enum json_type type;

    char *key;
    union {
        bool bool_value;
        long double int_value;
        char *string_value;
        struct json_s *list_value;
        struct json_s *dict_value;
    };

    struct json_s *prev;
    struct json_s *next;
} json_t;


/****************************************/
/*    Creation / Destruction function   */
/****************************************/

//Return a new null-like json.
json_t *new_json();
//Return a new bool-like json set at @b.
json_t *new_json_as_bool(bool b);
//Return a new number-like json set at @nb.
json_t *new_json_as_number(long double nb);
//Return a new string-like json set with a copy of @s.
json_t *new_json_as_string(const char *s);
//Return a new string-like json set with the string pointed by @s.
json_t *new_json_as_string_with_free(char *s);
//Return a new empty list-like json.
json_t *new_json_as_empty_list();
//Return a new list-like json set at @values. @values must be an NULL-terminated array.
json_t *new_json_as_list(json_t *values[]);
//Return a new empty object-like json.
json_t *new_json_as_empty_dict();
//Return a new object-like json with each values associated with the respective key. @keys and @values must be NULL-terminated arrays.
json_t *new_json_as_dict(const char *keys[], json_t *values[]);
//Return a new json equivalent to one describe in @file, or NULL if @file is not a valid json.
json_t *read_json_from_file(const char *file);

//Return a new json as a perfect copy of @other.
json_t *json_copy_new_json(const json_t *other);
//Copy each elements of @src into @dest.
json_t *json_copy(json_t *dest, const json_t *src);
//Copy @src into @dest using memmove.
json_t *json_move(json_t *dest, const json_t *src);

//Release a json and all its associated values.
void free_json(json_t *json);


/****************************************/
/*    Internal construction function    */
/****************************************/

//Remove any useless whitespace and coma on a string.
char *json_clean_str(char *s);
//Check if a string described a valid json.
bool json_is_valid(const char *s);
//Return a copy of a string rounded by quotes.
char *json_read_string(const char *s);

void parse_json(const char **s, json_t *json);
void parse_dict(const char **s, json_t *json);
void parse_list(const char **s, json_t *json);
void parse_string(const char **s, json_t *json);
void parse_number(const char **s, json_t *json);
void parse_bool(const char **s, json_t *json);
void parse_none(const char **s, json_t *json);


/****************************************/
/*             Get functions            */
/****************************************/

//Return the type of the json.
enum json_type json_get_type(const json_t *json);

//Check if an object-like json have a specific key.
bool json_has_key(const json_t *json, const char *key);
//Return the size of list-like json, or 0.
size_t json_get_list_size(const json_t *json);
//Return an NULL-terminated array with all keys of an object-like json.
char **json_get_all_keys(const json_t *json);

//Return the bool contain by a bool-like json, or False.
bool json_get_bool(const json_t *json);
//Return the number contain by a number-like json, or 0.
long double json_get_number(const json_t *json);
//Return the string contain by a string-like json, or NULL.
const char *json_get_string(const json_t *json);
//Return the value at a given index on a list-like json, or NULL.
json_t *json_get_at_index(const json_t *json, size_t index);
//Return the value at a given key on an object-like json, or NULL.
json_t *json_get_with_key(const json_t *json, const char *key);


/****************************************/
/*             Set functions            */
/****************************************/

//Set a json to a null-like json.
void json_set_as_none(json_t *json);
//Set a json to a bool-like json equal to @b.
void json_set_as_bool(json_t *json, bool b);
//Set a json to a number-like json equal to @nb.
void json_set_as_number(json_t *json, long double nb);
//Set a json to a string-like json with a copy of @str.
void json_set_as_string(json_t *json, const char *str);
//Set a json to a string-like json with the string pointed by @str.
void json_set_as_string_with_free(json_t *json, char *str);
//Set a json to a list-like json, with all values of @values. @values must ba a NULL-terminated array.
void json_set_as_list(json_t *json, json_t *values[]);
//Set a json to an object-like json, with each value of @values associated with the respective key of @keys. @keys and @values must be NULL-terminated arrays
void json_set_as_dict(json_t *json, const char *keys[], json_t *values[]);


/****************************************/
/*           Object functions           */
/****************************************/

//Return true if a key has successfully been added to an object-like json.
bool json_add_key(json_t *json, const char *key);
//Return true if a key and its value has successfully been added to an object-like json.
bool json_add_key_value(json_t *json, const char *key, json_t *value);

//Return true if a value at a given key has successfully been set on an object-like json.
bool json_set_value_at_key(json_t *json, const char *key, json_t *value);

//Return true if a key, and its associated value, has successfully been removed of an object-like json.
bool json_remove_key(json_t *json, const char *key);
//Return true if an object-like json has successfully been cleared.
bool json_clean_dict(json_t *json);


/****************************************/
/*            List functions            */
/****************************************/

//Return true if a value has successfully been inserted at a given index of a list-like json.
bool json_add_value_at_index(json_t *json, size_t index, json_t *value);
//Return true if a value has successfully been inserted at the end of a list-like json.
bool json_add_value_at_end(json_t *json, json_t *value);

//Return true if a value has successfully been set at a given index of a list-like json.
bool json_set_value_at_index(json_t *json, size_t index, json_t *value);

//Return true if a value has successfully been removed at a given index of a list-like json.
bool json_remove_value_at_index(json_t *json, size_t index);
//Return true if a value has successfully been removed at the end of a list-like json.
bool json_remove_value_at_end(json_t *json);
//Return true if a list-like json has successfully been cleared.
bool json_clean_list(json_t *json);


/****************************************/
/*            Other functions           */
/****************************************/

//Print the given json to the standart output, with an indentation of JSON_INDENT.
void display_json(const json_t *json);

#ifdef __cplusplus
}
#endif

/****************************************/
/*            Documentation             */
/****************************************/

/// @fn json_t *new_json()
/// @brief Create a default json_t.
/// @return A new pointer to a json_t.
/// @fn json_t *new_json_as_bool(bool b)
/// @brief Create a json_t as a bool.
/// @param b The bool use to set the json.
/// @return A new pointer to a json_t.
/// @fn json_t *new_json_as_number(long double nb)
/// @brief Create a json_t as a number.
/// @param nb The number use to set the json.
/// @return A new pointer to a json_t.
/// @fn json_t *new_json_as_string(const char *s)
/// @brief Create a json_t as a string.
/// @details The stored string is a copy of \@s.\n
/// For a non-copy version, use new_json_as_string_with_free
/// @param s The string use to set the json.
/// @return A new pointer to a json_t.
/// @fn json_t *new_json_as_string_with_free(char *s)
/// @brief Create a json_t as a string.
/// @details The stored string is the one passed as parameter. This mean the string will be automatically release when free_json will be called.\n
/// For a copy version, use new_json_as_string
/// @param s The string use to set the json.
/// @return A new pointer to a json_t.
/// @fn json_t *new_json_as_empty_list()
/// @brief Create a json_t as an empty list.
/// @return A new pointer to a json_t.
/// @fn json_t *new_json_as_list(json_t *values[])
/// @brief Create a json_t as a list.
/// @details The list is filled with the values in \@values, keeping the initial order.\n
/// The returned json_t will own those values, meaning it will manage to destroy them when it will be destroyed.
/// @param values A NULL-terminated array of pointer of json_t.
/// @return A new pointer to a json_t.
/// @fn json_t *new_json_as_empty_dict()
/// @brief Create a json_t as an empty object.
/// @return A new pointer to a json_t.
/// @fn json_t *new_json_as_dict(const char *keys[], json_t *values[])
/// @brief Create a json_t as an object.
/// @details The json will be filled with each values of \@values at the respective key of \@keys.\n\n
/// If \@keys and \@values do not have the same size, the lowest one will be used.\n\n
/// If a key appear more than once, only the value associated with the first one will be stored, the other ones being ignored.\n
/// The returned json_t will own those values, meaning it will manage to destroy them when it will be destroyed. However values from duplicated keys will not be destroyed as they are not owned. In the same way, if there is more values than keys, lasts one will not be destroyed.
/// @param keys A NULL-terminated array of string.
/// @param values A NULL-terminated array of pointer of json_t.
/// @return A new pointer to a json_t.

/// @fn json_t *read_json_from_file(const char *file)
/// @brief Return a json_t similar to the one describe in \@file.
/// @details If \@file is not a file or does not contain a valid json file, NULL will be return.
/// @param file A file path to a json file.
/// @return A new pointer to a json_t or NULL.

/// @fn json_t *json_copy_new_json(const json_t *other)
/// @brief Return a new json_t as the exact copy of \@other.
/// @details If other is NULL, NULL is return as well.
/// @param other A json_t to copy.
/// @return A new pointer to a json_t or NULL.
/// @fn json_t *json_copy(json_t *dest, const json_t *src)
/// @brief Copy the content of \@src into \@dest.
/// @details If \@dest is not a default json_t, its content will be destroyed before.
/// @param dest The json_t which will contain a copy of \@src.
/// @param src The json_t which will be copied.
/// @return \@dest
/// @fn json_t *json_move(json_t *dest, const json_t *src)
/// @brief Copy the content of \@src into \@dest with memmove.
/// @details If @dest is not a default json, its content will be freed before.\n
/// For more information, refer to memmove.
/// @param dest The json_t which will contain \@src.
/// @param src The json_t which will be moved.
/// @return \@dest

/// @fn void free_json(json_t *json)
/// @brief Delete the content of \@json and release its pointer.
/// @details If \@json own other json_t, they will be destroyed as well.
/// @param json A json_t to destroy.

/// @fn char *json_clean_str(char *s)
/// @brief Remove any whitespace and comma before a close bracket `}` or square bracket `]` which are not between quotes.
/// @param s The string to clear
/// @return \@s
/// @fn bool json_is_valid(const char *s)
/// @brief Check whether a string contain a valid json or not.
/// @details A string is a valid json if it consist of:
///    - An object: Square brackets `[]` containaing (or not) valids json, separated by coma `,`.
///    - A list: Curly brackets `{}` containaing (or not) valids pair, separated by coma `c`.
///     - A valid pair consist of a string rounded by quotes `"`, followed by a colon `:`, followed by a valid json.
///    - A string: Quotes surrounding any character except non-escape quotes.
///    - A number: one or more digit `0123456789` followed (or not) by a dot `.` and more digits.
///    - A boolean: Either `true` or `false`. Case insensitive.
///    - None: One of `none`, `null` or `nil`. Case insensitive.
/// @param s A string containing the description of a json.
/// @return True if \@s is a valid json. False otherwise.
/// @fn char *json_read_string(const char *s)
/// @brief Return a copy of a string contain between quote `"`, or NULL if there is less than two quotes.
/// @param s A string with at least two quotes.
/// @return A copy of a string contain between quotes or NULL.

/// @fn void parse_json(const char **s, json_t *json)
/// @brief Try to fill \@json with the described json set in \@s.
/// @details \@s will be parsed following the below rules, filling \@json in the meanwhile. It is considered \@s is a valid json.
///    - An object: Square brackets `[]` containaing (or not) valids jsons, separated by coma `,`.
///    - A list: Curly brackets `{}` containaing (or not) valids pairs, separated by coma `c`.
///      - A valid pair consist of a string rounded by quotes `"`, followed by a colon `:`, followed by a valid json.
///    - A string: Quotes surrounding any character except non-escape quotes.
///    - A number: one or more digit `0123456789` followed (or not) by a dot `.` and more digits.
///    - A boolean: Either `true` or `false`. Case insensitive.
///    - None: One of `none`, `null` or `nil`. Case insensitive.
/// @param s A pointer to a string which must have been cleared with json_clean_str.
/// @param json A default json_t which will be filled.

/// @fn enum json_type json_get_type(const json_t *json)
/// @brief Get the type of the content of json.
/// @param json
/// @return The type of json
/// @fn bool json_has_key(const json_t *json, const char *key)
/// @brief Check whether a key is present in an object-like json.
/// @param json An object-like json.
/// @param key A key to search.
/// @return True if \@json is an object-like json which contain the key \@key. False otherwise.
/// @fn size_t json_get_list_size(const json_t *json)
/// @brief Get the size of a list-like json.
/// @param json A list-like json.
/// @return the size of \@json if it is a list-like json. 0 otherwhise.
/// @fn char **json_get_all_keys(const json_t *json)
/// @brief Get a list of all keys contain in an object-like json.
/// @param json An object-like json.
/// @return A NULL-terminated array of string if \@json is an object-like json. NULL otherwise.

/// @fn bool json_get_bool(const json_t *json)
/// @brief Get the value of a bool-like json.
/// @param json A bool-like json.
/// @return The boolean stocked if \@json is a bool-like json. False otherwise.
/// @fn long double json_get_number(const json_t *json)
/// @brief Get the value of a number-like json.
/// @param json A number-like json.
/// @return The number stocked if \@json is a number-like json. 0 otherwise.
/// @fn const char *json_get_string(const json_t *json)
/// @brief Get the value of a string-like json.
/// @param json A string-like json.
/// @return The string stocked if \@json is a string-like json. NULL otherwise.
/// @fn json_t *json_get_at_index(const json_t *json, size_t index)
/// @brief Get the value stocked at a given index of a list-like json.
/// @param json A list-like json.
/// @param index A number lower to the list size.
/// @return The value at index \@index if \@json is a list-like json and \@index is lower to the size. NULL otherwise.
/// @fn json_t *json_get_with_key(const json_t *json, const char *key)
/// @brief Get the value stocked at a given key in an object-like json.
/// @param json An object-like json.
/// @param key A key which must be include in \@json.
/// @return The value at key \@key if \@json is an object-like json containing the key. NULL otherwise.

/// @fn void json_set_as_none(json_t *json)
/// @brief Set a json to its default state, a null-like json.
/// @details Setting a json to another state implied the destruction of its content.
/// @param json A json to reinitialize.
/// @fn void json_set_as_bool(json_t *json, bool b)
/// @brief Set a json to a bool-like json with a specific value.
/// @details Setting a json to another state implied the destruction of its content.
/// @param json A json to change.
/// @param b Value to set.
/// @fn void json_set_as_number(json_t *json, long double nb)
/// @brief Set a json to a number-like json with a specific value.
/// @details Setting a json to another state implied the destruction of its content.
/// @param json A json to change.
/// @param nb Value to set.
/// @fn void json_set_as_string(json_t *json, const char *str)
/// @brief Set a json to a string-like json with a specific value.
/// @details The stored string is a copy of \@str. For a non-copy version, use json_set_as_string_with_free.\n
/// Setting a json to another state implied the destruction of its content.
/// @param json A json to change.
/// @param str Value to set.
/// @fn void json_set_as_string_with_free(json_t *json, char *str)
/// @brief Set a json to a string-like json with a specific value.
/// @details The stored string is the one passed as parameter. This mean the string will be automatically release when free_json will be called.\n
/// For a copy version, use new_json_as_string\n
/// Setting a json to another state implied the destruction of its content.
/// @param json A json to change.
/// @param str Value to set.
/// @fn void json_set_as_list(json_t *json, json_t *values[])
/// @brief Set a json to a list-like json with initial values.
/// @details The list is filled with the values in \@values, keeping the initial order.\n
/// The json will own those values, meaning it will manage to destroy them when it will be destroyed. If this is not intended, use a copy of these values with json_copy or json_copy_new_json.\n
/// To set a json to an empty list, passed NULL or an array containing only NULL as parameter.\n
/// Setting a json to another state implied the destruction of its content.
/// @param json A json to change.
/// @param values A NULL-terminated array of json_t.
/// @fn void json_set_as_dict(json_t *json, const char *keys[], json_t *values[])
/// @brief Set a json to an object-like json with initial values.
/// @details The object is filled with each values of \@values at the respective key of \@keys.\n\n
/// If \@keys and \@values do not have the same size, the lowest one will be used.\n\n
/// If a key appear more than once, only the value associated with the first one will be stored, the others being ignored.\n
/// The json will own those values, meaning it will manage to destroy them when it will be destroyed. However values from duplicated keys will not be destroyed as they are not owned. In the same way, if there is more values than keys, lasts one will not be destroyed. If this is not intended, use a copy of these values with json_copy or json_copy_new_json.\n
/// To set a json to an empty list, passed NULL or an array containing only NULL as parameter.\n
/// Setting a json to another state implied the destruction of its content.
/// @param json A json to change.
/// @param keys A NULL-terminated array of string.
/// @param values A NULL-terminated array of pointer of json_t.

/// @fn bool json_add_key(json_t *json, const char *key)
/// @brief Add a key to an object-like json.
/// @details A key can not be inserted if the json is not an object-like json, or if it already contain the key.
/// @param json An object-like json.
/// @param key A unique string not already contain in \@json.
/// @return True if the key has successfully been inserted. False otherwise.
/// @fn bool json_add_key_value(json_t *json, const char *key, json_t *value)
/// @brief Add a value at a given key to an object-like json.
/// @details A pair can not be inserted if the json is not an object-like json, or if it already possess the key.\n
/// The json will own the value, meaning it will manage to destroy it when it will be destroyed. If this is not intended, use a copy of the value with json_copy or json_copy_new_json.\n
/// If the value is NULL, add a default null-like json.
/// @param json An object-like json.
/// @param key A unique string not already contain in \@json.
/// @param value A json_t to insert.
/// @return True if the pair key-value has successfully been inserted. False otherwise.
/// @fn bool json_set_value_at_key(json_t *json, const char *key, json_t *value)
/// @brief Set a value at a given key to an object-like json.
/// @details A value can not be set if the json is not an object-like json, or if it does not possess the key.\n
/// The json will own the value, meaning it will manage to destroy it when it will be destroyed. If this is not intended, use a copy of the value with json_copy or json_copy_new_json.\n
/// If the value is NULL, set the value to a default null-like json.
/// @param json An object-like json.
/// @param key A string contain in \@json.
/// @param value A json_t to set.
/// @return True if the value has successfully been set. False otherwise.
/// @fn bool json_remove_key(json_t *json, const char *key)
/// @brief Remove a key and its associated value from an object-like json.
/// @details A value can not be remove if the json is not an object-like json.
/// @param json An object-like json.
/// @param key A string contain in \@json.
/// @return True if the pair key-value has successfully been remove. False otherwise.
/// @fn bool json_clean_dict(json_t *json)
/// @brief Remove all key and their associated values from an object-like json.
/// @details The json can not be cleaned if it is not an object-like json.
/// @param json An object-like json.
/// @return True if the json has successfully been cleaned. False otherwise.

/// @fn bool json_add_value_at_index(json_t *json, size_t index, json_t *value)
/// @brief Add a value at a given index to a list-like json.
/// @details A value can not be inserted if ths json is not an list-like json, or if @index is greater to the size.\n
/// The value will be inserted at the given index, effectively increasing the list lize by one and shifting all other values.\n
/// The json will own the value, meaning it will manage to destroy it when it will be destroyed. If this is not intended, use a copy of the value with json_copy or json_copy_new_json.\n
/// If the value is NULL, add a default null-like json.
/// @param json A list-like json.
/// @param index An index lower or equal to the list's size.
/// @param value A json_t to add.
/// @return True if the value has successfully been inserted. False otherwise.
/// @fn bool json_add_value_at_end(json_t *json, json_t *value)
/// @brief Add a value at the end of a list-like json.
/// @details This function has the same behaviour as `json_add_value_at_index(json, json_get_list_size(json), value)`.\n
/// The json will own the value, meaning it will manage to destroy it when it will be destroyed. If this is not intended, use a copy of the value with json_copy or json_copy_new_json.\n
/// If the value is NULL, add a default null-like json.
/// @param json A list-like json.
/// @param value A json_t to add.
/// @return True if the value has successfully been inserted. False otherwise.
/// @fn bool json_set_value_at_index(json_t *json, size_t index, json_t *value)
/// @brief Set a value at a given index on a list-like json.
/// @details A value can not be set if the json is not an list-like json, or if the index is greater or equal to the size.\n
/// The json will own the value, meaning it will manage to destroy it when it will be destroyed. If this is not intended, use a copy of the value with json_copy or json_copy_new_json.\n
/// If the value is NULL, set the value to a default null-like json.
/// @param json A list-like json.
/// @param index An index lower to the list's size.
/// @param value A json_t to set.
/// @return True if the value has successfully been set. False otherwise.
/// @fn bool json_remove_value_at_index(json_t *json, size_t index)
/// @brief Remove a value at a given index of a list-like json.
/// @details A value can not be remove if the json is not an list-like json, or if the index is greater or equal to the size.
/// @param json A list-like json.
/// @param index An index lower to the list's size.
/// @return True if the value has successfully been removed. False otherwise.
/// @fn bool json_remove_value_at_end(json_t *json)
/// @brief Remove a value at the end of a list-like json.
/// @details A value can not be remove if the json is not an list-like json, or if it is empty.
/// @param json A list-like json.
/// @return True if the value has successfully been removed. False otherwise.
/// @fn bool json_clean_list(json_t *json)
/// @brief Remove all values of a list-like json.
/// @details The json can not be cleaned if it is not an list-like json.
/// @param json
/// @return True if the json has successfully been cleaned. False otherwise.

/// @fn void display_json(const json_t *json)
/// @brief Display the content of a json on the standart output.
/// @details It is indented at `JSON_INDENT` spaces. Its default value is 2, this can be overload with a #define command.
/// @param json A json to display.
