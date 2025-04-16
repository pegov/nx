#pragma once

#include <stdlib.h>
#include <string.h>

#include "types.h"

template<typename T>
struct Foo {
    T* value;
};

template<typename T>
struct ArrayView {
    T *arr;
    usize len;

    static ArrayView from_raw(const T* arr, usize len);

    class Iterator {
    public:
        Iterator(const T* const ptr) : curr(ptr) {}

        const T& operator*() const { return *curr; }
        Iterator& operator++() {
            ++curr;
            return *this;
        }
        Iterator operator++(int) {
            Iterator temp = *this;
            ++curr;
            return temp;
        }
        bool operator==(const Iterator& other) const { return curr == other.curr; }
        bool operator!=(const Iterator& other) const { return curr != other.curr; }

    private:
        const T* curr;
    };

    Iterator begin() const { return Iterator(arr); }
    Iterator end() const { return Iterator(arr + len); }
};

template<typename T>
struct Array {
    T* arr;
    usize len;
    usize cap;

    static Array create();
    static Array create(usize size);

    void resize(usize new_size);
    void append(T value);

    void extend(T *src, usize src_len); // TODO
    void extend(ArrayView<T> av); // TODO

    ArrayView<T> view();
};

template<typename T>
ArrayView<T> ArrayView<T>::from_raw(const T* arr, usize len) {
    return ArrayView<T>{
        .arr = (T*)arr,
        .len = len,
    };
}

template<typename T>
Array<T> Array<T>::create() {
    return Array<T>{
        .arr = nullptr,
        .len = 0,
        .cap = 0,
    };
}

template<typename T>
Array<T> Array<T>::create(usize len) {
    usize size = sizeof(T)*len;
    T* arr = malloc(sizeof(T)*len);
    memset(arr, 0, len);
    return Array<T>{
        .arr = arr,
        .len = len,
        .cap = len,
    };
}

template<typename T>
void Array<T>::resize(usize new_size) {
    if (new_size < this->cap) {
        return;
    }

    usize new_len = sizeof(T)*new_size;
    T* new_arr = (T*)malloc(sizeof(T)*new_size);
    memset(new_arr, 0, new_len);
    memcpy(new_arr, this->arr, sizeof(T)*this->len);
    free(this->arr);
    this->arr = new_arr;
    this->len = new_len;
    this->cap = new_len;
}

template<typename T>
void Array<T>::append(T value) {
    if (this->len == this->cap) {
        this->resize(this->cap*2);
    }

    this->arr[len++] = value;
}

template<typename T>
void Array<T>::extend(T *src, usize src_len) {
    if (this->len + src_len > this->cap) {
        this->resize(this->len + src_len);
    }

    memcpy(&this->arr[this->len], src, sizeof(T)*src_len);
    this->len = this->len + src_len;
}

template<typename T>
void Array<T>::extend(ArrayView<T> av) {
    this->extend(av.arr, av.len);
}

template<typename T>
ArrayView<T> Array<T>::view() {
    return ArrayView<T>::from_raw(this->arr, this->len);
}

