//
// Created by sergiy on 9/25/18.
//

#include <lest.hpp>
#include <container.h>

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
    }
};

int main(int argc, char** argv) {
    return lest::run(specification, argc, argv);
}