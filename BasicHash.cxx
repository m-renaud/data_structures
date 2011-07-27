#include <iostream>
#include <cstdlib>

//template <unsigned SIZE>
class HashTable
{

  std::tuple<unsigned, unsigned> hash(int val)
  {
    int index = val % SIZE;
    int probes = 1;

    while(table[index] != 0)
    {
      ++index;
      if(index == SIZE) index = 0;
      ++probes;
    }
    table[index] = val;

    return std::make_tuple(index, probes);
  }
public:
  enum {SIZE = 25003};
  int table[SIZE];

  HashTable()
  {
    for(unsigned i = 0; i < SIZE; ++i)
    {
      table[i] = 0;
    }
  }

  int insert(int val)
  {
    int index = val % SIZE;
    int probes = 1;

    while(table[index] != 0)
    {
      ++index;
      if(index == SIZE) index = 0;
      ++probes;
    }
    table[index] = val;
    return probes;
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
  HashTable ht;
  int totalProbes = 0;
  srand(50);
  for(int i = 0; i < 10000; ++i)
  {
    totalProbes += ht.insert(rand() + 1);
  }

  std::cout << "Average Probes: " << static_cast<double>(totalProbes)/10000.0 << std::endl;



//  ht.print();
}
