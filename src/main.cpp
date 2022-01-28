#define _ALLOW_KEYWORD_MACROS
#define private public
#include <array>
#include <bitset>
#include <functional>
#include <map>
#include <memory_resource>
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

#define TEST(message, ...)                   \
    static_assert(                           \
        [] {                                 \
            using namespace std;             \
            return sizeof(__VA_ARGS__);      \
        }() ==                               \
            [] {                             \
                using namespace STL_MSVC_NS; \
                return sizeof(__VA_ARGS__);  \
            }(),                             \
        message)

struct empty_t1 {};
struct empty_t2 {};

template <typename T>
struct fake_less {
    void* junk[16 / sizeof(void*)];
    bool operator()(T const&, T const&) const noexcept { return true; }
};

struct undefined;

int main() {
    TEST("array basic", array<char, 1>);
    TEST("array of array", array<array<int, 3>, 5>);

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

    TEST("optional char", optional<char>);
    TEST("optional int", optional<int>);
    TEST("optional empty_t1", optional<empty_t1>);
    TEST("optional of optional", optional<optional<char>>);

    TEST("vector of char", vector<char>);
    TEST("vector of char with allocator", vector<char, std::pmr::polymorphic_allocator<char>>);

    return 0;
}
