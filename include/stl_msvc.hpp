#pragma once
#ifdef STL_MSVC_NS
namespace STL_MSVC_NS {
#else
namespace std {
#endif
    struct __std_type_info_data {
        const char* _UndecoratedName;
        const char _DecoratedName[1];
    };

    using type_info = __std_type_info_data;

    //! conditonal::type is TrueT or FalseT depending on Condition
    template <bool Condition, typename TrueT, typename FalseT>
    struct conditional;

    //! conditonal::type is TrueT
    template <typename TrueT, typename FalseT>
    struct conditional<true, TrueT, FalseT> {
        using type = TrueT;
    };

    //! conditonal::type is FalseT
    template <typename TrueT, typename FalseT>
    struct conditional<false, TrueT, FalseT> {
        using type = FalseT;
    };

    //! conditonal_t is TrueT or FalseT depending on Condition
    template <bool Condition, typename TrueT, typename FalseT>
    using conditional_t = typename conditional<Condition, TrueT, FalseT>::type;

    //! a wrapper that may or may not hold an object
    template <typename T>
    struct optional {
        T value;
        bool has_value;
    };

    //! implements binary tuple, i.e. a pair of values
    template <typename T0, typename T1>
    struct pair {
        T0 first;
        T1 second;
    };

    //! static contiguous array
    template <typename T, size_t N>
    struct array {
        using iterator = T*;

        T data[N];
    };

    //! implements constant length bit array
    template <size_t N>
    struct bitset {
        using word_t = conditional_t<N <= sizeof(unsigned long) * 8, unsigned long, unsigned long long>;
        static constexpr inline size_t words_per_bit = sizeof(word_t) * 8;

        struct reference {
            word_t* word;
            size_t offset;
        };

        word_t words[N == 0 ? 1 : (N + words_per_bit - 1) / words_per_bit];
    };

    inline constexpr size_t dynamic_extent = (size_t)-1;

    //! a non-owning view over a contiguous sequence of objects
    //! @note size is known at compiletime
    template <typename T, size_t E = dynamic_extent>
    struct span {
        using iterator = T*;

        T* data;
        static constexpr inline size_t size = E;
    };

    //! a non-owning view over a contiguous sequence of objects
    //! @note size is only known at runtime
    template <typename T>
    struct span<T, dynamic_extent> {
        using iterator = T*;

        T* data;
        size_t size;
    };

    //! stores and manipulates sequences of characters
    template <typename C>
    struct basic_string_view {
        using iterator = C*;

        C* data;
        size_t size;
    };

    //! stores and manipulates sequences of narow character
    using string_view = basic_string_view<char>;

    //! stores and manipulates sequences of wide character
    using wstring_view = basic_string_view<wchar_t>;

    //! stores and manipulates sequences of utf8 character
    using u8string_view = basic_string_view<char>;

    //! stores and manipulates sequences of utf16 character
    using u16string_view = basic_string_view<char16_t>;

    //! stores and manipulates sequences of utf32 character
    using u32string_view = basic_string_view<char32_t>;

    //! stores and manipulates sequences of characters
    template <typename C>
    struct basic_string {
        static_assert(sizeof(C) <= 8, "We need to be able to fit at least 2 chars in SSO buffer(16 bytes)!");
        union data_t {
            C* big;
            C small[16 / sizeof(C)];
        };
        using iterator = C*;

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
        using iterator = T*;

        T* beg;
        T* end;
        T* cap;
    };

    //! vector of bool specialization
    template <>
    struct vector<bool> {
        struct iterator {
            unsigned int* ptr;
            size_t offset;
        };

        vector<unsigned int> data;
        size_t size;
    };

    //! singly-linked list
    template <typename T>
    struct forward_list {
        struct node_t {
            node_t* next;
            T value;
        };
        struct iterator {
            node_t* ptr;
        };

        node_t* head;
    };

    //! doubly-linked list
    template <typename T>
    struct list {
        struct node_t {
            node_t* prev;
            node_t* next;
            T value;
        };
        struct iterator {
            node_t* ptr;
        };

        node_t* head;
        size_t size;
    };

    template <typename Item>
    struct tree {
        enum color_t : char {
            RED,
            BLACK,
        };

        struct node_t {
            // left subtree, or smallest element if head
            node_t* left;
            // parent, or root of tree if head
            node_t* parent;
            // right subtree, or largest element if head
            node_t* right;
            // RED or BLACK, BLACK if head
            color_t color;
            // true only if head (also nil) node; TRANSITION, should be bool
            bool is_nil;
            // the stored value, unused if head
            Item item;
        };

        struct iterator {
            node_t* ptr;
        };

        node_t* head;
        size_t size;
    };

    template <typename Item>
    struct hash {
        using list = list<Item>;
        using iterator = typename list::iterator;

        // used for comparing
        float traits_obj;
        // list of elements
        list list_elems;
        // iterators for buckets. each bucket is 2 iterators denoting the locsed range of elements in
        // the bucket.or both iterators set to end if bucket is empty
        vector<iterator> vec_iters;
        size_t mask;
        size_t max_index;
    };

    //! collection of unique keys, sorted by keys
    template <typename K>
    struct set : tree<K> {};

    //! collection of key-value pairs, sorted by keys, keys are unique
    template <typename K, typename V>
    struct map : tree<pair<K, V>> {};

    //! collection of keys, sorted by keys, duplicates allowed
    template <typename K>
    struct multiset : tree<K> {};

    //! collection of key-value pairs, sorted by keys, duplicates allowed
    template <typename K, typename V>
    struct multimap : tree<pair<K, V>> {};

    //! collection of unique keys, hashed by keys
    template <typename K>
    struct unordered_set : hash<K> {};

    //! collection of key-value pairs, hashed by keys, keys are unique
    template <typename K, typename V>
    struct unordered_map : hash<pair<K, V>> {};

    //! collection of keys, hashed by keys, duplicates allowed
    template <typename K>
    struct unordered_multiset : hash<K> {};

    //! collection of key-value pairs, hashed by keys, duplicates allowed
    template <typename K, typename V>
    struct unordered_multimap : hash<pair<K, V>> {};

    //! double-ended queue
    template <typename T>
    struct deque;  // TODO

    //! adapts a container to provide stack (LIFO data structure)
    template <typename T, typename C = deque<T>>
    struct stack;  // TODO

    //! adapts a container to provide queue (FIFO data structure)
    template <typename T, typename C = deque<T>>
    struct queue;  // TODO

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

    //! wraps callable object of any copy constructible type with specified function call signature
    template <typename F>
    struct function;

    template <typename RetT, typename... ArgT>
    struct alignas(8) function<RetT(ArgT...)> {
        struct impl_t {
            virtual impl_t* copy(void* dst) const = 0;
            virtual impl_t* move(void* dst) noexcept = 0;
            virtual RetT call(ArgT&&...) = 0;
            virtual const type_info& traget_type() const noexcept = 0;
            virtual const void* get() const noexcept = 0;
        };
        void* storage[5 + 16 / sizeof(void*)];
        impl_t* impl;
    };
}