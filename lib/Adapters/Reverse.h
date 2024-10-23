#ifndef REVERSE_H
#define REVERSE_H

template<typename InnerIterator>
class ReverseInIterator {
  public:
    using value_type = typename InnerIterator::value_type;

    ReverseInIterator(InnerIterator it)
      : it_(std::move(it)) {
    };

    value_type operator*() {
      return *it_;
    }

    ReverseInIterator& operator++() {
      ++it_;
      return *this;
    }

    constexpr auto operator<=>(const ReverseInIterator& other) const = default;

  private:
    InnerIterator it_;
};

template<typename IteratorContainer>
class ReverseAdapter {
  public:
    using inner_iterator = typename IteratorContainer::const_reverse_iterator;
    using const_iterator = ReverseInIterator<inner_iterator>;
    using iterator = const_iterator;
    using const_reverse_iterator = typename IteratorContainer::const_iterator;

    ReverseAdapter(IteratorContainer range) :
      range_(range) {
    }

    iterator begin() {
      return iterator(range_.rbegin());
    }

    iterator end() {
      return iterator(range_.rend());
    }

    const_reverse_iterator rbegin() {
      return range_.begin();
    }

    const_reverse_iterator rend() {
      return range_.end();
    }

  private:
    IteratorContainer range_;
};

class ReverseHolder {
  public:
    ReverseHolder() = default;

    template<typename C>
    friend ReverseAdapter<C> operator|(const C& range, ReverseHolder t)
      requires (!AssociativeC<C> && !Set<C>) {
      return {range};
    }
};

class Reverse {
  public:
    constexpr Reverse() = default;

    template<typename C>
    ReverseAdapter<C> operator()(const C& range) const
      requires (!AssociativeC<C> && !Set<C>) {
      return {range};
    }

    ReverseHolder operator()() const {
      return {};
    }
};

#endif //REVERSE_H
