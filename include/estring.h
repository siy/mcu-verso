//
// Created by sergiy on 9/25/18.
//

#include <cassert>
#include <cstdint>
#include <utility>
#include <limits>
#include <cstdlib>

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

            basic_string(const T* str) {
                data[0] = 0;
                add(str);
            }

            basic_string(const T* str, int num) {
                data[0] = 0;

                while(*str && num > 0) {
                    add(*str++);
                }
            }

            T* first() const {
                return const_cast<T*>(&data[1]);
            }

            T* last() const {
                return const_cast<T*>(&data[L]);
            }

            const T* begin() const {
                assert(data[0] > 0);

                return first();
            }

            const T* end() const {
                assert(data[0] > 0);

                return &data[data[0] - 1];
            }

            const basic_string& reset() {
                data[0] = 0;
                return *this;
            }

            const basic_string& add(const T element) {
                assert(data[0] <= L);

                data[++data[0]] = element;
                return *this;
            }

            const basic_string& add(const basic_string& element) {
                element.for_each([=](T val) {add(val);});
                return *this;
            }

            const basic_string& add(const T* str) {
                if (!str) {
                    return *this;
                }

                while(*str) {
                    add(*str++);
                }

                return *this;
            }

            const basic_string operator() (T from, T to) const {
                return basic_string{*this, from, to};
            }

            const basic_string& operator += (const basic_string& other) {
                return add(other);
            }

            const basic_string& operator += (const T* str) {
                return add(str);
            }

            const basic_string& operator += (const T element) {
                return add(element);
            }

            const T& operator[](const size_t ndx) const {
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

            size_t len() const {
                return size_t(data[0]);
            }

            constexpr size_t size() const {
                return L;
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

    namespace estring {
        template <typename V>
        using string_type_t = typename conditional<std::numeric_limits<V>::max() < 999999,
                                                   string7,
                                                   conditional<std::numeric_limits<V>::max() < 99999999999999,
                                                               string15,
                                                               string31>>::type;

        //TODO: WIP
        template <typename V>
        inline string15 of(const V val) {
//            using str = typename conditional<std::numeric_limits<V>::max() < 999999, string7,
//                                             conditional<std::numeric_limits<V>::max() < 999999999, string15, string31>>::type;

            //using str = string_type_t<V>;
            basic_byte_string<15> data;

            bool sign = val < 0;

            V x = std::abs(val);

            uint8_t* s = data.last();

            if (!x) {
                *--s = '0';
            }

            for (; x; x/=10) {
                *--s = '0' + x % 10;
            }

            if (sign) {
                *--s = '-';
            }

            return string15((const uint8_t*)s, int(data.last() - s));
        }
    }
}

