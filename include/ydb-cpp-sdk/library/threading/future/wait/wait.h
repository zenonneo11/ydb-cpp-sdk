#pragma once

#include <span>

#include <ydb-cpp-sdk/library/threading/future/core/future.h>

#include "wait_group.h"

namespace NThreading {
    namespace NImpl {
        template <class TContainer>
        using EnableGenericWait = std::enable_if_t<
            !std::is_convertible_v<TContainer, std::span<const TFuture<void>>>,
            TFuture<void>>;
    }
    // waits for all futures
    [[nodiscard]] TFuture<void> WaitAll(const TFuture<void>& f1);
    [[nodiscard]] TFuture<void> WaitAll(const TFuture<void>& f1, const TFuture<void>& f2);
    [[nodiscard]] TFuture<void> WaitAll(std::span<const TFuture<void>> futures);
    template <typename TContainer>
    [[nodiscard]] NImpl::EnableGenericWait<TContainer> WaitAll(const TContainer& futures);

    // waits for the first exception or for all futures
    [[nodiscard]] TFuture<void> WaitExceptionOrAll(const TFuture<void>& f1);
    [[nodiscard]] TFuture<void> WaitExceptionOrAll(const TFuture<void>& f1, const TFuture<void>& f2);
    [[nodiscard]] TFuture<void> WaitExceptionOrAll(std::span<const TFuture<void>> futures);
    template <typename TContainer>
    [[nodiscard]] NImpl::EnableGenericWait<TContainer> WaitExceptionOrAll(const TContainer& futures);

    // waits for any future
    [[nodiscard]] TFuture<void> WaitAny(const TFuture<void>& f1);
    [[nodiscard]] TFuture<void> WaitAny(const TFuture<void>& f1, const TFuture<void>& f2);
    [[nodiscard]] TFuture<void> WaitAny(std::span<const TFuture<void>> futures);
    template <typename TContainer>
    [[nodiscard]] NImpl::EnableGenericWait<TContainer> WaitAny(const TContainer& futures);
}

#define INCLUDE_FUTURE_INL_H
#include "wait-inl.h"
#undef INCLUDE_FUTURE_INL_H
