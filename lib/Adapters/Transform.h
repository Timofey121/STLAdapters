#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "Concept.h"


template<typename InnerIterator, typename Functor>
class TransformInIterator {
  public:
    using inner_iterator_type = typename InnerIterator::value_type;
    using value_type = std::invoke_result_t<Functor, inner_iterator_type>;

    constexpr auto operator<=>(const TransformInIterator& other) const = default;

    TransformInIterator(InnerIterator it, Functor func)
      : it_(std::move(it)),
        func_(std::move(func)) {
    };

    value_type operator*() {
      return func_(*it_);
    }

    TransformInIterator& operator++() {
      ++it_;
      return *this;
    }

  private:
    InnerIterator it_;
    Functor func_;
};

template<typename IteratorContainer, typename TransformFunc>
class TransformAdapter {
  public:
    using const_iterator = TransformInIterator<IteratorContainer, TransformFunc>;
    using iterator = const_iterator;

    constexpr TransformAdapter(IteratorContainer begin, IteratorContainer end, TransformFunc fn)
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
    TransformFunc func_;
};


template<typename Funct>
class TransformHolder {
  public:
    TransformHolder(Funct fn)
      : fn_(std::move(fn)) {
    };

    template<typename C>
    friend TransformAdapter<typename C::const_iterator, Funct> operator|(const C& range, TransformHolder t)
      requires (!AssociativeC<C> && !Set<C>) {
      return {range.cbegin(), range.cend(), std::move(t.fn_)};
    }

  private:
    Funct fn_;
};

class Transform {
  public:
    constexpr Transform() = default;

    template<typename C, typename Funct>
    TransformAdapter<typename C::const_iterator, Funct> operator()(const C& range, Funct fn) const
      requires (!AssociativeC<C> && !Set<C>) {
      return {range.cbegin(), range.cend(), std::move(fn)};
    }

    template<typename Funct>
    TransformHolder<Funct> operator()(Funct fn) const {
      return {fn};
    }
};
#endif //TRANSFORM_H
