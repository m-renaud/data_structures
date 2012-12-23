#ifndef MRR_HEAP_HXX_
#define MRR_HEAP_HXX_

#include <vector>
#include <functional>

//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace mrr {

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename T, typename Comp = std::less<T>>
class heap
{
public:
  using value_type = T;
  using compare_type = Comp;
  using const_reference = value_type const&;
  using size_type = std::size_t;

private:
  std::vector<T> heap_;
  compare_type comp;

public:
  void insert(value_type const&);
  void remove_root();

  const_reference root()  const { return heap_.front(); }
  bool            empty() const { return heap_.size() == 0; }
  size_type       size()  const { return heap_.size(); }

private:
  void up_heap();
  void down_heap();

}; // class heap


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
  std::swap(heap_.front(), heap_.back());
  heap_.pop_back();
  down_heap();
}

template <typename T, typename Comp>
auto heap<T,Comp>::up_heap() -> void
{
  for(size_type index = heap_.size() - 1; index > 0;)
  {
    size_type parent = ((index + 1)/2) - 1;

    if(comp(heap_[parent], heap_[index]))
      break;

    std::swap(heap_[parent], heap_[index]);
    index = parent;
  }
}

template <typename T, typename Comp>
auto heap<T,Comp>::down_heap() -> void
{
  size_type index = 0;

  for(;;)
  {
    size_type child1 = 2 * index + 1; // Left child.
    size_type child2 = 2 * index + 2; // Right child.

    // We are at the bottom of the heap, no need to go further.
    if(child1 >= heap_.size())
      break;

    // Set the minimum child to the left child to begin with.
    size_type min_child = child1;

    // If there is a right child and it is ``less" than the left,
    if(child2 < heap_.size() && comp(heap_[child2], heap_[child1]))
      min_child = child2;

    // All done if current is ``less" than minimum child
    if(comp(heap_[index], heap_[min_child]))
      break;

    // Swap the current node with the minimum child.
    std::swap(heap_[index], heap_[min_child]);
    index = min_child;
  }
}


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

} // namespace mrr

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#endif // #ifndef MRR_HEAP_HXX_
