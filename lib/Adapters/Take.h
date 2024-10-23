#ifndef TAKE_H
#define TAKE_H
#include <cstdint>

#include "Concept.h"

template<typename InnerIterator>
class TakeInIterator {
  public:
    using value_type = typename InnerIterator::value_type;

    TakeInIterator(InnerIterator it)
      : it_(std::move(it)) {
    };

    value_type operator*() {
      return *it_;
    }

    TakeInIterator& operator++() {
      ++it_;
      return *this;
    }

    TakeInIterator& operator--() {
      --it_;
      return *this;
    }

    constexpr auto operator<=>(const TakeInIterator& other) const = default;

  private:
    InnerIterator it_;
};

template<typename IteratorContainer>
class TakeAdapter {
  public:
    using const_iterator = TakeInIterator<IteratorContainer>;
    using iterator = const_iterator;

    constexpr TakeAdapter(IteratorContainer begin, IteratorContainer end, uint64_t n)
      : begin_(std::move(begin)), end_(std::move(end)), n_(n) {
    };

    const_iterator begin() const {
      return {begin_};
    }

    const_iterator end() const {
      uint64_t counter = 0;
      auto it_end = end_;
      auto it = begin_;
      while (it != end_) {
        ++it;
        ++counter;
      }
      counter -= n_;
      while (counter != 0) {
        --it_end;
        --counter;
      }
      return iterator(it_end);
    }

    const_iterator cbegin() const {
      return {begin_};
    }

    const_iterator cend() const {
      return {end_};
    }

  private:
    IteratorContainer begin_;
    IteratorContainer end_;
    uint64_t n_;
};

class TakeHolder {
  public:
    TakeHolder(const uint64_t n)
      : n_(n) {
    };

    template<typename C>
    friend TakeAdapter<typename C::const_iterator> operator|(const C& range, TakeHolder t)
      requires (!AssociativeC<C> && !Set<C>) {
      return {range.cbegin(), range.cend(), t.n_};
    }

  private:
    uint64_t n_;
};

class Take {
  public:
    constexpr Take() = default;

    template<typename C>
    TakeAdapter<typename C::const_iterator> operator()(const C& range, uint64_t n) const
      requires (!AssociativeC<C> && !Set<C>) {
      return {range.cbegin(), range.cend(), n};
    }

    TakeHolder operator()(uint64_t n) const {
      return {n};
    }
};
#endif //TAKE_H
