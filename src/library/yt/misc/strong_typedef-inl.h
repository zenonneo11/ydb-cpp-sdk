#ifndef STRONG_TYPEDEF_INL_H_
#error "Direct inclusion of this file is not allowed, include strong_typedef.h"
// For the sake of sane code completion.
#include "strong_typedef.h"
#endif

#include <ydb-cpp-sdk/util/stream/output.h>
#include <ydb-cpp-sdk/util/str_stl.h>

#include "wrapper_traits.h"

#include <string_view>

#include <functional>

namespace NYT {

////////////////////////////////////////////////////////////////////////////////

template <class T, class TTag>
constexpr TStrongTypedef<T, TTag>::TStrongTypedef()
    requires std::is_default_constructible_v<T>
    : Underlying_{}
{ }

template <class T, class TTag>
constexpr TStrongTypedef<T, TTag>::TStrongTypedef(const T& underlying)
    requires std::is_copy_constructible_v<T>
    : Underlying_(underlying)
{ }

template <class T, class TTag>
constexpr TStrongTypedef<T, TTag>::TStrongTypedef(T&& underlying)
    requires std::is_move_constructible_v<T>
    : Underlying_(std::move(underlying))
{ }

template <class T, class TTag>
constexpr TStrongTypedef<T, TTag>::operator const T&() const
{
    return Underlying_;
}

template <class T, class TTag>
constexpr TStrongTypedef<T, TTag>::operator T&()
{
    return Underlying_;
}

template <class T, class TTag>
constexpr T& TStrongTypedef<T, TTag>::Underlying() &
{
    return Underlying_;
}

template <class T, class TTag>
constexpr const T& TStrongTypedef<T, TTag>::Underlying() const&
{
    return Underlying_;
}

template <class T, class TTag>
constexpr T&& TStrongTypedef<T, TTag>::Underlying() &&
{
    return std::move(Underlying_);
}

#define XX(op, defaultValue) \
    template <class T, class TTag> \
    constexpr auto TStrongTypedef<T, TTag>::operator op(const TStrongTypedef& rhs) const \
        noexcept(noexcept(Underlying_ op rhs.Underlying_)) \
            requires requires (T lhs, T rhs) {lhs op rhs; } \
    { \
        if constexpr (std::same_as<T, void>) { \
            return defaultValue; \
        } \
        return Underlying_ op rhs.Underlying_; \
    }

XX(<, false)
XX(>, false)
XX(<=, true)
XX(>=, true)
XX(==, true)
XX(!=, false)
XX(<=>, std::strong_ordering::equal)

#undef XX

template <class T, class TTag>
TStrongTypedef<T, TTag>::operator bool() const
    noexcept(noexcept(static_cast<bool>(Underlying_)))
{
    return static_cast<bool>(Underlying_);
}

////////////////////////////////////////////////////////////////////////////////

template <class T>
struct TStrongTypedefTraits
{
    constexpr static bool IsStrongTypedef = false;
};

template <class T, class TTag>
struct TStrongTypedefTraits<TStrongTypedef<T, TTag>>
{
    constexpr static bool IsStrongTypedef = true;
    using TUnderlying = T;
};

////////////////////////////////////////////////////////////////////////////////

template <class T, class TChar>
    requires CStrongTypedef<T>
bool TryFromStringImpl(const TChar* data, size_t size, T& value)
{
    return TryFromString(data, size, value.Underlying());
}

////////////////////////////////////////////////////////////////////////////////

class TYdbStringBuilderBase;

template <class T, class TTag>
void FormatValue(TYdbStringBuilderBase* builder, const TStrongTypedef<T, TTag>& value, std::string_view format)
    noexcept(noexcept(FormatValue(builder, value.Underlying(), format)))
{
    FormatValue(builder, value.Underlying(), format);
}

////////////////////////////////////////////////////////////////////////////////

template <class T, class TTag>
struct TBasicWrapperTraits<TStrongTypedef<T, TTag>>
{
    static constexpr bool IsTrivialWrapper = false;

    using TUnwrapped = T;

    static constexpr bool HasValue(const TStrongTypedef<T, TTag>&) noexcept
    {
        return true;
    }

    template <class U>
        requires std::same_as<std::remove_cvref_t<U>, TStrongTypedef<T, TTag>>
    static constexpr decltype(auto) Unwrap(U&& wrapper) noexcept
    {
        return std::forward<U>(wrapper).Underlying();
    }
};

////////////////////////////////////////////////////////////////////////////////

} // namespace NYT

namespace std {

////////////////////////////////////////////////////////////////////////////////

template <class T, class TTag>
struct hash<NYT::TStrongTypedef<T, TTag>>
{
    size_t operator()(const NYT::TStrongTypedef<T, TTag>& value) const
    {
        return std::hash<T>()(value.Underlying());
    }
};

////////////////////////////////////////////////////////////////////////////////

} // namespace std

////////////////////////////////////////////////////////////////////////////////

template <class T, class TTag>
struct THash<NYT::TStrongTypedef<T, TTag>>
{
    size_t operator()(const NYT::TStrongTypedef<T, TTag>& value) const
    {
        static constexpr bool IsHashable = requires (T value) {
            { THash<T>()(value) } -> std::same_as<size_t>;
        };

        if constexpr (IsHashable) {
            return THash<T>()(value.Underlying());
        } else {
            return std::hash<T>()(value.Underlying());
        }
    }
};

////////////////////////////////////////////////////////////////////////////////

template <class T, class TTag>
IOutputStream& operator<<(IOutputStream& out, const NYT::TStrongTypedef<T, TTag>& value)
{
    return out << value.Underlying();
}

////////////////////////////////////////////////////////////////////////////////
