#ifndef MRR_HEAP_HXX_
#define MRR_HEAP_HXX_

#include <vector>
#include <functional>

template <typename T, typename Comp = std::less<T> >
class heap
{
public:
  typedef T value_type;
  typedef Comp compare_type;


private:
  std::vector<T> heap_;
  compare_type comp;

public:
  void insert(value_type const&);
  void remove_root();

  value_type root()              { return heap_[0]; }
  value_type root()        const { return heap_[0]; }
  std::size_t const size() const { return heap_.size(); }

private:
  void up_heap();
  void down_heap();
};


template <typename T, typename Comp>
auto heap<T,Comp>::insert(value_type const& value) -> void
{
  heap_.push_back(value);
  up_heap();
}

template <typename T, typename Comp>
auto heap<T,Comp>::remove_root() -> void
{
  value_type value = heap_[0];
  std::swap(heap_[0], heap_[heap_.size()-1]);
  heap_.pop_back();
  down_heap();
}

template <typename T, typename Comp>
auto heap<T,Comp>::up_heap() -> void
{
  std::size_t index = heap_.size() - 1;

  while(index > 0)
  {
    std::size_t parent = (index % 2 == 0) ? (index - 2)/2 : (index - 1)/2;

    if(comp(heap_[parent], heap_[index]))
      break;

    std::swap(heap_[parent], heap_[index]);
    index = parent;
  }
}

template <typename T, typename Comp>
auto heap<T,Comp>::down_heap() -> void
{
  std::size_t index = 0;
  std::size_t child1;
  std::size_t child2;
  std::size_t min_child; // Minimum under the strict order...

  for(;;)
  {
    child1 = 2 * index + 1;
    child2 = 2 * index + 2;

    if(child1 >= heap_.size())
      break;

    min_child = child1;
    if(child2 < heap_.size() && comp(heap_[child2], heap_[child1]))
      min_child = child2;

    if(comp(heap_[index], heap_[min_child]))
      break;

    std::swap(heap_[index], heap_[min_child]);
    index = min_child;
  }
}

#endif // #ifndef MRR_HEAP_HXX_
