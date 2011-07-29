#include <iostream>
#include <tuple>

#include <cstdlib>
#include <ctime>

//===========================================================================
// Hash Table Class
//===========================================================================
template <unsigned SIZE, typename T = int>
class HashTable
{
  std::tuple<unsigned, unsigned> hash(T val)
  {
    unsigned index = val % SIZE;
    unsigned probes = 1;

    while(table[index] != 0)
    {
      ++index;
      if(index == SIZE) index = 0;
      ++probes;
    }

    return std::make_tuple(index, probes);
  }

public:
  T table[SIZE];

  // Constructor.
  HashTable()
  {
    for(unsigned i = 0; i < SIZE; ++i)
    {
      table[i] = 0;
    }
  }

  unsigned getTableSize()
  {
    return SIZE;
  }

  unsigned insert(T val)
  {
    std::tuple<unsigned, unsigned> i_p = hash(val);
    table[std::get<0>(i_p)] = val;
    return std::get<1>(i_p);
  }

  void print()
  {
    for(unsigned i = 0; i < SIZE; ++i)
    {
      if(table[i] != 0)
	std::cout << i << ": " << table[i] << std::endl;
    }
  }
};


int main()
{
  HashTable<25003, int> ht;
  unsigned totalProbes = 0;

  srand(time(NULL));
  for(int i = 0; i < 10000; ++i)
  {
    totalProbes += ht.insert(rand() + 1);
  }
  std::cout << "Average Probes: " << static_cast<double>(totalProbes)/10000.0 << std::endl;

//  ht.print();
}
