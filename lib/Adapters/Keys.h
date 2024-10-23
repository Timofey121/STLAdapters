#ifndef KEYS_H
#define KEYS_H

template<typename InnerIterator>
class KeysInIterator {
  public:
    using value_type = typename std::iterator_traits<InnerIterator>::value_type::first_type;

    explicit KeysInIterator(InnerIterator it)
      : it_(std::move(it)) {
    };

    value_type operator*() {
      return it_->first;
    }

    KeysInIterator& operator++() {
      ++it_;
      return *this;
    }

    constexpr auto operator<=>(const KeysInIterator& other) const = default;

  private:
    InnerIterator it_;
};

template<typename IteratorContainer>
class KeysAdapter {
  public:
    using const_iterator = KeysInIterator<IteratorContainer>;
    using iterator = const_iterator;

    constexpr KeysAdapter(IteratorContainer begin, IteratorContainer end)
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

class KeysHolder {
  public:
    KeysHolder() = default;

    template<typename C>
    friend KeysAdapter<typename C::const_iterator> operator|(const C& range, KeysHolder)
      requires (AssociativeC<C>) {
      return {range.cbegin(), range.cend()};
    }
};

class Keys {
  public:
    constexpr Keys() = default;

    template<typename C>
    KeysAdapter<typename C::const_iterator> operator()(const C& range) const
      requires (AssociativeC<C>) {
      return {range.cbegin(), range.cend()};
    }

    KeysHolder operator()() const {
      return {};
    }
};
#endif //KEYS_H
