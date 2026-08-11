//  Copyright (c) 2026 CrimsonSeraph(ltyy.leoyu@gmail.com)
//  SPDX-License-Identifier: MIT

#include "application/Polynomial.h"
#include "container/FixedVector.hpp"
#include "container/SinglyLinkedList.hpp"

#include <iostream>
#include <string>

void test_FixVector() {
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
}

void test_SinglyLinkedList() {
  SinglyLinkedList<int> list;

  list.push_front(10);
  list.push_front(20);
  list.push_front(30);

  std::cout << "Initial linked list: ";
  for (const auto &val : list) {
    std::cout << val << " ";
  }
  std::cout << std::endl; // 输出 30 20 10

  list.insert_after(1, 99);
  std::cout << "The linked list after insertion: ";
  for (auto it = list.begin(); it != list.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  list.erase_after(2);
  std::cout << "The list after deletion: ";
  for (auto it = list.begin(); it != list.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

void test_Polynomial() {
  Polynomial p;
  p.insert_term(3, 2);
  p.insert_term(2, 1);
  p.insert_term(-1, 0);
  std::cout << p.to_string() << std::endl;
  std::cout << p.evaluate(2) << std::endl;
}

int main() {
  //   test_FixVector();
  //   std::cout << std::endl;
  //   test_SinglyLinkedList();
  //   std::cout << std::endl;
  test_Polynomial();

  return 0;
}
