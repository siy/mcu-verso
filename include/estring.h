//
// Created by sergiy on 9/25/18.
//

#include <cassert>
#include <cstdint>

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

            basic_string(basic_string& element) {
                data[0] = 0;
                add(element);
            }

            basic_string(const T* str) {
                data[0] = 0;
                add(str);
            }

            basic_string& reset() {
                data[0] = 0;
                return *this;
            }

            basic_string& add(T element) {
                assert(data[0] < L);
                data[++data[0]] = element;
                return *this;
            }

            basic_string& add(basic_string& element) {
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

            T& operator[](size_t ndx) {
                assert(ndx < len());
                return data[ndx + 1];
            }

            template <typename F>
            basic_string& for_each(F fn) {
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
}