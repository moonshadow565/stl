#pragma once
#ifdef STL_NS
namespace STL_NS {
#else
namespace std {
    using int8_t = signed char;
    using uint8_t = unsigned char;
    using int16_t = signed short;
    using uint16_t = unsigned short;
    using int32_t = signed int;
    using uint32_t = unsigned int;
    using int64_t = signed long long;
    using uint64_t = unsigned long long;
    using size_t = ::size_t;
#endif
    struct __std_type_info_data {
        const char* _UndecoratedName;
        const char _DecoratedName[1];
    };

    using type_info = __std_type_info_data;

    //! a wrapper that may or may not hold an object
    template <typename T>
    struct optional {
        T value;
        bool has_value;
    };

    //! implements binary tuple, i.e. a pair of values
    template <typename K, typename V>
    struct kvpair {
        K key;
        V value;
    };

    //! static contiguous array
    template <typename T, size_t N>
    struct array {
        T data[N];
    };

    //! implements constant length bit array
    template <size_t N>
    struct bitset {
        static constexpr auto zero_word = []{ if constexpr (N <= sizeof(unsigned) * 9) return 0u; else return 0ull; }();
        using word_t = decltype(zero_word);
        word_t words[N == 0 ? 1 : (N + (sizeof(word_t) * 8  - 1)) / (sizeof(word_t) * 8)];
    };

    inline constexpr size_t dynamic_extent = (size_t)-1;

    //! a non-owning view over a contiguous sequence of objects
    //! @note size is known at compiletime
    template <typename T, size_t E = dynamic_extent>
    struct span {
        T* data;
        static constexpr inline size_t size = E;
    };

    //! a non-owning view over a contiguous sequence of objects
    //! @note size is only known at runtime
    template <typename T>
    struct span<T, dynamic_extent> {
        T* data;
        size_t size;
    };

    //! a non-owning view over sequences of characters
    template <typename C>
    struct basic_string_view {
        C* data;
        size_t size;
    };

    //! a non-owning view over sequences of narow character
    using string_view = basic_string_view<char>;

    //! a non-owning view over sequences of wide character
    using wstring_view = basic_string_view<wchar_t>;

    //! a non-owning view over sequences of utf8 character
    using u8string_view = basic_string_view<char>;

    //! a non-owning view over sequences of utf16 character
    using u16string_view = basic_string_view<char16_t>;

    //! a non-owning view over sequences of utf32 character
    using u32string_view = basic_string_view<char32_t>;

    //! stores and manipulates sequences of characters
    template <typename C>
    struct basic_string {
        static_assert(sizeof(C) <= 8, "We need to be able to fit at least 2 chars in SSO buffer(16 bytes)!");
        union data_t {
            C* big;
            C small[16 / sizeof(C)];
        };
        data_t data;
        size_t size;
        size_t reserved;
    };

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

    //! dynamic contiguous array
    template <typename T>
    struct vector {
        T* beg;
        T* end;
        T* cap;
    };

    //! vector of bool specialization
    template <>
    struct vector<bool> {
        vector<unsigned int> data;
        size_t size;
    };

    template <typename T>
    struct forward_list_node {
        forward_list_node* next;
        T value;
    };

    //! singly-linked list
    template <typename T>
    struct forward_list {
        forward_list_node<T>* head;
    };

    template <typename T>
    struct list_node {
        list_node* prev;
        list_node* next;
        T value;
    };

    //! doubly-linked list
    template <typename T>
    struct list {
        list_node<T>* head;
        size_t size;
    };

    template <typename Item, bool Multi>
    struct rb_node {
        rb_node* left;
        rb_node* parent;
        rb_node* right;
        bool is_black;
        bool is_nil;
        Item item;
    };

    template <typename Item, bool Multi>
    struct rb_tree {
        rb_node<Item, Multi>* head;
        size_t size;
    };

    template <typename Item, bool Multi>
    struct hash_table {
        float traits_obj;
        list<Item> elems;
        vector<list_node<Item>*> buckets;
        size_t mask;
        size_t max_index;
    };

    //! collection of unique keys, sorted by keys
    template <typename K>
    struct set : rb_tree<K, false> {};

    //! collection of key-value pairs, sorted by keys, keys are unique
    template <typename K, typename V>
    struct map : rb_tree<kvpair<K, V>, false> {};

    //! collection of keys, sorted by keys, duplicates allowed
    template <typename K>
    struct multiset : rb_tree<K, true> {};

    //! collection of key-value pairs, sorted by keys, duplicates allowed
    template <typename K, typename V>
    struct multimap : rb_tree<kvpair<K, V>, true> {};

    //! collection of unique keys, hashed by keys
    template <typename K>
    struct unordered_set : hash_table<K, false> {};

    //! collection of key-value pairs, hashed by keys, keys are unique
    template <typename K, typename V>
    struct unordered_map : hash_table<kvpair<K, V>, false> {};

    //! collection of keys, hashed by keys, duplicates allowed
    template <typename K>
    struct unordered_multiset : hash_table<K, true> {};

    //! collection of key-value pairs, hashed by keys, duplicates allowed
    template <typename K, typename V>
    struct unordered_multimap : hash_table<kvpair<K, V>, true> {};

    //! double-ended queue
    template <typename T>
    struct deque {
        void* proxy;
        T** map; // pointer to array of pointers to blocks
        size_t mapsize; // size of map array, zero or 2^N
        size_t offset; // offset of initial element
        size_t size; // current length of sequence
    };

    //! adapts a container to provide stack (LIFO data structure)
    template <typename T, typename C = deque<T>>
    struct stack {
        C container;
    };

    //! adapts a container to provide queue (FIFO data structure)
    template <typename T, typename C = deque<T>>
    struct queue {
        C container;
    };

    //! default deleter for unique_ptr
    template <typename T>
    struct default_delete {};

    //! smart pointer with unique object ownership semantics
    template <typename T, typename D = default_delete<T>>
    struct unique_ptr : D {
        T* ptr;
    };

    struct ref_count_base {
        virtual void destroy() noexcept = 0;
        virtual void delete_this() noexcept = 0;
        virtual ~ref_count_base() noexcept = 0;
        virtual void* get_deleter(type_info const& tinfo) const noexcept = 0;
        unsigned long uses;
        unsigned long weaks;
    };

    //! smart pointer with shared object ownership semantics
    template <typename T>
    struct shared_ptr {
        T* ptr;
        ref_count_base* ref_count;
    };

    //! weak reference to an object managed by std::shared_ptr
    template <typename T>
    struct weak_ptr {
        T* ptr;
        ref_count_base* ref_count;
    };

    //! allows an object to create a shared_ptr referring to itself
    template <typename T>
    struct enable_shared_from_this {
        weak_ptr<T> this_weak_ptr;
    };

    template <typename RetT, typename... ArgT>
    struct function_impl {
        virtual function_impl* copy(void* dst) const = 0;
        virtual function_impl* move(void* dst) noexcept = 0;
        virtual RetT call(ArgT&&...) = 0;
        virtual const type_info& traget_type() const noexcept = 0;
        virtual const void* get() const noexcept = 0;
    };

    //! wraps callable object of any copy constructible type with specified function call signature
    template <typename F>
    struct function;

    template <typename RetT, typename... ArgT>
    struct function<RetT(ArgT...)> {
        void* storage[5 + 16 / sizeof(std::size_t)];
        function_impl<RetT, ArgT...>* impl;
    };

    struct thread {
        void* handle;
        unsigned int id;
    };

    struct mutex {
#ifdef _CRT_WINDOWS
        size_t internal[sizeof(std::size_t) == 8 ? 4 : 5];
#else
        size_t internal[sizeof(std::size_t) == 8 ? 10 : 12];
#endif
    };

    struct condition_variable {
#ifdef _CRT_WINDOWS
        size_t internal[2];
#else
        size_t internal[sizeof(std::size_t) == 8 ? 9 : 10];
#endif
    };

    struct recursive_mutex : mutex {};

    struct condition_variable_any {
        shared_ptr<mutex> mutex;
        condition_variable condition;
    };

    struct timed_mutex {
        mutex mutex;
        condition_variable condition;
        unsigned int locked;
    };

    struct recursive_timed_mutex {
        mutex mutex;
        condition_variable condition;
        unsigned int locked;
        unsigned int owner_thread_id;
    };

    template<typename M>
    struct lock_guard {
        M* mutex;
    };

    template<typename M>
    struct unique_lock {
        M* mutex;
        bool owned;
    };
}
