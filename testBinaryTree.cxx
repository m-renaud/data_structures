#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <sstream>


#include "BinaryTree.hxx"

template <typename T>
std::string numericToString(T val)
{
  std::string s;
  std::stringstream out;
  out << val;
  s = out.str();
  return s;
}


int main()
{
  BinaryTree<int, std::greater<int> > t1;

  srand(time(NULL));
  unsigned depthSum = 0;
  for (int i = 0; i < 50; ++i)
  {
    for(int j = 0; j < 50; ++j)
    {
      t1.insert(rand() % 200);
    }
    depthSum += t1.depth();
    t1.print("Tree " + numericToString(i) + ": ");
    t1.clear();
  }
  std::cout << std::endl;
  std::cout << "Expected Avg depth: " << log2(50) << std::endl;
  std::cout << "Actual Avg depth: " << static_cast<double>(depthSum)/50.0 << std::endl;

}
