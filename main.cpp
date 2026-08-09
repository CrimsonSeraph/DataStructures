//  Copyright (c) 2026 CrimsonSeraph(ltyy.leoyu@gmail.com)
//  SPDX-License-Identifier: MIT

#include "FixedVector.hpp"

#include <iostream>
#include <string>

int main() {
  FixedVector<std::string> vec(2);
  vec.push_back("Hello");
  vec.push_back("world! ");
  std::cout << "vec.length(): " << vec.length() << std::endl;
  vec.reserve(10);
  vec.push_back("C++");
  vec.push_back("is");
  vec.push_back("awesome!");
  std::cout << "vec.capacity(): " << vec.capacity() << std::endl;
  vec.pop_back();
  std::cout << "vec.length() after pop_back: " << vec.length() << std::endl;
  vec.push_back("dificult! ");
  vec.shrink_to_fit();
  std::cout << "vec.capacity() after shrink_to_fit: " << vec.capacity()
            << std::endl;

  for (const auto &s : vec) {
    std::cout << s << " ";
  }
  std::cout << std::endl;

  return 0;
}
