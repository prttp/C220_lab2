#pragma once
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

template<typename T>
class UVector {
    std::vector<T> d;
	T m_min{};
	T m_max{};
   typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;
 public:
    UVector(const std::initializer_list<T>& data = {}) : d{} {
		d.reserve(data.size());
        for (const auto& element : data) {
            if ((element > m_min) && (element < m_max)&&(std::count(d.cbegin(), d.cend(), element) == 0)) {
                d.emplace_back(element);
            }
        }
    }
	~UVector() = default; 

    void add(const std::initializer_list<T>& data) {
        for (const auto& element : data) {
            if ((std::count(d.cbegin(), d.cend(), element) == 0) && (element > m_min) && (element < m_max)) {
                d.emplace_back(element);
               
            }
        }
    }
    void erase(const std::initializer_list<T>& data) {
        for (auto eit = data.begin(); eit != data.end(); eit++) {
            auto it = std::find(d.cbegin(), d.cend(), *eit);
            if (it != d.cend()) {
                d.erase(it);
            }
        }
    }
    void sort(bool less) {
        if (less) {
            std::sort(d.begin(), d.end(), std::less<>());
        }
        else {
            std::sort(d.begin(), d.end(), std::greater<>());
        }
    }
    UVector& operator= (const std::initializer_list<T>& data) {
        d.clear();
        add(data);
        return *this;
    }
	UVector& operator= (const UVector& other) = default;
    std::size_t size() const {
        return d.size();
    }
    const T& operator[](int i) const {
        return d[i];
    }
    const_iterator cbegin() const {
        return d.cbegin();
    }
    const_iterator cend() const {
        return d.cend();
    }
    iterator begin() {
        return d.begin();
    }
    iterator end() {
        return d.end();
    }
    const T& at(std::size_t i) const {
        if (i < 0 || i >= size()) {
            throw std::range_error("Out of range!");
        }
        else {
            return d[i];
        }
    }
    T& at(std::size_t i) {
        if (i < 0 || i >= size()) {
            throw std::range_error("Out of range!");
        }
        else {
            return d[i];
        }
    }
};
template <typename T>
void printUVec(const UVector<T>& v) {
    for (std::size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << std::endl;
    }
    std::cout << "-----------------" << std::endl;
}