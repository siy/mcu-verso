//
// Created by sergiy on 9/25/18.
//

#include <cassert>
#include <cstdint>
#include <utility>

#pragma once

using namespace std;

namespace verso {
    template <typename T, size_t L>
    class basic_string {
            using index_type = T;
            static constexpr size_t Size = L + 1;

            T data[Size];

        public:
            basic_string() {
                data[0] = 0;
            }

            basic_string(const basic_string& element, T from, T to) {
                data[0] = 0;

                while (from != to) {
                    add(element.data[1 + from++]);
                }
            }

            basic_string(const basic_string& element) {
                data[0] = 0;
                add(element);
            }

            T* first() {
                return &data[1];
            }

            T* last() {
                return &data[L];
            }

            T* begin() {
                assert(data[0] > 0);

                return first();
            }

            T* end() {
                assert(data[0] > 0);

                return &data[data[0] - 1];
            }

            basic_string(const T* str) {
                data[0] = 0;
                add(str);
            }

            basic_string& reset() {
                data[0] = 0;
                return *this;
            }

            basic_string& add(const T element) {
                assert(data[0] <= L);
                data[++data[0]] = element;
                return *this;
            }

            basic_string& add(const basic_string& element) {
                element.for_each([=](T val) {add(val);});
                return *this;
            }

            basic_string& add(const T* str) {
                if (!str) {
                    return *this;
                }

                while(*str) {
                    add(*str++);
                }

                return *this;
            }

            basic_string operator() (T from, T to) {
                return basic_string(*this, from, to);
            }

            basic_string& operator += (basic_string& other) {
                return add(other);
            }

            basic_string& operator += (const T* str) {
                return add(str);
            }

            basic_string& operator += (const T element) {
                return add(element);
            }

            const T& operator[](size_t ndx) {
                assert(ndx < len());
                return data[ndx + 1];
            }

            template <typename F>
            const basic_string& for_each(F fn) const {
                for(size_t i = 1; i <= data[0]; i++) {
                    fn(data[i]);
                }
                return *this;
            }

            size_t len() {
                return size_t(data[0]);
            }
    };

    template <size_t L>
    class basic_byte_string : public basic_string <uint8_t, L>{};

    using string7   = basic_byte_string<7>;
    using string15  = basic_byte_string<15>;
    using string31  = basic_byte_string<31>;
    using string63  = basic_byte_string<63>;
    using string127 = basic_byte_string<127>;
    using string255 = basic_byte_string<255>;

//    namespace string {
//
//        //TODO: WIP
//        template <typename V>
//        inline string31 of(V val) {
//            string31 data;
//
//            T* s = data.last();
//
//            if (!x) {
//                *--s = '0';
//            }
//
//            for (; x; x/=10) {
//                *--s = '0' + x % 10;
//            }
//        }
//
//    }
}

