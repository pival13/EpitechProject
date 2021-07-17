/*
** A Kevin Pruvost's project, May 2020
** KVector.hpp
** File description:
** my vector enhancement
*/

#pragma once

// Project includes
#include "Exception.hpp"

// C++ includes
#include <vector>
#include <list>
#include <algorithm>
#include <ostream>

template<typename T, typename Alloc = std::allocator<T>>
class KVector : public std::vector<T>
{
public:
    using std::vector<T>::vector;
    ~KVector() = default;

    T & operator[](size_t pos) { return this->at(pos); }
    const T & operator[](size_t pos) const { return this->at(pos); }
    KVector<KVector<T>> split(size_t nb) const
    {
        KVector<KVector<T>> newVector;
        KVector<T> temp = (*this);
        if (temp.size() == 0)
            return newVector;
        if (temp.size() < nb)
        {
            while (!temp.empty())
            {
                newVector.emplace_back();
                newVector.back().push_back(temp[0]);
                temp.erase(temp.begin());
            }
            return newVector;
        }

        for (size_t i = 0; i < nb; ++i)
            newVector.emplace_back();
        double gap = (double)temp.size() / nb;
        size_t isize = (size_t)gap;
        gap -= isize;
        size_t i = 0;
        while (!temp.empty())
        {
            if (temp.empty())
                return newVector;
            newVector[i].push_back(temp[0]);
            temp.erase(temp.begin());
            if (newVector[i].size() + (((double)(i + 1) / nb > gap) ? 1 : 0) > isize)
                ++i;
        }
        return newVector;
    }

    using std::vector<T>::erase;
    void eraseAt(size_t index) { if (!this->empty() && index < this->size()) std::vector<T>::erase(this->begin() + index); }
    void removeAt(size_t index) { eraseAt(index); }
    void eraseAt(typename KVector<T>::const_iterator ite) { std::vector<T>::erase(ite); }
    void removeAt(typename KVector<T>::const_iterator ite) { std::vector<T>::erase(ite); }
    void remove(typename KVector<T>::const_iterator ite1, typename KVector<T>::const_iterator ite2) { std::vector<T>::erase(ite1, ite2); }
    void remove(size_t index1, size_t index2)
    {
        if (index1 > index2)
            throw EXCEPTION("Index 1 is superior to Index 2 : " + std::to_string(index1) + " | " + std::to_string(index2));
        if (index1 > this->size())
            throw EXCEPTION("Index 1 is superior to the vector's size : " + std::to_string(index1) + " | " + std::to_string(this->size()));
        if (index2 > this->size())
            throw EXCEPTION("Index 2 is superior to the vector's size : " + std::to_string(index2) + " | " + std::to_string(this->size()));
        std::vector<T>::erase(this->begin() + index1, this->begin() + index2);
    }
    void removeFirst() { erase(this->begin()); }
    void removeLast() { removeAt(this->size() - 1); }

    bool contains(const T & obj) const { return std::find(this->begin(), this->end(), obj) != this->end(); }

    /******************************/
    /***** Pattern searching.******/
    /******************************/
    typename KVector<T>::iterator firstIteratorOf(const T & obj) { return std::find(this->begin(), this->end(), obj); }
    typename KVector<T>::const_iterator firstIteratorOf(const T & obj) const { return std::find(this->begin(), this->end(), obj); }
    typename KVector<T>::iterator lastIteratorOf(const T & obj) { return std::find(this->rbegin(), this->rend(), obj); }
    typename KVector<T>::const_iterator lastIteratorOf(const T & obj) const { return std::find(this->rbegin(), this->rend(), obj); }
    KVector<typename KVector<T>::iterator> iteratorsOf(const T & obj)
    {
        KVector<typename KVector<T>::iterator> indexes;
        auto start = this->begin();
        auto ite = std::find(start, this->end(), obj);
        while (ite != this->end())
        {
            indexes.push_back(ite);
            start = ite + 1;
            ite = std::find(start, this->end(), obj);
        }
        return indexes;
    }
    KVector<typename KVector<T>::const_iterator> iteratorsOf(const T & obj) const { return static_cast<KVector<typename KVector<T>::const_iterator>>((static_cast<KVector<typename KVector<T>::iterator> (KVector<T>::*)(const T &) const>(&iteratorsOf))(obj)); }

    // Index searching methods all return KVector<T>::npos when the
    // specified object is not found.
    const static size_t npos = static_cast<size_t>(-1);
    size_t firstIndexOf(const T & obj) const { auto ite = std::find(this->begin(), this->end(), obj); return ((ite == this->end()) ? npos : ite - this->begin());};
    size_t lastIndexOf(const T & obj) const { auto ite = std::find(this->rbegin(), this->rend(), obj); return ((ite == this->rend()) ? npos : this->size() - 1 - (ite - this->rbegin()));};
    KVector<size_t> indexesOf(const T & obj)
    {
        KVector<size_t> indexes;
        auto ites = iteratorsOf(obj);
        for (const auto & ite : ites)
            indexes.push_back(ite - this->begin());
        return indexes;
    }

    KVector<T> & operator+(const KVector<T> & vec) { for (const auto & obj : vec) this->push_back(obj); return *this; }
    KVector<T> & operator+(const T & obj) { this->push_back(obj); return *this; }
    KVector<T> & operator+=(const KVector<T> & vec) { for (const auto & obj : vec) this->push_back(obj); }
    KVector<T> & operator+=(const T & obj) { this->push_back(obj); return *this; }
    void insertAt(typename KVector<T>::iterator ite, const T & obj) { std::vector<T>::insert(ite, obj); };
    void insertAt(size_t index, const T & obj) { insertAt(this->begin() + index, obj); };

    std::list<T> toStdList() { std::list<T> list; for (size_t i = 0; i < this->size(); ++i) list.push_back((*this)[i]); return list; }
    std::vector<T> toStdVector() { return *this; }
};

#include <sstream>

template<typename T>
std::ostream & operator<<(std::ostream & os, const KVector<T> & foo)
{
    std::stringstream ss;
    ss << "[";
    for (size_t i = 0; i < foo.size(); ++i)
        ss << foo[i] << ((i + 1 < foo.size()) ? ", " : "");
    ss << "]";
    return os << ss.str();
}