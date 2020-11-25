#pragma once

#include <memory>
#include <chrono>
#include <functional>
#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>
#include <filesystem>
#include <string>
#include <sstream>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <unordered_set>

template<typename Base, typename T>
inline bool instanceof(const T*) {
   return std::is_base_of<Base, T>::value;
}
