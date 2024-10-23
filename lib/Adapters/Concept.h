#ifndef CONCEPT_H
#define CONCEPT_H
#include <utility>


template<typename T>
concept AssociativeC = requires(T t) {
  typename T::value_type::first_type;
  typename T::value_type::second_type;
};

template<typename T>
concept Set = requires(T a) {
  { a.begin() } -> std::same_as<typename T::iterator>;
  { a.end() } -> std::same_as<typename T::iterator>;
  { a.insert(std::declval<typename T::value_type>()) };
  { a.find(std::declval<typename T::value_type>()) } -> std::same_as<typename T::iterator>;
};

#endif //CONCEPT_H
