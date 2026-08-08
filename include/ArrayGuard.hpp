#pragma once

#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T> class ArrayGuard {
public:
  /// @brief 默认构造函数
  ArrayGuard() = default;

  /// @brief 构造函数，分配指定大小的数组
  /// @param size 数组的大小
  inline explicit ArrayGuard(size_t size) : m_ptr(new T[size]), m_size(size) {}

  /// @brief 析构函数，释放数组内存
  inline ~ArrayGuard() { delete[] m_ptr; }

  /// @brief 禁止拷贝构造
  /// @param
  ArrayGuard(const ArrayGuard &) = delete;
  ArrayGuard &operator=(const ArrayGuard &) = delete;

  /// @brief 移动构造函数，转移资源所有权
  /// @param other 另一个 ArrayGuard 对象
  inline ArrayGuard(ArrayGuard &&other) noexcept
      : m_ptr(std::exchange(other.m_ptr, nullptr)),
        m_size(std::exchange(other.m_size, 0)) {}

  /// @brief 移动赋值运算符，转移资源所有权
  /// @param other 另一个 ArrayGuard 对象
  /// @return 当前对象的引用
  inline ArrayGuard &operator=(ArrayGuard &&other) noexcept {
    if (this != &other) {
      delete[] m_ptr;
      m_ptr = std::exchange(other.m_ptr, nullptr);
      m_size = std::exchange(other.m_size, 0);
    }
    return *this;
  }

  /// @brief 重载下标运算符，访问数组元素
  /// @param index 要访问的元素索引
  /// @return 指定索引处的数组元素的引用
  inline T &operator[](size_t index) {
    at(index);
    return m_ptr[index];
  }

  /// @brief 重载下标运算符，访问数组元素（常量版本）
  /// @param index 要访问的元素索引
  /// @return 指定索引处的数组元素的常量引用
  inline const T &operator[](size_t index) const {
    at(index);
    return m_ptr[index];
  }

  /// @brief 获取数组的指针
  /// @return 指向数组的指针
  inline T *data() { return m_ptr; }
  inline T *data() const { return m_ptr; }

  /// @brief 获取数组的大小
  /// @return 数组的大小
  inline size_t size() const { return m_size; }

  /// @brief 检查数组是否为空
  /// @return 如果数组为空则返回 true，否则返回 false
  inline bool empty() const { return m_size == 0; }

  /// @brief 访问指定索引处的数组元素，并进行范围检查
  /// @param index 要访问的元素索引
  /// @return 指定索引处的数组元素的引用
  inline T &at(size_t index) {
    if (index >= m_size) {
      throw std::out_of_range("ArrayGuard::at: index out of range");
    }
    return m_ptr[index];
  }
  inline T &at(size_t index) const {
    if (index >= m_size) {
      throw std::out_of_range("ArrayGuard::at: index out of range");
    }
    return m_ptr[index];
  }

  /// @brief 交换当前对象与另一个 ArrayGuard 对象的内容
  /// @param other 另一个 ArrayGuard 对象
  inline void swap(ArrayGuard &other) noexcept {
    using std::swap;
    swap(m_ptr, other.m_ptr);
    swap(m_size, other.m_size);
  }

private:
  T *m_ptr = nullptr;
  size_t m_size = 0;
};
