// Day 03

#include "utility/utility.hpp"

using namespace std::string_literals;
using namespace std::string_view_literals;

template<>
struct std::hash<std::pair<std::size_t, std::size_t>>
{
  std::uint64_t operator()(const std::pair<std::size_t, std::size_t>& value) const noexcept
  {
    // computes the hash of an employee using a variant
    // of the Fowler-Noll-Vo hash function
    constexpr std::uint64_t prime{0x100000001B3};
    std::uint64_t result{0xcbf29ce484222325};

    result = (result * prime) ^ std::hash<std::size_t>()(value.first);
    result *= result ^ std::hash<std::size_t>()(value.second);

    return result;
  }
};

namespace
{
  std::pair<std::uint32_t, std::size_t> find_number(std::size_t j, const std::string& line)
  {
    std::uint32_t number = 0;
    std::size_t k = j;
    while(k < line.size() and std::isdigit(line[k]))
    {
      ++k;
    } //Count up until the end is found
    std::from_chars(&line[j], line.data() + k, number);
    return { number, k - j };
  }

  bool check_line(const std::string& line, const std::size_t numberBegin, const std::size_t numberEnd)
  {
    const auto start = (static_cast<std::ptrdiff_t>(numberBegin) - 1 >= 0) ? numberBegin - 1 : 0;
    const auto end = (numberEnd + 1 < line.size()) ? numberEnd + 1 : numberEnd;
    const std::string_view view{ &line[start], end - start };
    for (const auto& c : view)
    {
      if (c != '.' and !std::isdigit(c))
      {
        return true;
      }
    }
    return false;
  }

  bool is_part_number(std::size_t numberBegin, std::size_t numberEnd, std::size_t line_number, const std::vector<std::string>& input)
  {
    bool result = false;
    const auto& line = input[line_number];
    result |= check_line(line, numberBegin, numberEnd);

    //maybe check above the number
    if (static_cast<std::ptrdiff_t>(line_number) - 1 >= 0)
    {
      const auto& top_line = input[line_number - 1];
      result |= check_line(top_line, numberBegin, numberEnd);
    }

    //maybe check beneath the number
    if (line_number + 1 < input.size())
    {
      const auto& bottom_line = input[line_number + 1];
      result |= check_line(bottom_line, numberBegin, numberEnd);
    }
    return result;
  }
	
  std::uint32_t part1(const std::vector<std::string>& input)
  {
    std::uint32_t sum = 0;
    for (std::size_t i = 0; i < input.size(); ++i)
    {
      const auto& line = input[i];
      for (std::size_t j = 0; j < line.size(); ++j)
      {
        if (std::isdigit(line[j]))
        {
          const auto [number, size_of_number] = find_number(j, line);
          if (is_part_number(j, j + size_of_number, i, input))
          {
            sum += number;
          }
          j += size_of_number;
        }
      }
    }
    return sum;
  }

  std::tuple<bool, std::size_t> check_line_for_gear(const std::string& line, const std::size_t numberBegin, const std::size_t numberEnd)
  {
    const auto start = (static_cast<std::ptrdiff_t>(numberBegin) - 1 >= 0) ? numberBegin - 1 : 0;
    const auto end = (numberEnd + 1 < line.size()) ? numberEnd + 1 : numberEnd;
    for (std::size_t i = start; i < end; ++i)
    {
      if (line[i] == '*')
      {
        return { true, i };
      }
    }
    return { false, 0 };
  }

  std::tuple<bool, std::size_t, std::size_t> is_gear_number(std::size_t numberBegin, std::size_t numberEnd, std::size_t line_number, const std::vector<std::string>& input)
  {
    std::tuple<bool, std::size_t, std::size_t> result { false, 0, 0};
    const auto& line = input[line_number];
    const auto line_check = check_line_for_gear(line, numberBegin, numberEnd);
    if (std::get<0>(line_check))
    {
      std::get<0>(result) = true;
      std::get<1>(result) = std::get<1>(line_check);
      std::get<2>(result) = line_number;
      return result;
    }

    //maybe check above the number
    if (static_cast<std::ptrdiff_t>(line_number) - 1 >= 0)
    {
      const auto& top_line = input[line_number - 1];
      const auto top_line_result = check_line_for_gear(top_line, numberBegin, numberEnd);
      if (std::get<0>(top_line_result))
      {
        std::get<0>(result) = true;
        std::get<1>(result) = std::get<1>(top_line_result);
        std::get<2>(result) = line_number - 1;
        return result;
      }
    }

    //maybe check beneath the number
    if (line_number + 1 < input.size())
    {
      const auto& bottom_line = input[line_number + 1];
      const auto bottom_line_result = check_line_for_gear(bottom_line, numberBegin, numberEnd);
      if (std::get<0>(bottom_line_result))
      {
        std::get<0>(result) = true;
        std::get<1>(result) = std::get<1>(bottom_line_result);
        std::get<2>(result) = line_number + 1;
        return result;
      }
    }
    //return if we didnt find anything relevant
    return result;
  }

  std::uint32_t part2(const std::vector<std::string>& input)
  {
    std::uint32_t sum = 0;
    std::unordered_map<std::pair<std::size_t, std::size_t>, bool> key_map;
    
    std::unordered_multimap<std::pair<std::size_t, std::size_t>, std::uint32_t> map;
    for (std::size_t i = 0; i < input.size(); ++i)
    {
      const auto& line = input[i];
      for (std::size_t j = 0; j < line.size(); ++j)
      {
        if (std::isdigit(line[j]))
        {
          const auto [number, size_of_number] = find_number(j, line);
          auto [found_gear, gear_number, line_number] = is_gear_number(j, j + size_of_number, i, input);
          if (found_gear)
          {
            key_map.insert( {{ gear_number, line_number }, true });
            map.insert({{ gear_number, line_number }, number });
          }
          j += size_of_number;
        }
      }
    }
    for (const auto& [key, placeholder] : key_map)
    {
      std::vector<std::uint32_t> valid_numbers;
      auto result_range = map.equal_range(key);
      for (auto it = result_range.first; it != result_range.second; ++it)
      {
        valid_numbers.emplace_back(it->second);
      }

      if (valid_numbers.size() == 2)
      {
        sum += (valid_numbers[0] * valid_numbers[1]);
      }
    }
    return sum;
  }
}

int main(int, char**)
{
  try
  {
    const std::vector<std::string> input = utility::read_file(std::filesystem::current_path() / "../input/Day03.txt"sv);

    fmt::print(FMT_STRING("Part 1: {0}\n"), part1(input));
    fmt::print(FMT_STRING("Part 2: {0}\n"), part2(input));
  }
  catch(...)
  {
    return -1;
  }
  return 0;
}