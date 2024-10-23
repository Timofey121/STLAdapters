#ifndef FILTER_H
#define FILTER_H
#include "Concept.h"

template<typename InnerIterator, typename Functor>
class FilterInIterator {
  public:
    using value_type = typename InnerIterator::value_type;

    constexpr auto operator<=>(const FilterInIterator& other) const = default;

    FilterInIterator(InnerIterator it, Functor func)
      : it_(std::move(it)),
        func_(std::move(func)) {
      while (it_ != InnerIterator{} && !func_(*it_)) {
        ++it_;
      }
    };

    value_type operator*() {
      return *it_;
    }

    FilterInIterator& operator++() {
      do {
        ++it_;
      } while (it_ != InnerIterator{} && !func_(*it_));
      return *this;
    }

  private:
    InnerIterator it_;
    Functor func_;
};

template<typename IteratorContainer, typename FilterFunc>
class FilterAdapter {
  public:
    using const_iterator = FilterInIterator<IteratorContainer, FilterFunc>;
    using iterator = const_iterator;

    constexpr FilterAdapter(IteratorContainer begin, IteratorContainer end, FilterFunc fn)
      : begin_(std::move(begin)), end_(std::move(end)), func_(std::move(fn)) {
    };

    const_iterator begin() const {
      return {begin_, func_};
    }

    const_iterator end() const {
      return {end_, func_};
    }

    const_iterator cbegin() const {
      return {begin_, func_};
    }

    const_iterator cend() const {
      return {end_, func_};
    }

  private:
    IteratorContainer begin_;
    IteratorContainer end_;
    FilterFunc func_;
};

template<typename Funct>
class FilterHolder {
  public:
    FilterHolder(Funct fn)
      : fn_(std::move(fn)) {
    };

    template<typename C>
    friend FilterAdapter<typename C::const_iterator, Funct> operator|(const C& range, FilterHolder t)
      requires (!AssociativeC<C> && !Set<C>) {
      return {range.cbegin(), range.cend(), std::move(t.fn_)};
    }

  private:
    Funct fn_;
};

class Filter {
  public:
    constexpr Filter() = default;

    template<typename C, typename Funct>
    FilterAdapter<typename C::const_iterator, Funct> operator()(const C& range, Funct fn) const
      requires (!AssociativeC<C> && !Set<C>) {
      return {range.cbegin(), range.cend(), std::move(fn)};
    }

    template<typename Funct>
    FilterHolder<Funct> operator()(Funct fn) const {
      return {fn};
    }
};
#endif //FILTER_H
