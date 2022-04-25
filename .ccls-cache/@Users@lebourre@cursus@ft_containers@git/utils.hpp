#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft {

struct nullptr_t {
 private:
  void operator&() const;

 public:
  template < class T >
  inline operator T*() const {
    return 0;
  }

  template < class C, class T >
  inline operator T C::*() const {
    return 0;
  }
};

static nullptr_t u_nullptr = {};

}

#endif
