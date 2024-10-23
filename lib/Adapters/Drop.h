#ifndef DROP_H
#define DROP_H

template<typename InnerIterator>
class DropInIterator {
  public:
    using value_type = typename InnerIterator::value_type;

    DropInIterator(InnerIterator it, const uint64_t n)
      : it_(std::move(it)),
        n_(n) {
      while (n_ != 0) {
        --n_;
        ++it_;
      }
    };

    value_type operator*() {
      return *it_;
    }

    DropInIterator& operator++() {
      ++it_;
      return *this;
    }

    constexpr auto operator<=>(const DropInIterator& other) const = default;

  private:
    InnerIterator it_;
    uint64_t n_;
};

template<typename IteratorContainer>
class DropAdapter {
  public:
    using const_iterator = DropInIterator<IteratorContainer>;
    using iterator = const_iterator;

    constexpr DropAdapter(IteratorContainer begin, IteratorContainer end, const uint64_t n)
      : begin_(std::move(begin)), end_(std::move(end)), n_(n) {
    };

    const_iterator begin() const {
      return {begin_, n_};
    }

    const_iterator end() const {
      return {end_, 0};
    }

    const_iterator cbegin() const {
      return {begin_, n_};
    }

    const_iterator cend() const {
      return {end_, 0};
    }

  private:
    IteratorContainer begin_;
    IteratorContainer end_;
    uint64_t n_;
};

class DropHolder {
  public:
    DropHolder(const uint64_t n)
      : n_(n) {
    };

    template<typename C>
    friend DropAdapter<typename C::const_iterator> operator|(const C& range, DropHolder t)
      requires (!AssociativeC<C> && !Set<C>) {
      return {range.cbegin(), range.cend(), t.n_};
    }

  private:
    uint64_t n_;
};

class Drop {
  public:
    constexpr Drop() = default;

    template<typename C>
    DropAdapter<typename C::const_iterator> operator()(const C& range, uint64_t n) const
      requires (!AssociativeC<C> && !Set<C>) {
      return {range.cbegin(), range.cend(), n};
    }

    DropHolder operator()(uint64_t n) const {
      return {n};
    }
};
#endif //DROP_H
