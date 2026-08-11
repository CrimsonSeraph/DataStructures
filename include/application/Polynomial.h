//  Copyright (c) 2026 CrimsonSeraph(ltyy.leoyu@gmail.com)
//  SPDX-License-Identifier: MIT

// Polynomial.h
// 基于 SinglyLinkedList.hpp 单向链表的多项式类头文件

#pragma once

#include "container/SinglyLinkedList.hpp"

#include <string>

class Polynomial {
public:
  /// @brief 单项式：系数 + 指数
  struct Term {
    double coef;
    int exp;

    /// @brief 构造单项式
    /// @param c 系数
    /// @param e 指数
    inline Term(double c, int e) : coef(c), exp(e) {}
  };

  /// @brief 默认构造函数，构造零多项式（空链表）
  Polynomial();

  /// @brief 从单个项构造多项式（coef 为 0.0 则构造空链表）
  /// @param coef 系数
  /// @param exp  指数
  Polynomial(double coef, int exp);

  /// @brief 向多项式中插入一项，自动维持指数降序，并合并同类项
  /// @param coef 系数（若为0则忽略）
  /// @param exp  指数
  void insert_term(double coef, int exp);

  /// @brief 将多项式转换为易读的字符串形式
  /// @return 格式化的字符串
  std::string to_string() const;

  /// @brief 计算多项式在给定 x 处的值
  /// @param x 自变量
  /// @return 多项式值
  double evaluate(double x) const;

  /// @brief 多项式加法（待实现）
  /// @param other 另一个多项式
  /// @return 相加后的新多项式
  // Polynomial add(const Polynomial& other) const;

  /// @brief 多项式减法（待实现）
  /// @param other 另一个多项式
  /// @return 相减后的新多项式
  // Polynomial subtract(const Polynomial& other) const;

private:
  SinglyLinkedList<Term> m_terms; ///< 存储各项的链表（指数降序）

  /// @brief 在链表中查找指数为 exp 的项，返回其指针（可修改）
  /// @param exp 要查找的指数
  /// @return 若找到则返回指向该项的指针，否则返回 nullptr
  Term *get_current_term(int exp);

  /// @brief 确定一个新项（指数为 exp）应该插入的位置（前驱索引）
  /// @param exp 待插入项的指数
  /// @return 前驱节点在链表中的索引（从0开始），若应插入头部则返回 SIZE_MAX
  size_t get_current_index(int exp);
};
