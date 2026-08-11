//  Copyright (c) 2026 CrimsonSeraph(ltyy.leoyu@gmail.com)
//  SPDX-License-Identifier: MIT

// SinglyLinkedList.hpp
// 单向链表，提供基本功能

#pragma once

#include <memory>
#include <stdexcept>

template <typename T> class SinglyLinkedList {
public:
  /// @brief 单个节点：值 + 下一节点指针
  struct Node {
    T data;
    std::unique_ptr<Node> next;

    /// @brief 构造一个节点，保存给定值
    /// @param value 要存储的数据（拷贝构造）
    inline explicit Node(const T &value) : data(value), next(nullptr) {}
  };

  /// @brief 非常量迭代器，用于遍历链表并修改节点数据
  class Iterator {
    friend class ConstIterator;

  public:
    /// @brief 构造一个指向给定节点的迭代器
    /// @param ptr 指向节点的原始指针，迭代器将持有该指针
    inline explicit Iterator(Node *ptr) : m_ptr(ptr) {}

    /// @brief 解引用迭代器，返回节点数据的可变引用
    /// @return 当前节点中存储数据的引用（T&）
    inline T &operator*() const { return m_ptr->data; }

    /// @brief 通过箭头运算符访问节点数据（可变）
    /// @return 指向当前节点数据的指针（T*）
    inline T *operator->() const { return &m_ptr->data; }

    /// @brief 前置递增，使迭代器指向链表中的下一个节点
    /// @return 递增后的迭代器引用（指向下一节点）
    inline Iterator &operator++() {
      m_ptr = m_ptr->next.get();
      return *this;
    }

    /// @brief 比较两个迭代器是否不相等
    /// @param other 要比较的另一个迭代器
    /// @return 若指向不同节点则返回 true，否则 false
    inline bool operator!=(const Iterator &other) const {
      return m_ptr != other.m_ptr;
    }

  private:
    Node *m_ptr; ///< 底层原始指针
  };

  /// @brief 常量迭代器，用于只读遍历链表
  class ConstIterator {
  public:
    /// @brief 从非常量迭代器构造常量迭代器（允许隐式转换）
    /// @param it 非常量迭代器
    inline ConstIterator(const Iterator &it) : m_ptr(it.m_ptr) {}

    /// @brief 构造一个指向给定节点的常量迭代器
    /// @param ptr 指向节点的原始指针（常量）
    inline explicit ConstIterator(Node *ptr) : m_ptr(ptr) {}

    /// @brief 解引用迭代器，返回节点数据的常量引用（只读）
    /// @return 当前节点数据的常量引用（const T&）
    inline const T &operator*() const { return m_ptr->data; }

    /// @brief 通过箭头运算符访问节点数据（只读）
    /// @return 指向当前节点数据的常量指针（const T*）
    inline const T *operator->() const { return &m_ptr->data; }

    /// @brief 前置递增，使迭代器指向链表中的下一个节点
    /// @return 递增后的常量迭代器引用
    inline ConstIterator &operator++() {
      m_ptr = m_ptr->next.get();
      return *this;
    }

    /// @brief 比较两个常量迭代器是否不相等
    /// @param other 要比较的另一个常量迭代器
    /// @return 若指向不同节点则返回 true，否则 false
    inline bool operator!=(const ConstIterator &other) const {
      return m_ptr != other.m_ptr;
    }

  private:
    const Node *m_ptr;
  };

  using iterator = Iterator;
  using const_iterator = ConstIterator;

  /// @brief 默认构造函数
  inline explicit SinglyLinkedList() = default;

  /// @brief 默认析构函数
  inline ~SinglyLinkedList() = default;

  /// @brief 在链表头部添加一个新元素
  /// @param value 要添加的元素值（拷贝构造）
  inline void push_front(const T &value) {
    auto ptr = std::make_unique<Node>(value);
    ptr->next = std::move(m_head);
    m_head = std::move(ptr);
    m_size++;
  }

  /// @brief 移除链表头部的元素（若链表非空）
  inline void pop_front() {
    if (m_size == 0) {
      return;
    } else {
      m_head = std::move(m_head->next);
      m_size--;
    }
  }

  /// @brief 在指定索引位置之后插入一个新元素
  /// @param index 要插入位置的前一个节点索引（从0开始）
  /// @param value 要插入的元素值（拷贝构造）
  inline void insert_after(size_t index, const T &value) {
    if (index >= m_size)
      throw std::out_of_range(
          "SinglyLinkList::insert_after: index out of range!");

    auto ptr = std::make_unique<Node>(value);
    Node *current_ptr = m_head.get();
    for (size_t i = 0; i < index; ++i) {
      current_ptr = current_ptr->next.get();
    }
    ptr->next = std::move(current_ptr->next);
    current_ptr->next = std::move(ptr);
    m_size++;
  }

  /// @brief 删除指定索引位置之后的那个节点
  /// @param index 要删除节点的前一个节点索引（从0开始）
  inline void erase_after(size_t index) {
    if (m_size < 2 || index >= m_size - 1)
      throw std::out_of_range(
          "SinglyLinkList::erase_after: index out of range!");

    Node *current_ptr = m_head.get();
    for (size_t i = 0; i < index; ++i) {
      current_ptr = current_ptr->next.get();
    }
    current_ptr->next = std::move(current_ptr->next->next);
    m_size--;
  }

  /// @brief 获取链表中当前存储的元素个数
  /// @return 链表大小（size_t）
  inline size_t size() const { return m_size; }

  /// @brief 返回指向容器第一个元素的非常量迭代器
  /// @return 指向头节点（m_head）的迭代器；若容器为空，则返回与 end()
  /// 相同的尾后迭代器（nullptr）。
  inline iterator begin() noexcept { return Iterator(m_head.get()); }

  /// @brief 返回容器的尾后非常量迭代器（哨兵）
  /// @return 始终返回 nullptr 构造的迭代器，表示序列的结束位置
  inline iterator end() noexcept { return Iterator(nullptr); }

  /// @brief 返回指向容器第一个元素的常量迭代器（只读）
  /// @return 指向头节点的常量迭代器；若容器为空，则返回与 cend()
  /// 相同的尾后迭代器。
  inline const_iterator cbegin() const noexcept {
    return ConstIterator(m_head.get());
  }

  /// @brief 返回容器的尾后常量迭代器（只读哨兵）
  /// @return 始终返回 nullptr 构造的常量迭代器，表示常量序列的结束位置
  inline const_iterator cend() const noexcept { return ConstIterator(nullptr); }

  /// @brief 返回指向容器第一个元素的常量迭代器（只读）
  /// @return 与 cbegin() 相同，提供 const 对象上的范围 for 支持
  inline const_iterator begin() const noexcept { return cbegin(); }

  /// @brief 返回容器的尾后常量迭代器（只读）
  /// @return 与 cend() 相同，提供 const 对象上的范围 for 支持
  inline const_iterator end() const noexcept { return cend(); }

private:
  std::unique_ptr<Node> m_head;
  size_t m_size = 0;
};
