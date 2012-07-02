#include <iostream>
#include <string>
#include <vector>
#include <set>

#include "trie.hxx"


int main()
{
#if 0
  {
    mrr::trie<std::string, int> t_string;
    mrr::trie<std::string, int>::iterator val;

    t_string.insert("abc", 5);

    val = t_string.find("abc");

    if(val != std::end(t_string))
      std::cout << *val << std::endl;
    else
      std::cout << "Not found" << std::endl;
  }

  {
    mrr::trie<std::vector<int>, int> t_vector;
    mrr::trie<std::vector<int>, int>::iterator val;

    std::vector<int> key {1,2,3,4};

    t_vector.insert(key, 8);

    val = t_vector.find(key);

    if(val != std::end(t_vector))
      std::cout << *val << std::endl;
    else
      std::cout << "Not found" << std::endl;
  }

  // Set
  {
    // Set...
    mrr::trie<std::set<int>, int> t_set;
    mrr::trie<std::set<int>, int>::iterator val;

    std::set<int> key {1,4,6,7,8,9};

    t_set.insert(key, 123);

    val = t_set.find(key);

    if(val != std::end(t_set))
      std::cout << *val << std::endl;
    else
      std::cout << "Not found" << std::endl;
  }
#endif

  mrr::trie<std::string, int> t_string;

  t_string.insert(std::make_pair("abc", 5));
  auto i = t_string .find("abc");

  if(i != std::end(t_string))
    std::cout << i->first << ' ' << i->second << std::endl;
  else
    std::cout << "Not found" << std::endl;
    

  return 0;
}
