//  Copyright (c) 2026 CrimsonSeraph(ltyy.leoyu@gmail.com)
//  SPDX-License-Identifier: MIT

// FixedVector.hpp
// 自定义向量类，提供动态数组功能，支持在固定容量内添加元素

#pragma once

#include "RawMemory.hpp"

#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>

template <typename T> class FixedVector {
public:
  /// @brief 构造函数，分配指定容量的固定向量
  /// @param capacity 固定向量的容量
  explicit FixedVector(size_t capacity) : m_data(capacity), m_length(0) {}

  /// @brief 析构函数，销毁固定向量中的元素
  ~FixedVector() {
    for (size_t i = 0; i < m_length; ++i) {
      std::destroy_at(m_data.data() + i);
    }
  }

  /// @brief 在向量末尾添加一个元素
  /// @param value 要添加的元素值
  void push_back(const T &value) {
    if (m_length >= m_data.size()) {
      size_t new_capacity = m_data.size() == 0 ? 1 : m_data.size() * 2;
      RawMemory<T> new_data(new_capacity);
      std::uninitialized_move(m_data.data(), m_data.data() + m_length,
                              new_data.data());
      std::destroy(m_data.data(), m_data.data() + m_length);
      m_data = std::move(new_data);
    }

    std::construct_at(m_data.data() + m_length, value);
    m_length++;
  }

  /// @brief 移除向量末尾的元素
  void pop_back() {
    if (m_length > 0) {
      std::destroy_at(m_data.data() + m_length - 1);
      m_length--;
    } else {
      throw std::out_of_range("Cannot pop_back from an empty FixedVector");
    }
  }

  /// @brief 重载下标运算符，访问向量中的元素
  /// @param index 要访问的元素索引
  /// @return 指定索引处的元素的引用
  T &operator[](size_t index) {
    m_data.at(index);
    return m_data[index];
  }

  /// @brief 重载下标运算符，访问向量中的元素（常量版本）
  /// @param index 要访问的元素索引
  /// @return 指定索引处的元素的常量引用
  const T &operator[](size_t index) const {
    m_data.at(index);
    return m_data[index];
  }

  /// @brief 获取向量的当前长度
  /// @return 向量中元素的数量
  size_t length() const { return m_length; }

  /// @brief 获取向量的容量
  /// @return 向量的最大容量
  size_t capacity() const { return m_data.size(); }

private:
  RawMemory<T> m_data;
  size_t m_length;
};
