#pragma once
#include <array>

namespace duc::ex {
    /*
template<size_t _size>
class sstring {
public:
    char buffer[_size];

public:
    constexpr size_t size() const noexcept { return _size; }

    template<size_t otherSize>
    char* operator+(const sstring<otherSize> &other) {
        char* newString = new char[this->size() + other.size() - 1] {};

        for (size_t i = 0; i < this->size(); i++) {
            newString[i] = this->buffer[i];
        }
        for (size_t i = 0; i < other.size(); i++) {
            newString[(this->size() - 1) + i] = other.buffer[i];
        }

        return newString;
    }
    template<size_t otherSize>
    char* operator+(sstring<otherSize> &&other) {
        char* newString = new char[this->size() + other.size()];

        // Make copy
        newString[0] = this->buffer;
        newString[this->size()] = other.buffer;

        return newString;
    }
    template<size_t otherSize>
    char* operator+(const char *other) {
        size_t j = 0;
        for (; other[j] != '\0'; j++);

        char* newString = new char[this->size() + j - 1] {};

        for (size_t i = 0; i < this->size(); i++) {
            newString[i] = this->buffer[i];
        }
        for (size_t i = 0; i < j; i++) {
            newString[(this->size() - 1) + i] = other.buffer[i];
        }

        return newString;
    }

    #ifdef _STRING_
    operator std::string() {
        return this->buffer._Elems;
    }
    #endif // STRING

    #ifdef _IOSTREAM_
    friend std::ostream &operator<<(std::ostream& os, const sstring& str) {
        return os << str.buffer._Elems;
    }
    #endif // _IOSTREAM_


};
*/
    template<size_t _size>
    class sstring { // fixed size array of values
    public:
        char buffer[_size + 1] = {};

        using value_type = char;
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using pointer = char*;
        using const_pointer = const char*;
        using reference = char&;
        using const_reference = const char&;

        using iterator = std::_Array_iterator<char, _size + 1>;
        using const_iterator = std::_Array_const_iterator<char, _size + 1>;

        using reverse_iterator = _STD reverse_iterator<iterator>;
        using const_reverse_iterator = _STD reverse_iterator<const_iterator>;

        _CONSTEXPR20 void fill(const char& _Value) {
            _STD fill_n(buffer, _size + 1, _Value);
        }

        _CONSTEXPR20 void swap(sstring& _Other) noexcept(std::_Is_nothrow_swappable<char>::value) {
            std::_Swap_ranges_unchecked(buffer, buffer + _size + 1, _Other.buffer);
        }

        _NODISCARD _CONSTEXPR17 iterator begin() noexcept {
            return iterator(buffer, 0);
        }

        _NODISCARD _CONSTEXPR17 const_iterator begin() const noexcept {
            return const_iterator(buffer, 0);
        }

        _NODISCARD _CONSTEXPR17 iterator end() noexcept {
            return iterator(buffer, _size + 1);
        }

        _NODISCARD _CONSTEXPR17 const_iterator end() const noexcept {
            return const_iterator(buffer, _size + 1);
        }

        _NODISCARD _CONSTEXPR17 reverse_iterator rbegin() noexcept {
            return reverse_iterator(end());
        }

        _NODISCARD _CONSTEXPR17 const_reverse_iterator rbegin() const noexcept {
            return const_reverse_iterator(end());
        }

        _NODISCARD _CONSTEXPR17 reverse_iterator rend() noexcept {
            return reverse_iterator(begin());
        }

        _NODISCARD _CONSTEXPR17 const_reverse_iterator rend() const noexcept {
            return const_reverse_iterator(begin());
        }

        _NODISCARD _CONSTEXPR17 const_iterator cbegin() const noexcept {
            return begin();
        }

        _NODISCARD _CONSTEXPR17 const_iterator cend() const noexcept {
            return end();
        }

        _NODISCARD _CONSTEXPR17 const_reverse_iterator crbegin() const noexcept {
            return rbegin();
        }

        _NODISCARD _CONSTEXPR17 const_reverse_iterator crend() const noexcept {
            return rend();
        }

        _CONSTEXPR17 char* _Unchecked_begin() noexcept {
            return buffer;
        }

        _CONSTEXPR17 const char* _Unchecked_begin() const noexcept {
            return buffer;
        }

        _CONSTEXPR17 char* _Unchecked_end() noexcept {
            return buffer + _size + 1;
        }

        _CONSTEXPR17 const char* _Unchecked_end() const noexcept {
            return buffer + _size + 1;
        }

        _NODISCARD constexpr size_type size() const noexcept {
            return _size + 1;
        }

        _NODISCARD constexpr size_type max_size() const noexcept {
            return _size + 1;
        }

        _NODISCARD_EMPTY_ARRAY_MEMBER constexpr bool empty() const noexcept {
            return false;
        }

        _NODISCARD _CONSTEXPR17 reference at(size_type _Pos) {
            if (_size + 1 <= _Pos) {
                _Xran();
            }

            return buffer[_Pos];
        }

        _NODISCARD constexpr const_reference at(size_type _Pos) const {
            if (_size + 1 <= _Pos) {
                _Xran();
            }

            return buffer[_Pos];
        }

        _NODISCARD _CONSTEXPR17 reference operator[](_In_range_(0, _size) size_type _Pos) noexcept /* strengthened */ {
            #if _CONTAINER_DEBUG_LEVEL > 0
            _STL_VERIFY(_Pos < _size + 1, "array subscript out of range");
            #endif // _CONTAINER_DEBUG_LEVEL > 0

            return buffer[_Pos];
        }

        _NODISCARD constexpr const_reference operator[](_In_range_(0, _size) size_type _Pos) const noexcept
            /* strengthened */ {
            #if _CONTAINER_DEBUG_LEVEL > 0
            _STL_VERIFY(_Pos < _size + 1, "array subscript out of range");
            #endif // _CONTAINER_DEBUG_LEVEL > 0

            return buffer[_Pos];
        }

        _NODISCARD _CONSTEXPR17 reference front() noexcept /* strengthened */ {
            return buffer[0];
        }

        _NODISCARD constexpr const_reference front() const noexcept /* strengthened */ {
            return buffer[0];
        }

        _NODISCARD _CONSTEXPR17 reference back() noexcept /* strengthened */ {
            return buffer[_size];
        }

        _NODISCARD constexpr const_reference back() const noexcept /* strengthened */ {
            return buffer[_size];
        }

        _NODISCARD _CONSTEXPR17 char* data() noexcept {
            return buffer;
        }

        _NODISCARD _CONSTEXPR17 const char* data() const noexcept {
            return buffer;
        }

        [[noreturn]] void _Xran() const {
            std::_Xout_of_range("invalid array<T, N> subscript");
        }

        #ifdef _IOSTREAM_
        friend std::ostream &operator<<(std::ostream& os, const sstring& str) {
            return os << str.buffer;
        }
        #endif // _IOSTREAM_
    };


    template <>
    class sstring<0> {
    public:
        char buffer[1];

    public:
        using value_type = char;
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using pointer = char*;
        using const_pointer = const char*;
        using reference = char&;
        using const_reference = const char&;

        using iterator = std::_Array_iterator<char, 0>;
        using const_iterator = std::_Array_const_iterator<char, 0>;

        using reverse_iterator = _STD reverse_iterator<iterator>;
        using const_reverse_iterator = _STD reverse_iterator<const_iterator>;

        _CONSTEXPR20 void fill(const char&) {}

        _CONSTEXPR20 void swap(sstring&) noexcept {}

        _NODISCARD _CONSTEXPR17 iterator begin() noexcept {
            return iterator{};
        }

        _NODISCARD _CONSTEXPR17 const_iterator begin() const noexcept {
            return const_iterator{};
        }

        _NODISCARD _CONSTEXPR17 iterator end() noexcept {
            return iterator{};
        }

        _NODISCARD _CONSTEXPR17 const_iterator end() const noexcept {
            return const_iterator{};
        }

        _NODISCARD _CONSTEXPR17 reverse_iterator rbegin() noexcept {
            return reverse_iterator(end());
        }

        _NODISCARD _CONSTEXPR17 const_reverse_iterator rbegin() const noexcept {
            return const_reverse_iterator(end());
        }

        _NODISCARD _CONSTEXPR17 reverse_iterator rend() noexcept {
            return reverse_iterator(begin());
        }

        _NODISCARD _CONSTEXPR17 const_reverse_iterator rend() const noexcept {
            return const_reverse_iterator(begin());
        }

        _NODISCARD _CONSTEXPR17 const_iterator cbegin() const noexcept {
            return begin();
        }

        _NODISCARD _CONSTEXPR17 const_iterator cend() const noexcept {
            return end();
        }

        _NODISCARD _CONSTEXPR17 const_reverse_iterator crbegin() const noexcept {
            return rbegin();
        }

        _NODISCARD _CONSTEXPR17 const_reverse_iterator crend() const noexcept {
            return rend();
        }

        _CONSTEXPR17 char* _Unchecked_begin() noexcept {
            return nullptr;
        }

        _CONSTEXPR17 const char* _Unchecked_begin() const noexcept {
            return nullptr;
        }

        _CONSTEXPR17 char* _Unchecked_end() noexcept {
            return nullptr;
        }

        _CONSTEXPR17 const char* _Unchecked_end() const noexcept {
            return nullptr;
        }

        _NODISCARD constexpr size_type size() const noexcept {
            return 0;
        }

        _NODISCARD constexpr size_type max_size() const noexcept {
            return 0;
        }

        _NODISCARD_EMPTY_ARRAY_MEMBER constexpr bool empty() const noexcept {
            return true;
        }

        [[noreturn]] reference at(size_type) {
            _Xran();
        }

        [[noreturn]] const_reference at(size_type) const {
            _Xran();
        }

        _NODISCARD reference operator[](size_type) noexcept /* strengthened */ {
            #if _CONTAINER_DEBUG_LEVEL > 0
            _STL_REPORT_ERROR("array subscript out of range");
            #endif // _CONTAINER_DEBUG_LEVEL > 0

            return *data();
        }

        _NODISCARD const_reference operator[](size_type) const noexcept /* strengthened */ {
            #if _CONTAINER_DEBUG_LEVEL > 0
            _STL_REPORT_ERROR("array subscript out of range");
            #endif // _CONTAINER_DEBUG_LEVEL > 0

            return *data();
        }

        _NODISCARD reference front() noexcept /* strengthened */ {
            #if _CONTAINER_DEBUG_LEVEL > 0
            _STL_REPORT_ERROR("array<T, 0>::front() invalid");
            #endif // _CONTAINER_DEBUG_LEVEL > 0

            return *data();
        }

        _NODISCARD const_reference front() const noexcept /* strengthened */ {
            #if _CONTAINER_DEBUG_LEVEL > 0
            _STL_REPORT_ERROR("array<T, 0>::front() invalid");
            #endif // _CONTAINER_DEBUG_LEVEL > 0

            return *data();
        }

        _NODISCARD reference back() noexcept /* strengthened */ {
            #if _CONTAINER_DEBUG_LEVEL > 0
            _STL_REPORT_ERROR("array<T, 0>::back() invalid");
            #endif // _CONTAINER_DEBUG_LEVEL > 0

            return *data();
        }

        _NODISCARD const_reference back() const noexcept /* strengthened */ {
            #if _CONTAINER_DEBUG_LEVEL > 0
            _STL_REPORT_ERROR("array<T, 0>::back() invalid");
            #endif // _CONTAINER_DEBUG_LEVEL > 0

            return *data();
        }

        _NODISCARD _CONSTEXPR17 char* data() noexcept {
            return nullptr;
        }

        _NODISCARD _CONSTEXPR17 const char* data() const noexcept {
            return nullptr;
        }

        [[noreturn]] void _Xran() const {
            std::_Xout_of_range("invalid array<T, 0> subscript");
        }
    };
}

