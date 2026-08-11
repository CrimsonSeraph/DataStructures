//  Copyright (c) 2026 CrimsonSeraph(ltyy.leoyu@gmail.com)
//  SPDX-License-Identifier: MIT

// FixedVector.hpp
// 自定义向量类（顺序表），提供动态数组功能，支持在固定容量内添加元素

#pragma once

#include "memory/RawMemory.hpp"

#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>

template <typename T> class FixedVector {
public:
  using iterator = T *;
  using const_iterator = const T *;

  /// @brief 构造函数，分配指定容量的固定向量
  /// @param capacity 固定向量的容量
  inline explicit FixedVector(size_t capacity)
      : m_data(capacity), m_length(0) {}

  /// @brief 析构函数，销毁固定向量中的元素
  inline ~FixedVector() {
    for (size_t i = 0; i < m_length; ++i) {
      std::destroy_at(m_data.data() + i);
    }
  }

  /// @brief 在向量末尾添加一个元素
  /// @param value 要添加的元素值
  inline void push_back(const T &value) {
    if (m_length >= m_data.size()) {
      reserve(m_data.size() == 0 ? 1 : m_data.size() * 2);
    }

    std::construct_at(m_data.data() + m_length, value);
    m_length++;
  }

  /// @brief 移除向量末尾的元素
  inline void pop_back() {
    if (m_length > 0) {
      std::destroy_at(m_data.data() + m_length - 1);
      m_length--;
    } else {
      throw std::out_of_range(
          "FixedVector::pop_back: Cannot pop_back from an empty FixedVector");
    }
  }

  /// @brief 在指定索引处插入一个元素
  /// @param index 要插入元素的索引
  /// @param value 要插入的元素值
  inline void insert(size_t index, const T &value) {
    if (index > m_length)
      throw std::out_of_range("FixedVector::insert: index out of range!");

    if (m_length >= m_data.size()) {
      size_t new_cap = m_data.size() == 0 ? 1 : m_data.size() * 2;
      reserve(new_cap);
    }

    if (index == m_length) {
      std::construct_at(m_data.data() + m_length, value);
    } else {
      std::construct_at(m_data.data() + m_length,
                        std::move(m_data.data()[m_length - 1]));
      std::move_backward(m_data.data() + index, m_data.data() + m_length - 1,
                         m_data.data() + length);

      std::construct_at(m_data.data() + index, value);
    }

    m_length++;
  }

  /// @brief 删除指定索引处的元素
  /// @param index 要删除元素的索引
  inline void erase(size_t index) {
    if (index >= m_length)
      throw std::out_of_range("FixedVector::insert: index out of range!");

    std::move(m_data.data() + index + 1, m_data.data() + m_length,
              m_data.data() + index);

    m_length--;
    std::destroy_at(m_data.data() + m_length);
  }

  /// @brief  预留容量
  /// @param new_capacity 目标容量大小
  /// @return 是否成功
  inline bool reserve(size_t new_capacity) {
    if (new_capacity <= m_data.size())
      return false;

    RawMemory<T> new_data(new_capacity);
    std::uninitialized_move(m_data.data(), m_data.data() + m_length,
                            new_data.data());
    std::destroy(m_data.data(), m_data.data() + m_length);
    m_data = std::move(new_data);

    return true;
  }

  inline void shrink_to_fit() {
    if (m_length == 0) {
      RawMemory<T> empty_data(0);
      m_data = std::move(empty_data);
      return;
    }

    if (m_length == m_data.size())
      return;

    RawMemory<T> new_data(m_length);
    std::uninitialized_move(m_data.data(), m_data.data() + m_length,
                            new_data.data());
    std::destroy(m_data.data(), m_data.data() + m_length);
    m_data = std::move(new_data);
  }

  /// @brief 清空向量
  inline void clear() {
    for (size_t i = 0; i < m_length; ++i) {
      std::destroy_at(m_data.data() + i);
    }
    m_length = 0;
  }

  /// @brief 重载下标运算符，访问向量中的元素
  /// @param index 要访问的元素索引
  /// @return 指定索引处的元素的引用
  inline T &operator[](size_t index) {
    if (index >= m_length)
      throw std::out_of_range("FixedVector: index out of range!");

    return m_data[index];
  }

  /// @brief 重载下标运算符，访问向量中的元素（常量版本）
  /// @param index 要访问的元素索引
  /// @return 指定索引处的元素的常量引用
  inline const T &operator[](size_t index) const {
    if (index >= m_length)
      throw std::out_of_range("FixedVector: index out of range!");

    return m_data[index];
  }

  /// @brief 获取向量的当前长度
  /// @return 向量中元素的数量
  inline size_t length() const { return m_length; }

  /// @brief 获取向量的容量
  /// @return 向量的最大容量
  inline size_t capacity() const { return m_data.size(); }

  /// @brief 检查是否为空
  /// @return 是否为空
  inline bool empty() const noexcept { return m_length == 0; }

  /// @brief 返回指向容器第一个元素的迭代器（非常量）
  /// @return iterator 指向首元素；若容器为空，则返回的迭代器等于 end()
  inline iterator begin() noexcept { return m_data.data(); }

  /// @brief 返回指向容器尾后位置的迭代器（非常量）
  /// @return iterator 指向尾后位置
  inline iterator end() noexcept { return m_data.data() + m_length; }

  /// @brief 返回指向容器第一个元素的常量迭代器
  /// @return const_iterator 指向首元素（只读）
  inline const_iterator cbegin() const noexcept { return m_data.data(); }

  /// @brief 返回指向容器尾后位置的常量迭代器
  /// @return const_iterator 指向尾后位置（只读）
  inline const_iterator cend() const noexcept {
    return m_data.data() + m_length;
  }

  /// @brief 返回指向容器第一个元素的常量迭代器（const 对象重载）
  /// @return const_iterator 指向首元素（只读）
  inline const_iterator begin() const noexcept { return cbegin(); }

  /// @brief 返回指向容器尾后位置的常量迭代器（const 对象重载）
  /// @return const_iterator 指向尾后位置（只读）
  inline const_iterator end() const noexcept { return cend(); }

private:
  RawMemory<T> m_data;
  size_t m_length;
};
