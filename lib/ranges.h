#pragma once

#include "Adapters/Filter.h"
#include "Adapters/Take.h"
#include "Adapters/Transform.h"
#include "Adapters/Drop.h"
#include "Adapters/Reverse.h"
#include "Adapters/Keys.h"
#include "Adapters/Values.h"


namespace ranges {
  constexpr Transform transform;
  constexpr Filter filter;
  constexpr Take take;
  constexpr Drop drop;
  constexpr Reverse reverse;
  constexpr Keys keys;
  constexpr Values values;
};
