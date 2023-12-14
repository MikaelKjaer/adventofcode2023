// Day 01
#include <execution>

#include "utility/utility.hpp"

namespace
{
  std::string find_char(auto beginIt, auto endIt)
  {
    auto it = std::ranges::find_if(beginIt, endIt, [](const std::string::value_type& val) -> bool
    {
        return std::isdigit(val);
    });
    return { it, it + 1 };
  }

  std::string find_char_or_name(auto beginIt, auto endIt, const std::string& string, bool reversed = false)
  {
    using namespace std::string_literals;
    using namespace std::string_view_literals;
    auto it = std::ranges::find_if(beginIt, endIt, [](const std::string::value_type& val) -> bool
    {
        return std::isdigit(val);
    });

    constexpr static std::array names = { "zero"sv, "one"sv, "two"sv, "three"sv, "four"sv, "five"sv, "six"sv, "seven"sv, "eight"sv, "nine"sv };
    const static std::array digits = { "0"s, "1"s, "2"s, "3"s, "4"s, "5"s, "6"s, "7"s, "8"s, "9"s};
    auto nameIt = names.end();
    std::string::size_type nDistance = std::string::npos;
    if (not reversed)
    {
      for (auto nIt = std::begin(names); nIt != std::end(names); ++nIt)
      {
        const auto found = string.find(*nIt);
        if (found != std::string::npos && found < nDistance)
        {
          nDistance = found;
          nameIt = nIt;
        }
      }
    }
    else
    {
      for (auto nIt = std::begin(names); nIt != std::end(names); ++nIt)
      {
        const auto found = string.rfind(*nIt);
        if (found != std::string::npos and (nDistance == std::string::npos or found > nDistance))
        {
          nDistance = found;
          nameIt = nIt;
        }
      }
    }

    if (it != endIt and nameIt == std::end(names))
    {
      return { it, it + 1 };
    }
    if (it == endIt and nameIt != std::end(names))
    {
      const auto idx = std::distance(std::begin(names), nameIt);
      return digits[idx];
    }

    const auto namesIdx = std::distance(std::begin(names), nameIt);
    if (not reversed)
    {
      auto itIdx = std::distance(beginIt, it);
      if (static_cast<std::string::size_type>(itIdx) <= nDistance)
      {
        return { it, it + 1 };
      }
      return digits[namesIdx];
    }
    const auto itIdx = static_cast<std::string::size_type>(std::abs(std::distance(endIt - 1, it)));
    if (itIdx >= nDistance)
    {
      return { it, it + 1 };
    }
    return digits[namesIdx];
  }

  std::uint32_t part1(const std::vector<std::string>& input)
  {
    std::uint32_t sum = 0;

    std::ranges::for_each(input, [&sum](const std::string &string)
    {
      std::uint32_t firstValue = 0, secondValue = 0;
      const auto firstDigit = find_char(string.begin(), string.end());
      const auto lastDigit = find_char(string.rbegin(), string.rend());
      std::from_chars(firstDigit.data(), firstDigit.data() + 1, firstValue);
      std::from_chars(lastDigit.data(), lastDigit.data() + 1, secondValue);
      firstValue *= 10;
      sum += firstValue;
      sum += secondValue;
    });

    return sum;
  }

  std::uint32_t part2(const std::vector<std::string>& input)
  {
    std::uint32_t sum = 0;

    std::ranges::for_each(input, [&sum](const std::string &string)
    {
      std::uint32_t firstValue = 0, secondValue = 0;
      const auto firstDigit = find_char_or_name(string.begin(), string.end(), string);
      const auto lastDigit = find_char_or_name(string.rbegin(), string.rend(), string, true);
      std::from_chars(firstDigit.data(), firstDigit.data() + 1, firstValue);
      std::from_chars(lastDigit.data(), lastDigit.data() + 1, secondValue);
      firstValue *= 10;
      sum += firstValue;
      sum += secondValue;
    });

    return sum;
  }
}

int main(int, char**)
{
  using namespace std::string_literals;
  using namespace std::string_view_literals;
  try
  {
    const std::vector<std::string> input = utility::read_file(std::filesystem::current_path() / "../input/day01.txt"sv);
    fmt::print(FMT_STRING("Part 1 sum: {0}\n"), part1(input));
    fmt::print(FMT_STRING("Part 2 sum: {0}\n"), part2(input));
  }
  catch(...)
  {
    return -1;
  }
  return 0;
}