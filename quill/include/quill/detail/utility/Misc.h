#pragma once

#include "quill/detail/utility/Attributes.h"
#include <array>
#include <cassert>
#include <cerrno>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace quill
{
namespace detail
{
static constexpr size_t CACHELINE_SIZE{64u};

/**
 * Check if a number is a power of 2
 * @param number the number to check against
 * @return true if the number is power of 2
 *         false otherwise
 */
QUILL_NODISCARD constexpr bool is_pow_of_two(uint64_t number) noexcept
{
  return (number != 0) && ((number & (number - 1)) == 0);
}

/**
 * Constexpr string length
 * @param str
 * @return
 */
QUILL_NODISCARD constexpr size_t strlen(char const* str) { return *str ? 1 + strlen(str + 1) : 0; }

/**
 * Simple wrapper around fwrite, throws on error
 * @param ptr
 * @param size
 * @param count
 * @param stream
 */
void fwrite_fully(void const* ptr, size_t size, size_t count, FILE* stream);

/**
 * Same as strncpy.
 * Compared to normal strncpy :
 * a) It copies only the required bytes and b) always null terminates.
 * @tparam N
 * @param destination
 * @param source
 */
template <size_t N>
void safe_strncpy(std::array<char, N>& destination, char const* source) noexcept
{
  assert(source && "source pointer can not be nullptr");
  size_t const len = std::min(std::strlen(source), N - 1);
  std::memcpy(destination.data(), source, len);
  destination[len] = '\0';
}

} // namespace detail
} // namespace quill