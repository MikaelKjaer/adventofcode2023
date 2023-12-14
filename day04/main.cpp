// Day 04

#include "utility/utility.hpp"

using namespace std::string_literals;
using namespace std::string_view_literals;

namespace
{
  struct card
  {
    void parse(const std::string& line)
    {
      copies = 1;
      match_count = 0;

      std::vector<std::string> base_split;
      for (const auto& word : std::views::split(line, ": "s))
      {
        std::string s(word.begin(), word.end());
        utility::trim(s);
        base_split.push_back(s);
      }

      std::vector<std::string> line_split;
      for (const auto& word : std::views::split(base_split[1], "| "s))
      {
        std::string s(word.begin(), word.end());
        utility::trim(s);
        line_split.push_back(s);
      }

      std::vector<std::string> winning_split;
      for (const auto& word : std::views::split(line_split[0], " "s))
      {
        std::string s(word.begin(), word.end());
        utility::trim(s);
        winning_split.push_back(s);
      }
      for (const auto& number_string : winning_split)
      {
        std::uint32_t placeholder = 0;
        std::from_chars(number_string.data(), number_string.data() + number_string.size(), placeholder);
        if (placeholder != 0)
        {
          winning_numbers.push_back(placeholder);
        }
      }

      std::vector<std::string> drawn_split;
      for (const auto& word : std::views::split(line_split[1], " "s))
      {
        std::string s(word.begin(), word.end());
        utility::trim(s);
        drawn_split.push_back(s);
      }
      for (const auto& number_string : drawn_split)
      {
        std::uint32_t placeholder = 0;
        std::from_chars(number_string.data(), number_string.data() + number_string.size(), placeholder);
        if (placeholder != 0)
        {
          drawn_numbers.push_back(placeholder);
        }
      }
    }

    std::uint32_t matches()
    {
      std::uint32_t result = 0;
      for (const auto winning : winning_numbers)
      {
        for (const auto drawn : drawn_numbers)
        {
          if (winning == drawn)
          {
            ++match_count;
            if (result == 0)
            {
              result = 1;
            }
            else
            {
              result *= 2;
            }
          }
        }
      }
      return result;
    }

    std::uint32_t id;
    std::vector<std::uint32_t> winning_numbers;
    std::vector<std::uint32_t> drawn_numbers;
    std::size_t match_count;
    std::uint32_t copies;
  };

  std::uint32_t part1(std::vector<card>& cards)
  {
    std::uint32_t sum = 0;

    for (auto& c : cards)
    {
      sum += c.matches();
    }
    return sum;
  }

  std::uint32_t part2(std::vector<card>& cards)
  {
    std::uint32_t sum = 0;

    for (std::size_t i = 0; i < cards.size(); ++i)
    {
      if (i + 1 < cards.size())
      {
        for (std::size_t c = 0; c < cards[i].copies; ++c)
        {
          for (std::size_t j = i + 1; j < i + 1 + cards[i].match_count && j < cards.size(); ++j)
          {
            cards[j].copies++;
          }
        }
      }
    }

    for (const auto& c : cards)
    {
      sum += c.copies;
    }

    return sum;
  }

}

int main(int, char**)
{
  try
  {
    const std::vector<std::string> input = utility::read_file(std::filesystem::current_path() / "../input/Day04.txt"sv);

    std::vector<card> cards;
    cards.reserve(input.size());

    std::uint32_t count = 1;
    for (const auto& line : input)
    {
      card c;
      c.id = count++;
      c.parse(line);
      cards.emplace_back(c);
    }
    fmt::print(FMT_STRING("Part 1: {0}\n"), part1(cards));
    fmt::print(FMT_STRING("Part 2: {0}\n"), part2(cards));
  }
  catch(...)
  {
    return -1;
  }
  return 0;
}