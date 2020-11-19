#pragma once

#include <memory>
#include <functional>
#include <iostream>
#include <utility>
#include <algorithm>

#include <filesystem>
#include <string>
#include <sstream>
#include <cstdint>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>

template<typename Base, typename T>
inline bool instanceof(const T*) {
   return std::is_base_of<Base, T>::value;
}
