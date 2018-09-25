//
// Created by sergiy on 9/25/18.
//

#include <cstdint>

#include <container.h>

#pragma once

namespace verso {
    template <typename T, size_t L>
    class basic_string : public container<T, L> {
            using index_type = typename container<T, L>::index_type;
            using base_type = container<T, L>;
        public:
            basic_string():base_type() {
            }

            basic_string(basic_string& element):base_type() {
                add(element);
            }

            basic_string(const T* str):base_type() {
                add(str);
            }

            basic_string& reset() {
                base_type::clear();
                return *this;
            }

            basic_string& add(T element) {
                base_type::new_element() = element;
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

            index_type len() {
                return base_type::size();
            }
    };

    template <size_t L>
    class basic_byte_string : public basic_string <uint8_t, L>{};

    using string8   = basic_byte_string<8>;
    using string16  = basic_byte_string<16>;
    using string32  = basic_byte_string<32>;
    using string64  = basic_byte_string<64>;
    using string128 = basic_byte_string<128>;
    using string256 = basic_byte_string<256>;
}