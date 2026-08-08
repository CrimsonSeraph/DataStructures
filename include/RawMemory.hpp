//  Copyright (c) 2026 CrimsonSeraph(ltyy.leoyu@gmail.com)
//  SPDX-License-Identifier: MIT

// RawMemory.hpp
// 原始内存管理类，用于分配和管理原始内存，提供安全的访问和操作接口。

#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>

template <typename T> class RawMemory {
public:
  /// @brief 构造函数，分配指定大小的原始内存
  /// @param size 原始内存的大小
  inline explicit RawMemory(size_t size) : m_size(size) {
    m_ptr = static_cast<T *>(::operator new(m_size * sizeof(T)));
  }

  /// @brief 析构函数，释放原始内存
  inline ~RawMemory() { ::operator delete(m_ptr); }

  /// @brief 禁止拷贝构造和拷贝赋值
  /// @param
  RawMemory(const RawMemory &) = delete;
  RawMemory &operator=(const RawMemory &) = delete;

  /// @brief 移动构造函数，转移资源所有权
  /// @param other 另一个 RawMemory 对象
  inline RawMemory(RawMemory &&other) noexcept
      : m_ptr(std::exchange(other.m_ptr, nullptr)),
        m_size(std::exchange(other.m_size, 0)) {}

  /// @brief 移动赋值运算符，转移资源所有权
  /// @param other 另一个 RawMemory 对象
  /// @return 当前对象的引用
  inline RawMemory &operator=(RawMemory &&other) noexcept {
    if (this != &other) {
      ::operator delete(m_ptr);
      m_ptr = std::exchange(other.m_ptr, nullptr);
      m_size = std::exchange(other.m_size, 0);
    }
    return *this;
  }

  /// @brief 重载下标运算符，访问原始内存中的元素
  /// @param index 要访问的元素索引
  /// @return 指定索引处的原始内存元素的引用
  inline T &operator[](size_t index) {
    at(index);
    return m_ptr[index];
  }

  /// @brief 重载下标运算符，访问原始内存中的元素（常量版本）
  /// @param index 要访问的元素索引
  /// @return 指定索引处的原始内存元素的常量引用
  inline const T &operator[](size_t index) const {
    at(index);
    return m_ptr[index];
  }

  /// @brief 指定索引处原始内存的指针，并进行范围检查
  /// @param index 要访问的元素索引
  /// @return 指向原始内存的指针
  inline T *at(size_t index) const {
    if (index >= m_size) {
      throw std::out_of_range("Index out of range");
    }
    return &m_ptr[index];
  }

  /// @brief 检查原始内存是否为空
  /// @return 如果原始内存为空，则返回 true；否则返回 false
  inline bool empty() const { return m_size == 0; }

  /// @brief 交换当前对象与另一个 RawMemory 对象的内容
  /// @param other 另一个 RawMemory 对象
  inline void swap(RawMemory &other) noexcept {
    using std::swap;
    swap(m_ptr, other.m_ptr);
    swap(m_size, other.m_size);
  }

  /// @brief 获取原始内存的指针
  /// @return 指向原始内存的指针
  inline T *data() { return m_ptr; }

  /// @brief 获取原始内存的指针（常量版本）
  /// @return 指向原始内存的常量指针
  inline const T *data() const { return m_ptr; }

  /// @brief 获取原始内存的大小
  /// @return 原始内存的大小
  inline size_t size() const { return m_size; }

private:
  T *m_ptr;
  size_t m_size;
};
