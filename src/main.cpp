#define _ALLOW_KEYWORD_MACROS
#define private public
#include <array>
#include <bitset>
#include <condition_variable>
#include <deque>
#include <forward_list>
#include <functional>
#include <list>
#include <map>
#include <memory_resource>
#include <mutex>
#include <optional>
#include <queue>
#include <set>
#include <span>
#include <stack>
#include <string>
#include <string_view>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>

#define STL_NS test
#include "stl_msvc.hpp"

#define TEST(message, ...)                   \
    static_assert(                           \
        [] {                                 \
            using namespace std;             \
            return sizeof(__VA_ARGS__);      \
        }() ==                               \
            [] {                             \
                using namespace STL_NS;      \
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
    TEST("", array<int, 3>);
    TEST("", array<int, 3>::iterator);

    TEST("", bitset<0>);
    TEST("", bitset<0>::reference);

    TEST("", bitset<7>);
    TEST("", bitset<9>);
    TEST("", bitset<32>);
    TEST("", bitset<65>);

    TEST("", span<char>);
    TEST("", span<char>::iterator);

    TEST("", span<char, 1>);
    TEST("", span<char, 1>::iterator);

    TEST("", string_view);
    TEST("", string_view::iterator);

    TEST("", wstring_view);
    TEST("", wstring_view::iterator);

    TEST("", u8string_view);
    TEST("", u8string_view::iterator);

    TEST("", u16string_view);
    TEST("", u16string_view::iterator);

    TEST("", u32string_view);
    TEST("", u32string_view::iterator);

    TEST("", string);
    TEST("", string::iterator);

    TEST("", wstring);
    TEST("", wstring::iterator);

    TEST("", u8string);
    TEST("", u8string::iterator);

    TEST("", u16string);
    TEST("", u16string::iterator);

    TEST("", u32string);
    TEST("", u32string::iterator);

    TEST("", optional<char>);
    TEST("", optional<int>);
    TEST("", optional<empty_t1>);
    TEST("", optional<optional<char>>);

    TEST("", vector<char>);
    TEST("", vector<char>::iterator);

    TEST("", vector<bool>);
    TEST("", vector<bool>::iterator);

    TEST("", forward_list<int>);
    TEST("", forward_list<int>::iterator);

    TEST("", set<int>);
    TEST("", set<int>::iterator);

    TEST("", map<int, int>);
    TEST("", map<int, int>::iterator);

    TEST("", multiset<int>);
    TEST("", multiset<int>::iterator);

    TEST("", multimap<int, int>);
    TEST("", multimap<int, int>::iterator);

    TEST("", unordered_set<int>);
    TEST("", unordered_set<int>::iterator);

    TEST("", unordered_map<int, int>);
    TEST("", unordered_map<int, int>::iterator);

    TEST("", unordered_multiset<int>);
    TEST("", unordered_multiset<int>::iterator);

    TEST("", unordered_multimap<int, int>);
    TEST("", unordered_multimap<int, int>::iterator);

    TEST("", unique_ptr<int>);
    TEST("", shared_ptr<int>);
    TEST("", weak_ptr<int>);
    TEST("", enable_shared_from_this<int>);
    TEST("", function<int(float, short)>);

    TEST("", deque<int>);
    TEST("", queue<int>);
    TEST("", stack<int>);

    TEST("", thread);

    TEST("", mutex);

    TEST("", recursive_mutex);

    TEST("", condition_variable);

    TEST("", condition_variable_any);

    TEST("", timed_mutex);

    TEST("", recursive_timed_mutex);

    TEST("", lock_guard<mutex>);

    TEST("", unique_lock<mutex>);

    return 0;
}
