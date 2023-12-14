// Day 05

#include "utility/utility.hpp"

using namespace std::string_literals;
using namespace std::string_view_literals;

namespace
{
  struct map_value
  {
    std::size_t destination;
    std::size_t length;
  };
  using range_map_t = std::map<std::size_t, map_value>;
  using range_map_ref_t = std::reference_wrapper<range_map_t>;

  std::vector<std::size_t> parse_seeds(const std::vector<std::string>& seeds_txt)
  {
    std::vector<std::string> seeds_strings;
    for (const auto& line : seeds_txt)
    {
      for (const auto& word : std::views::split(line, " "s))
      {
        std::string s(word.begin(), word.end());
        utility::trim(s);
        seeds_strings.push_back(s);
      }
    }

    std::vector<std::size_t> seeds;
    for (const auto& seed_string : seeds_strings)
    {
      std::size_t seed;
      std::from_chars(seed_string.data(), seed_string.data() + seed_string.size(), seed);
      seeds.push_back(seed);
    }
    return seeds;
  }

  range_map_t parse_map(const std::vector<std::string>& maps_txt)
  {
    
  }

  std::size_t part1(const std::vector<std::size_t>& seeds, std::vector<range_map_ref_t>& map_sequence)
  {
    std::size_t value = std::numeric_limits<std::size_t>::max();
    auto part1_search = [&map_sequence](std::size_t input) -> std::size_t
    {
      for (auto map_ref : map_sequence)
      {
        const auto equal_range = map_ref.get().equal_range(input);
        const auto lower_iterator = equal_range.first;
        if (lower_iterator->first >= input and lower_iterator->first + lower_iterator->second.length <= input)
        {
          input = lower_iterator->second.destination + (lower_iterator->first - input);
        }
        const auto upper_iterator = equal_range.second;
        if (upper_iterator->first >= input and upper_iterator->first + upper_iterator->second.length <= input)
        {
          input = upper_iterator->second.destination + (upper_iterator->first - input);
        }
      }
      return input;
    };

    for (const auto& seed : seeds)
    {
      const auto result = part1_search(seed);
      if (result < value)
      {
        value = result;
      }
    }

    return value;
  }

}

int main(int, char**)
{
  try
  {
    const std::vector<std::string> seeds_txt = utility::read_file(std::filesystem::current_path() / "../input/Day05_seeds.txt"sv);
    const std::vector<std::string> seed_to_soil_txt = utility::read_file(std::filesystem::current_path() / "../input/Day05_seed_to_soil.txt"sv);
    const std::vector<std::string> soil_to_fertilizer_txt = utility::read_file(std::filesystem::current_path() / "../input/Day05_to_fertilizer.txt"sv);
    const std::vector<std::string> fertilizer_to_water_txt = utility::read_file(std::filesystem::current_path() / "../input/Day05_fertilizer_to_water.txt"sv);
    const std::vector<std::string> water_to_light_txt = utility::read_file(std::filesystem::current_path() / "../input/Day05_water_to_light.txt"sv);
    const std::vector<std::string> light_to_temperature_txt = utility::read_file(std::filesystem::current_path() / "../input/Day05_light_to_temperature.txt"sv);
    const std::vector<std::string> temperature_to_humidity_txt = utility::read_file(std::filesystem::current_path() / "../input/Day05_temperature_to_humidity.txt"sv);
    const std::vector<std::string> humidity_to_location_txt = utility::read_file(std::filesystem::current_path() / "../input/Day05_humidity_to_location.txt"sv);
    auto seeds = parse_seeds(seeds_txt);
    auto seed_to_soil_map = parse_map(seed_to_soil_txt);
    auto soil_to_fertilizer_map = parse_map(soil_to_fertilizer_txt);
    auto fertilizer_to_water_map = parse_map(fertilizer_to_water_txt);
    auto water_to_light_map = parse_map(water_to_light_txt);
    auto light_to_temperature_map = parse_map(light_to_temperature_txt);
    auto temperature_to_humidity_map = parse_map(temperature_to_humidity_txt);
    auto humidity_to_location_map = parse_map(humidity_to_location_txt);
    std::vector<range_map_ref_t> map_sequence{ seed_to_soil_map, soil_to_fertilizer_map, fertilizer_to_water_map, water_to_light_map, light_to_temperature_map, temperature_to_humidity_map, humidity_to_location_map };

    fmt::print(FMT_STRING("Part 1: {0}\n"), part1(seeds, map_sequence));
  }
  catch(...)
  {
    return -1;
  }
  return 0;
}