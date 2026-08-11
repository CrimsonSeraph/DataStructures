//  Copyright (c) 2026 CrimsonSeraph(ltyy.leoyu@gmail.com)
//  SPDX-License-Identifier: MIT

// ArrayStack.hpp
// 顺序栈 - 复用 FixedVector

#pragma once

#include "container/FixedVector.hpp"

#include <stdexcept>

template <typename T> class ArrayStack {
public:
  /// @brief 构造函数，分配固定容量的顺序栈
  /// @param size 顺序栈容量
  inline explicit ArrayStack(size_t size = 10) : m_data(size) {}

  /// @brief 入栈
  /// @param value 入栈值
  inline void push_back(const T &value) { m_data.push_back(value); }

  /// @brief 出栈
  inline void pop_back() {
    if (empty()) {
      throw std::out_of_range("ArrayStack::pop_back: Stack empty!");
      return;
    }

    m_data.pop_back();
  }

  /// @brief 获得栈顶值
  /// @return 栈顶值
  T &top() {
    if (empty()) {
      throw std::out_of_range("ArrayStack::top: Stack empty!");
      return;
    }

    return m_data[m_data.size() - 1];
  }

  /// @brief 检查栈是否为空
  /// @return 是否为空
  bool empty() const { return m_data.empty(); }

  /// @brief 获得当前栈大小
  /// @return 当前栈大小
  size_t size() const { return m_data.size(); }

private:
  FixedVector<T> m_data;
};
