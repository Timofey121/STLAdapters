#ifndef VALUES_H
#define VALUES_H

template<typename InnerIterator>
class ValuesInIterator {
  public:
    using value_type = typename std::iterator_traits<InnerIterator>::value_type::second_type;

    explicit ValuesInIterator(InnerIterator it)
      : it_(std::move(it)) {
    };

    value_type operator*() {
      return it_->second;
    }

    ValuesInIterator& operator++() {
      ++it_;
      return *this;
    }

    constexpr auto operator<=>(const ValuesInIterator& other) const = default;

  private:
    InnerIterator it_;
};

template<typename IteratorContainer>
class ValuesAdapter {
  public:
    using const_iterator = ValuesInIterator<IteratorContainer>;
    using iterator = const_iterator;

    constexpr ValuesAdapter(IteratorContainer begin, IteratorContainer end)
      : begin_(std::move(begin)), end_(std::move(end)) {
    };

    iterator begin() {
      return iterator(begin_);
    }

    iterator end() {
      return iterator(end_);
    }

  private:
    IteratorContainer begin_;
    IteratorContainer end_;
};

class ValuesHolder {
  public:
    ValuesHolder() = default;

    template<typename C>
    friend ValuesAdapter<typename C::const_iterator> operator|(const C& range, ValuesHolder)
      requires (AssociativeC<C>) {
      return {range.cbegin(), range.cend()};
    }
};

class Values {
  public:
    constexpr Values() = default;

    template<typename C>
    ValuesAdapter<typename C::const_iterator> operator()(const C& range) const
      requires (AssociativeC<C>) {
      return {range.cbegin(), range.cend()};
    }

    ValuesHolder operator()() const {
      return {};
    }
};
#endif //VALUES_H
