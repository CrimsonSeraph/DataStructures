//  Copyright (c) 2026 CrimsonSeraph(ltyy.leoyu@gmail.com)
//  SPDX-License-Identifier: MIT

// Polynomial.h
// 基于 SinglyLinkedList.hpp 单向链表的多项式类源文件

#include "application/Polynomial.h"

#include <cmath>
#include <cstdint>
#include <sstream>
#include <string>

namespace {
/// @brief 将 double 系数格式化为简洁字符串（自动去掉多余的尾零）
/// @param v 需要格式化的系数
/// @return 格式化后的字符串
std::string format_coef(double v) {
  if (v == 0.0) {
    return "0";
  }
  std::ostringstream oss;
  oss << v;
  return oss.str();
}
} // namespace

Polynomial::Polynomial() {}

Polynomial::Polynomial(double coef, int exp) {
  if (coef != 0.0)
    m_terms.push_front(Term(coef, exp));
}

void Polynomial::insert_term(double coef, int exp) {
  if (coef == 0.0)
    return;

  Term *term = get_current_term(exp);
  if (term) {
    term->coef += coef;
    if (term->coef == 0.0) {
      size_t prev = get_current_index(term->exp);
      if (prev == SIZE_MAX) {
        m_terms.pop_front();
      } else {
        m_terms.erase_after(prev);
      }
    }

    return;
  }

  const size_t pos = get_current_index(exp);
  if (pos == SIZE_MAX || m_terms.size() == 0) {
    m_terms.push_front(Term(coef, exp));
  } else {
    m_terms.insert_after(pos, Term(coef, exp));
  }
}

std::string Polynomial::to_string() const {
  std::string result;
  for (auto it = m_terms.cbegin(); it != m_terms.cend(); ++it) {
    const double coef = it->coef;
    const int exp = it->exp;
    if (coef == 0.0)
      continue;

    if (!result.empty()) {
      result += (coef > 0) ? " + " : " - ";
    } else if (coef < 0) {
      result += "-";
    }

    const double abs_coef = std::fabs(coef);
    if (exp == 0) {
      result += format_coef(abs_coef);
    } else {
      if (abs_coef != 1.0) {
        result += format_coef(abs_coef);
      }
      result += 'x';
      if (exp != 1) {
        result += "^" + std::to_string(exp);
      }
    }
  }
  return result.empty() ? "0" : result;
}

double Polynomial::evaluate(double x) const {
  double result = 0.0;
  for (auto it = m_terms.cbegin(); it != m_terms.cend(); ++it) {
    result += it->coef * std::pow(x, it->exp);
  }
  return result;
}

Polynomial::Term *Polynomial::get_current_term(int exp) {
  for (auto it = m_terms.begin(); it != m_terms.end(); ++it) {
    if (it->exp == exp) {
      return &(*it);
    }
  }
  return nullptr;
}

size_t Polynomial::get_current_index(int exp) {
  size_t index = 0;
  for (auto it = m_terms.begin(); it != m_terms.end(); ++it, ++index) {
    if (it->exp < exp) {
      return (index == 0) ? SIZE_MAX : index - 1;
    }
  }
  return m_terms.size() == 0 ? SIZE_MAX : m_terms.size() - 1;
}
