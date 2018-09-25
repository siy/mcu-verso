//
// Created by sergiy on 9/25/18.
//
#include <cassert>
#include <util.h>

#pragma once

namespace verso {
    template <typename T, int Size>
    class container {
            using index_type = index_type_t<Size>;

            index_type_t<Size> used;
            T data[Size];
        public:

            container():used {0} {}

            index_type new_index() {
                assert(used < Size);

                return used++;
            }

            T& new_element() {
                assert(used < Size);

                return data[used++];
            }

            constexpr index_type capacity() {
                return Size;
            }

            index_type size() {
                return used;
            }

            template <typename F>
            container& for_each(F fn) {
                for(index_type i = 0; i < used; i++) {
                    fn(data[i]);
                }
                return *this;
            }

            T& operator[](index_type ndx) {
                assert(ndx < Size);

                return data[ndx];
            }
    };
}