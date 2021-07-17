/*
** EPITECH PROJECT, 2020
** cpp_d15_2019 [WSL: Ubuntu]
** File description:
** ex05
*/

#pragma once

#include <iostream>
#include <iomanip>

template<typename T>
class array {
    public:
        array() : _arr(nullptr), _size(0) {}
        array(size_t size) : _arr(new T[size]), _size(size) { for (size_t i = 0; i != size; i++) _arr[i] = T(); }
        array(const array &arr) : _arr(nullptr) { *this = arr; }
        ~array() { if (_arr != nullptr) delete[] _arr; }

        array &operator=(const array &arr) {
            if (_arr != nullptr)
                delete[] _arr;
            _arr = new T[arr.size()];
            _size = arr.size();
            for (size_t i = 0; i != _size; i++)
                _arr[i] = arr[i];
            for (size_t i = _size; i < arr.size(); i++)
                _arr[i] = T();
            return *this;
        }

        T &operator[](size_t i) {
            if (i >= _size) {
                T *tmp = new T[i+1];
                for (size_t j = 0; _arr != nullptr && j != _size; j++)
                    tmp[j] = _arr[j];
                for (size_t j = (_arr == nullptr ? 0 : _size); j != i+1; j++)
                    tmp[j] = T();
                _size = i+1;
                if (_arr != nullptr)
                    delete[] _arr;
                _arr = tmp;
            }
            return _arr[i];
        }

        T operator[](size_t i) const {
            if (i >= _size)
                throw std::exception();
            return _arr[i];
        }

        size_t size() const { return _size; }
        void dump() const {
            std::cout << "[";
            for (size_t i = 0; i != _size; i++) {
                if (i != 0)
                    std::cout << ", ";
                std::cout << std::boolalpha << _arr[i];
            }
            std::cout << "]" << std::endl;
        }

        template<typename U>
        array<U> convertTo(U (*f)(const T &)) {
            array<U> n(_size);
            for (size_t i = 0; i != _size; i++)
                n[i] = f(_arr[i]);
            return n;
        }
    
    private:
        T *_arr;
        size_t _size;
};