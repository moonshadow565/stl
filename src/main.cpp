#include <array>
#include <bitset>
#include <functional>
#include <map>
#include <optional>
#include <set>
#include <span>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>

#define STL_MSVC_NS test
#include "stl_msvc.hpp"

#define TEST(message, ...) static_assert(sizeof(std::__VA_ARGS__) == sizeof(STL_MSVC_NS::__VA_ARGS__), message)

struct empty_t1 {};
struct empty_t2 {};

int main() {
    TEST("array basic", array<char, 1>);

    TEST("bitset 0", bitset<0>);
    TEST("bitset 7", bitset<7>);
    TEST("bitset 9", bitset<9>);
    TEST("bitset 32", bitset<32>);
    TEST("bitset 65", bitset<65>);

    TEST("span", span<char>);
    TEST("span", span<char, 1>);
    TEST("span", span<char, (size_t)-1>);

    TEST("pair of ints", pair<int, int>);
    TEST("pair of int and char", pair<int, char>);

    TEST("string_view", string_view);
    TEST("u8string_view", u8string_view);
    TEST("u16string_view", u16string_view);
    TEST("u32string_view", u32string_view);

    TEST("string", string);
    TEST("u8string", u8string);
    TEST("u16string", u16string);
    TEST("u32string", u32string);

    return 0;
}
