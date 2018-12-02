#include <algorithm>
#include <iterator>
#include <cstdint>

struct add_zip_iterator: public std::iterator<std::random_access_iterator_tag, uint32_t>
{
  uint32_t* a;
  uint32_t* b;

  using traits = std::iterator_traits<add_zip_iterator>;

  add_zip_iterator() { }
  add_zip_iterator(uint32_t* a_, uint32_t* b_):
    a(a_), b(b_)
  { }

  add_zip_iterator(add_zip_iterator const&) = default;
  add_zip_iterator(add_zip_iterator&&) = default;

  inline uint32_t operator*() const { return *a + *b; }
  inline add_zip_iterator& operator++() {
    ++a; ++b;
    return *this;
  }
  inline add_zip_iterator operator++(int) const {
    add_zip_iterator ret;
    ret.a = a+1;
    ret.b = b+1;
    return ret;
  }
  inline bool operator==(add_zip_iterator const& o) const
  {
    return (o.a == a) && (o.b == b);
  }
  inline bool operator!=(add_zip_iterator const& o) const
  {
    return !(*this == o);
  }
  inline add_zip_iterator& operator+=(traits::difference_type n)
  {
    a += n; b += n;
    return *this;
  }

  inline add_zip_iterator operator+(traits::difference_type n) const
  {
    return add_zip_iterator{a+n, b+n};
  }

  inline add_zip_iterator& operator-=(traits::difference_type n)
  {
    a -= n; b -= n;
    return *this;
  }

  inline add_zip_iterator operator-(traits::difference_type n) const
  {
    return add_zip_iterator{a-n, b-n};
  }

  inline uint32_t operator[](traits::difference_type n) const
  {
    return *(a+n) + *(b+n);
  }

  inline difference_type operator-(add_zip_iterator const& o) const
  {
    return o.a - a;
  }
};

void op(uint32_t* res, add_zip_iterator const it, add_zip_iterator const it_end)
{
  // CHECK-LABEL: define void @{{.*op.*\(.*\).*}} {
  // CHECK: add <{{[0-9]+}} x i32>
  std::copy(it, it_end, res);
}
