//
// Created by sergiy on 9/25/18.
//

#include <cstdint>
#include <estring.h>

#pragma once

namespace verso {

template <typename T>
class gcode_parser_state {
    public:
        gcode_parser_state& reset() {
            return *this;
        }
};
    
template <typename T>
class gcode_lexer {
    public:
        T parse_line(char* line) {
            T result = 0;
            
            while (*line) {
                result = parse_char(*line++);
                
                if (result != 0) {
                    return result;
                }
            }

            return parse_char(0);
        }
        
        T parse_char(uint8_t chr) {
            
        }
};
    
}
