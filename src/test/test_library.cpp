//
// Created by sergiy on 9/25/18.
//

#include <lest.hpp>
#include <container.h>
#include <gcode.h>

using namespace verso;

using test_container_t = container<uint32_t, 10>;

const lest::test specification[] = {
    SCENARIO("Containers can be size up to predefined size " "[container]") {
        GIVEN("A container with some elements") {
            test_container_t tc;

            EXPECT(tc.size() == 0);
            EXPECT(tc.capacity() == 10);

            WHEN("Element is added as is") {
                tc.new_element() = 123;

                THEN("Container grows") {
                    EXPECT(tc.size() == 1);
                    EXPECT(tc[0] == 123);
                }
            }
            WHEN("Element is added as index") {
                auto index = tc.new_index();
                tc[index] = 321;

                THEN("Container grows") {
                    EXPECT(tc.size() == 1);
                    EXPECT(tc[index] == 321);
                }
            }
        }
    },
    SCENARIO("Simple string test " "[string]") {
        GIVEN("An empty string") {
            string7 s;

            EXPECT(s.len() == 0);

            WHEN("Element is added") {
                s.add('A');

                THEN("String grows") {
                    EXPECT(s.len() == 1);
                    EXPECT(s[0] == 'A');
                }
            }
            WHEN("Other string is added") {
                string7 n{(const uint8_t *) "Hi"};
                s.add(n);

                THEN("String content is appended") {
                    EXPECT(s.len() == 2);
                    EXPECT(s[0] == 'H');
                    EXPECT(s[1] == 'i');
                }
            }
            WHEN("Constant is added") {
                auto c = (const uint8_t *) "Lo";
                s.add(c);

                THEN("String content is appended") {
                    EXPECT(s.len() == 2);
                    EXPECT(s[0] == 'L');
                    EXPECT(s[1] == 'o');
                }
            }
        }
    },
//    CASE("Simple lexer test") {
//        EXPECT(gcode_parser().parse_line("G0 x10.1 y 00000123.456789"));
//    }
};

int main(int argc, char** argv) {
    return lest::run(specification, argc, argv);
}