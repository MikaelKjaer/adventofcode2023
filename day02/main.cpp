// Day 02
#include <execution>

#include "utility/utility.hpp"

using namespace std::string_literals;
using namespace std::string_view_literals;

namespace
{
  struct draw
  {
    draw() :
     blues(0),
     reds(0),
     greens(0)
    {}
    draw(const draw&) = default;
    draw(draw&&) = default;
    ~draw() = default;

    draw& operator=(const draw&) = default;
    draw& operator=(draw&&) = default;

    bool is_valid(const std::uint32_t max_blues, const std::uint32_t max_reds, const std::uint32_t max_greens) const
    {
      if (blues > max_blues or reds > max_reds or greens > max_greens)
      {
        return false;
      }
      return true;
    }

    std::uint32_t blues;
    std::uint32_t reds;
    std::uint32_t greens;
  };

  struct game
  {
    constexpr game() = default;
    game(const game&) = default;
    game(game&&) noexcept = default;
    ~game() = default;

    game& operator=(const game&) = default;
    game& operator=(game&&) = default;

    void parse(const std::string& string)
    {
      std::vector<std::string> base_split;
      for (const auto& word : std::views::split(string, ": "s))
      {
        base_split.emplace_back(word.begin(), word.end());
      }

      std::vector<std::string> id_split;
      for (const auto& word : std::views::split(base_split[0], " "s))
      {
        id_split.emplace_back(word.begin(), word.end());
      }
      std::from_chars(id_split[1].data(), id_split[1].data() + id_split[1].size(), id);

      std::vector<std::string> draw_strings;
      for (const auto& draw_string : std::views::split(base_split[1], "; "s))
      {
        draw_strings.emplace_back(draw_string.begin(), draw_string.end());
      }

      for (const auto& draw_string : draw_strings)
      {
        std::vector<std::string> draw_parts;
        for (const auto& draw_part : std::views::split(draw_string, ", "s))
        {
          draw_parts.emplace_back(draw_part.begin(), draw_part.end());
        }

        draw d;
        for (const auto& draw_part : draw_parts)
        {
          std::vector<std::string> parts;
          for (const auto& split_draw_part : std::views::split(draw_part, " "s))
          {
            parts.emplace_back(split_draw_part.begin(), split_draw_part.end());
          }

          if (parts[1] == "blue")
          {
            std::from_chars(parts[0].data(), parts[0].data() + parts[0].size(), d.blues);
          }
          else if (parts[1] == "red")
          {
            std::from_chars(parts[0].data(), parts[0].data() + parts[0].size(), d.reds);
          }
          else if (parts[1] == "green")
          {
            std::from_chars(parts[0].data(), parts[0].data() + parts[0].size(), d.greens);
          }

        }
        draws.push_back(d);
      }
    }

    bool is_valid(const std::uint32_t max_blues, const std::uint32_t max_reds, const std::uint32_t max_greens) const
    {
      bool result = true;
      for (const auto &draw : draws)
      {
        result &= draw.is_valid(max_blues, max_reds, max_greens);
        if (not result)
        {
          break;
        }
      }
      return result;
    }

    std::uint32_t minimum_valid_set() const
    {
      draw d;

      for (const auto& draw : draws)
      {
        if (draw.blues > d.blues)
        {
          d.blues = draw.blues;
        }
        if (draw.reds > d.reds)
        {
          d.reds = draw.reds;
        }
        if (draw.greens > d.greens)
        {
          d.greens = draw.greens;
        }
      }

      return d.reds * d.greens * d.blues;
    }

    std::uint32_t id;
    std::vector<draw> draws;
  };

  std::uint32_t part1(const std::vector<game>& games)
  {
    std::uint32_t sum = 0;
    for (const auto& game : games)
    {
      if (game.is_valid(14, 12, 13))
      {
        sum += game.id;
      }
    }
    return sum;
  }

  std::uint32_t part2(const std::vector<game>& games)
  {
    std::uint32_t sum = 0;
    for (const auto& game : games)
    {
      sum += game.minimum_valid_set();
    }
    return sum;
  }
}

int main(int, char**)
{
  try
  {
    const std::vector<std::string> input = utility::read_file(std::filesystem::current_path() / "../input/day02.txt"sv);

    std::vector<game> games;
    games.reserve(input.size());

    for (const auto& string : input)
    {
      game g;
      g.parse(string);
      games.push_back(g);
    }

    fmt::print(FMT_STRING("Part 1: {0}\n"), part1(games));
    fmt::print(FMT_STRING("Part 2: {0}\n"), part2(games));
  }
  catch(...)
  {
    return -1;
  }
  return 0;
}