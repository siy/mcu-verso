//
// Created by sergiy on 9/25/18.
//

#include <climits>
#include <cstdint>

#include <conditional.h>
#include <limits>

#pragma once

namespace verso {
    template <int S>
    using index_type_t = typename conditional< S <= std::numeric_limits<uint8_t>::max(),
                                    uint8_t,
                                    conditional<S <= std::numeric_limits<uint16_t>::max(),
                                               uint16_t,
                                               uint32_t>>::type;
}