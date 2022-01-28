#include <array>
#include <bitset>
#include <functional>
#include <map>
#include <set>
#include <span>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>
#define STL_MSVC_NS msvc_std
#include "stl_msvc.hpp"

#define TEST(message, ...) static_assert(sizeof(std::__VA_ARGS__) == sizeof(STL_MSVC_NS::__VA_ARGS__), message)

int main() { return 0; }
