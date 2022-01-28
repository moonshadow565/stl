#pragma once
#ifdef STL_MSVC_NS
namespace STL_MSVC_NS {
#else
namespace std {
#endif
    //! the default allocator
    template <typename T>
    struct allocator {};

    //! std::hash specializations for fundamental, enumeration, and pointer types
    template <typename T>
    struct hash {};

    //! function object implementing x == y
    template <typename T>
    struct equal_to {};

    //! function object implementing x != y
    template <typename T>
    struct not_equal_to {};

    //! function object implementing x > y
    template <typename T>
    struct greater {};

    //! function object implementing x < y
    template <typename T>
    struct less {};

    //! function object implementing x >= y
    template <typename T>
    struct greater_equal {};

    //! function object implementing x <= y
    template <typename T>
    struct less_equal {};

    //! Class Template which describes properties of a character type
    template <typename T>
    struct char_traits {};

    //! default deleter for unique_ptr
    template <typename T>
    struct default_delete {};

    //! stores and manipulates sequences of characters
    template <typename C, typename T = char_traits<C>, typename A = allocator<C>>
    struct basic_string;

    //! stores and manipulates sequences of narow character
    using string = basic_string<char>;

    //! stores and manipulates sequences of wide character
    using wstring = basic_string<wchar_t>;

    //! stores and manipulates sequences of utf8 character
    using u8string = basic_string<char>;

    //! stores and manipulates sequences of utf16 character
    using u16string = basic_string<char16_t>;

    //! stores and manipulates sequences of utf32 character
    using u32string = basic_string<char32_t>;

    //! stores and manipulates sequences of characters
    template <typename C, typename T = char_traits<C>, typename A = allocator<C>>
    struct basic_string_view;

    //! stores and manipulates sequences of narow character
    using string_view = basic_string_view<char>;

    //! stores and manipulates sequences of wide character
    using wstring_view = basic_string_view<wchar_t>;

    //! stores and manipulates sequences of utf8 character
    using u8string_view = basic_string_view<char>;

    //! stores and manipulates sequences of utf16 character
    using u16string_view = basic_string_view<char16_t>;

    //! stores and manipulates sequences of utf32 character
    using u32string = basic_string<char32_t>;

    //! a non-owning view over a contiguous sequence of objects
    template <typename T, size_t E = (size_t)-1>
    struct span;

    //! a wrapper that may or may not hold an object
    template <typename T>
    struct option;

    //! placeholder type for use as the first alternative in a variant of non-default-constructible types
    struct monostate {};

    //! a type-safe discriminated union
    template <typename... T>
    struct variant;

    //! implements binary tuple, i.e. a pair of values
    template <typename T0, typename T1>
    struct pair;

    //! static contiguous array
    template <typename T, size_t N>
    struct array;

    //! implements constant length bit array
    template <size_t N>
    struct bitset;

    //! dynamic contiguous array
    template <typename T, typename A = allocator<T>>
    struct vector;

    //! double-ended queue
    template <typename T, typename A = allocator<T>>
    struct deque;

    //! singly-linked list
    template <typename T, typename A = allocator<T>>
    struct forward_list;

    //! doubly-linked list
    template <typename T, typename A = allocator<T>>
    struct list;

    //! collection of unique keys, sorted by keys
    template <typename K, typename L = less<K>, typename A = allocator<K>>
    struct set;

    //! collection of key-value pairs, sorted by keys, keys are unique
    template <typename K, typename V, typename L = less<K>, typename A = allocator<pair<K, V>>>
    struct map;

    //! collection of keys, sorted by keys
    template <typename K, typename L = less<K>, typename A = allocator<K>>
    struct multiset;

    //! collection of key-value pairs, sorted by keys
    template <typename K, typename V, typename L = less<K>, typename A = allocator<pair<K, V>>>
    struct multimap;

    //! collection of unique keys, hashed by keys
    template <typename K, typename H = hash<K>, typename E = equal_to<K>, typename A = allocator<K>>
    struct unordered_set;

    //! collection of key-value pairs, hashed by keys, keys are unique
    template <typename K,
              typename V,
              typename H = hash<K>,
              typename E = equal_to<K>,
              typename A = allocator<pair<K, V>>>
    struct unordered_map;

    //! collection of keys, hashed by keys
    template <typename K, typename H = hash<K>, typename E = equal_to<K>, typename A = allocator<K>>
    struct unordered_multiset;

    //! collection of key-value pairs, hashed by keys
    template <typename K,
              typename V,
              typename H = hash<K>,
              typename E = equal_to<K>,
              typename A = allocator<pair<K, V>>>
    struct unordered_multimap;

    //! adapts a container to provide stack (LIFO data structure)
    template <typename T, typename C = deque<T>>
    struct stack;

    //! adapts a container to provide queue (FIFO data structure)
    template <typename T, typename C = deque<T>>
    struct queue;

    //! adapts a container to provide priority queue
    template <typename T, typename C = vector<T>, typename L = less<T>>
    struct priority_queue;

    //! smart pointer with unique object ownership semantics
    template <typename T, typename D = default_delete<T>>
    struct unique_ptr;

    //! smart pointer with shared object ownership semantics
    template <typename T>
    struct shared_ptr;

    //! weak reference to an object managed by std::shared_ptr
    template <typename T>
    struct weak_ptr;

    //! allows an object to create a shared_ptr referring to itself
    template <typename T>
    struct enable_shared_from_this;

    //! wraps callable object of any copy constructible type with specified function call signature
    template <typename>
    struct function;
}