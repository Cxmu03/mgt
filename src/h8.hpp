#include <climits>
#include <cstdint>
#include <string>
#include <utility>

namespace h8
{

using hash_t = std::uintmax_t;

inline auto to_string(hash_t const h) noexcept
{
  return [&]<auto ...I>(std::index_sequence<I...>) noexcept
  {
    char const a[]{char(h >> I * CHAR_BIT)...};

    return std::string(a);
  }(std::make_index_sequence<sizeof(hash_t)>());
}

constexpr auto hash(char const* const s, std::size_t const N) noexcept
{
  return [&]<auto ...I>(std::index_sequence<I...>) noexcept
  {
    return ((hash_t(I < N ? s[I] : 0) << I * CHAR_BIT) | ...);
  }(std::make_index_sequence<sizeof(hash_t)>());
}

template <std::size_t N>
constexpr auto hash(char const(&s)[N]) noexcept
{
  return hash(s, N - 1);
}

constexpr auto hash(std::string_view const& s) noexcept
{
  return hash(s.data(), s.size());
}

namespace literals
{

constexpr hash_t operator"" _h8(char const* const s,
  std::size_t const N) noexcept
{
  return hash(s, N);
}
} // namespace literals
} // namespace h8

