/*
  This program provides general solution to the problem defined below.

  A network card has m session managers. Each session manager can manage up to n sessions.
  Each session is allocated a unique port number. All port numbers should be continous, thus
  given a starting port number p, the range for all possible port numbers should be
  [p, p + m * n).Given a sequence of already occupied port numbers and j, allocate no 
  more than j new port numbers.

  When allocating ports, the following rules need to be honored.

  1.balance the load to different session managers as evenly as possible.
  2.each session manager should contain no more than k sessions (k <= n)
  3.lowest available port should come first in the same session manager
  4.session manager that has available ports with lower port numbers should come first

  Input: m, n, p, k, a vector (unsorted) of already allocated port numbers, j

  Output: no more than j available ports, sorted from low to high

  e.g.

  Input: 3, 10, 0, 10, [0 10], 2
  Output: [1 20]

  Input: 3, 10, 0, 1, [0 10 20], 3
  Output: []

  Note: existing allocated port numbers are only guaranteed to conform to rule #2 due to oversight,
  human error, port deletion etc,etc. The solution should follow required rules regardless

  Requires boost/gtest to build

  Built with gcc 4.8.1:
  g++ ./allocate_ports.cpp --std=c++11 -I/usr/local/boost/boost_1_57_0/include/ -I/usr/local/gtest/gtest/include -L /usr/local/gtest/gtest/lib -lgtest -pthread -o ./allocate_ports

  For use in canada trc
  ./allocate_ports --max-sessions-per-manager=4 [input file pipelined from db] [new session #]

  Build for unittest
  g++ ./allocate_ports.cpp -g -O2 --std=c++0x -D__UNITTEST__ -I/opt/libc++/boost/1.64.0/include -I/opt/libstdc++/gtest/1.8.0/include -L /opt/libc++-sanitizer/gtest/1.8.0/lib -lgtest -pthread -fPIC -o ./allocate_ports

  algorithm overview:
  1. Initialize a array of Port_Tile of size m, each representing a session manager and has the following info:
   * starting port number for this session manager
   * how many slots are already taken (with boost::dynamic_bitset, std::bitset can only be defined at compile time)
  2. Push initialized Port_Tile array into a min heap, which will always put the tile with the least used slots and the
     lowest port number on top, which is out candidate for allocateing port
  3. pop from min heap, get the next avaible slot, insert it to results, and push it again since the heap has been updated
  4. repeat #3 until we get enough slots OR we don't have have any more available slots
  time complexity should be mlog(m) for building the heap and jlog(m) for popping and pushing to heap j times
  
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <assert.h>
#include <string.h>
#include <getopt.h>

#include <boost/dynamic_bitset.hpp>

#ifdef __UNITTEST__
#include <gtest/gtest.h>
#endif

using namespace std;

 /*
 these default values are that of current canada trc
 except for max_sessions_per_manager
 max_sessions_per_manager should be set to 4 or 5
 when running in canada trc
 */
constexpr uint32_t default_num_of_managers = 22;
constexpr uint32_t default_capacity_per_manager = 16;
constexpr uint32_t default_start_port_number = 2000;
constexpr uint32_t default_max_sessions_per_manager = default_capacity_per_manager;

struct Options
{
  uint32_t num_of_managers;
  uint32_t capacity_per_manager;
  uint32_t start_port_number;
  uint32_t max_sessions_per_manager;
};

void usage(const char * name)
{

  cout << "Usage: " << basename(name) << "  [options] [file] [num of ports requested]" << endl
       << "  --start-port-number=<port>" << endl
       << "    starting port of allocation. default is " << default_start_port_number << endl
       << "  --num-of-managers=<num>" << endl
       << "    number of session managers available. default is " << default_max_sessions_per_manager << endl
       << "  --capacity-per-manager=<num>" << endl
       << "    number of sessions each manager can handle. default is " << default_capacity_per_manager << endl
       << "  --max-sessions-per-manager=<num>" << endl
       << "    max number of sessions allowed to be allocated for each manager. " << endl
       << "    should be less than or equal to capacity-per-manager. default is " << default_max_sessions_per_manager << endl
       << "  --help " << endl
       << "    print this message" << endl;

}

struct Ports_Tile
{
  Ports_Tile (uint16_t width, uint32_t start)
    : buckets(width),
      start(start)
  {}

  boost::dynamic_bitset<> buckets;
  uint32_t start;
};

auto  allocate_ports(const vector<uint32_t> & current_ports, int num, const Options & options) 
  -> typename remove_const<remove_reference<decltype(current_ports)>::type>::type
{
  using return_type = typename remove_const<remove_reference<decltype(current_ports)>::type>::type;
  return_type res;

  auto compare = [](const Ports_Tile & lhs, const Ports_Tile & rhs) -> bool
  {
    // if same slots are taken, lower port first
    if (lhs.buckets.count() == rhs.buckets.count())
    {
      return lhs.start > rhs.start;
    }
    // port tile with less ports taken first
    return lhs.buckets.count() > rhs.buckets.count();
  };
  priority_queue<Ports_Tile, vector<Ports_Tile>, decltype(compare)> pq(compare);

  vector<Ports_Tile> tiles;
  for (decltype(options.num_of_managers) i = 0; i < options.num_of_managers; ++i)
  {
    tiles.emplace_back(options.capacity_per_manager, options.start_port_number + i * options.capacity_per_manager);
  }

  const auto end_port_number = options.start_port_number + options.capacity_per_manager * options.num_of_managers;
  for (auto port_num : current_ports)
  {
    if (port_num >= options.start_port_number && port_num < end_port_number)
    {
      auto offset = port_num - options.start_port_number;
      auto pos = make_pair(offset / options.capacity_per_manager, offset % options.capacity_per_manager);
      tiles[pos.first].buckets.set(pos.second);
    }
  }

  for (const auto & tile : tiles) pq.push(tile);

  assert(pq.size() == options.num_of_managers);

  while (num-- > 0 && !pq.empty())
  {
    if (pq.top().buckets.count() >= options.max_sessions_per_manager) break;
    auto pt = pq.top();
    pq.pop();

    size_t i = 0;
    while (pt.buckets.test(i)) i++;
    pt.buckets.set(i);
    res.emplace_back(pt.start + i);
    pq.push(pt);
  }

  sort(res.begin(), res.end());
  return res;
}

#ifdef __UNITTEST__
// unit tests
TEST (Allocate_Ports, basic)
{
  EXPECT_EQ(allocate_ports({0, 10}, 2, {3,10,0,10}), (vector<uint32_t>{1,20}));
  EXPECT_EQ(allocate_ports({0, 10, 20}, 3, {3,10,0,1}), (vector<uint32_t>{}));
  EXPECT_EQ(allocate_ports({0, 7, 10, 20}, 3, {3,10,0,3}), (vector<uint32_t>{1,11,21}));
  EXPECT_EQ(allocate_ports({}, 4, {3,10,0,3}), (vector<uint32_t>{0, 1, 10, 20}));
}
#endif

int main(int argc, char * argv[])
{

#ifdef __UNITTEST__

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

#else

  Options input_options {
    default_num_of_managers, 
    default_capacity_per_manager,
    default_start_port_number,
    default_max_sessions_per_manager
  };

  while (1)
  {
    static struct option long_options[] =
    {
      {"start-port-number", required_argument, 0, 's'},
      {"num-of-managers", required_argument, 0, 'n'},
      {"capacity-per-manager", required_argument, 0, 'c'},
      {"max-sessions-per-manager", required_argument, 0, 'm'},
      {"help", no_argument, 0, 'h'},
      {0,0,0,0}
    };
    int optional_index = 0;
    int c = getopt_long(argc, argv, "s:n:c:m:h", long_options, &optional_index);
    if (-1 == c)
      break;
    switch (c)
    {
      case 's':
        input_options.start_port_number = atoi(optarg);
        break;
      case 'n':
        input_options.num_of_managers = atoi(optarg);
        break;
      case 'c':
        input_options.capacity_per_manager = atoi(optarg);
        break;
      case 'm':
        input_options.max_sessions_per_manager = atoi(optarg);
        break;
      case 'h':
        usage(argv[0]);
        return 0;
      case '?':
        return -1;
      default:
        abort();
    }
  }

  if (argc - optind < 2)
  {
    cout << "Not enough parameters. Try \"" << basename(argv[0]) << " --help\"" << endl;
    return -1;
  }

  ifstream input(argv[optind++]);
  vector<uint32_t> current_ports;
  if (input.is_open())
  {
    std::string line;
    while (getline(input, line))
    {
      current_ports.emplace_back(atoi(line.c_str()));
    }
  }

  auto requested_num = atoi(argv[optind]);
  auto new_ports = allocate_ports(current_ports, requested_num, input_options);

  cout << to_string(new_ports.size()) << " ports allocated" << endl;
  for (auto i : new_ports)
  {
    cout << i << endl;
  }
  return new_ports.size() == (size_t)requested_num ? 0 : -1;
#endif
}
