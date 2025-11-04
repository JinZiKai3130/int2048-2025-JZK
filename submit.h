#pragma once
#ifndef SJTU_BIGINTEGER
#define SJTU_BIGINTEGER

// your hpp source code
#include <complex>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

// 请不要使用 using namespace std;

namespace sjtu {
class int2048 {
  // todo
  std::vector<int> v;
  bool negative;
  const long long mod = 1e9;
  const int mod_num = 9;
public:
  // 构造函数
  int2048();
  int2048(long long);
  int2048(const std::string &);
  int2048(const int2048 &);

  // 以下给定函数的形式参数类型仅供参考，可自行选择使用常量引用或者不使用引用
  // 如果需要，可以自行增加其他所需的函数
  template <typename T>
  void checkCarry(std::vector<T> &, int, T &);
  void minusCheck(int2048 &, int2048 &);
  void checkBorrow(std::vector<int> &, int, int &);
  bool abscmp(std::vector<int> &, std::vector<int> &);
  // ===================================
  // Integer1
  // ===================================

  // 读入一个大整数
  void read(const std::string &);
  // 输出储存的大整数，无需换行
  void print();
  // 加上一个大整数
  int2048 &add(const int2048 &);
  // 返回两个大整数之和
  friend int2048 add(int2048, const int2048 &);

  // 减去一个大整数
  int2048 &minus(const int2048 &);
  // 返回两个大整数之差
  friend int2048 minus(int2048, const int2048 &);

  // ===================================
  // Integer2
  // ===================================

  int2048 operator+() const;
  int2048 operator-() const;

  int2048 &operator=(const int2048 &);

  int2048 &operator+=(const int2048 &);
  friend int2048 operator+(int2048, const int2048 &);

  int2048 &operator-=(const int2048 &);
  friend int2048 operator-(int2048, const int2048 &);

  int2048 &operator*=(const int2048 &);
  friend int2048 operator*(int2048, const int2048 &);

  int2048 &operator/=(const int2048 &);
  friend int2048 operator/(int2048, const int2048 &);

  int2048 &operator%=(const int2048 &);
  friend int2048 operator%(int2048, const int2048 &);

  friend std::istream &operator>>(std::istream &, int2048 &);
  friend std::ostream &operator<<(std::ostream &, const int2048 &);

  friend bool operator==(const int2048 &, const int2048 &);
  friend bool operator!=(const int2048 &, const int2048 &);
  friend bool operator<(const int2048 &, const int2048 &);
  friend bool operator>(const int2048 &, const int2048 &);
  friend bool operator<=(const int2048 &, const int2048 &);
  friend bool operator>=(const int2048 &, const int2048 &);
};
} // namespace sjtu

// your cpp source code
namespace sjtu {

int2048::int2048() : negative(false) {
    v.clear();
}

int2048::int2048(long long a) : negative(false) {
    long long tmp = a, curr_num;
    // step: the level of current num
    // cnt: the current digit
    if (tmp < 0) {
        tmp = -tmp;
        negative = true;
    }
    while (tmp != 0) {
        curr_num = tmp % mod;
        tmp /= mod;
        v.push_back(curr_num);
    }
}

int2048::int2048(const std::string &s) : negative(false) {
    int len = s.size();
    // std::cerr << "len = " << len << '\n';
    if (s[0] == '-') {
        negative = true;
    }
    int tmp, cnt;
    bool flag = false;
    for (int i = len - 1; i >= static_cast<int>(negative); i -= mod_num) {
        tmp = 0, cnt = 1;
        for (int j = i; j > std::max(i - mod_num, static_cast<int>(negative) - 1); j--) {
            flag |= static_cast<int>(s[j] - '0');
            tmp += static_cast<int>(s[j] - '0') * cnt;
            cnt *= 10;
            // std::cerr << "tmp = " << tmp << std::endl;
        }
        if (flag)
        v.push_back(tmp);
    }
    if (!flag) {
        negative = false;
    }
}

int2048::int2048(const int2048 &tmp) : v(tmp.v), negative(tmp.negative) {
}

void int2048::read(const std::string &s) {
    v.clear();
    negative = false;
    int len = s.size();
    if (s[0] == '-') {
        negative = true;
    }
    int tmp, cnt;
    bool flag = false;
    for (int i = len - 1; i >= static_cast<int>(negative); i -= mod_num) {
        tmp = 0, cnt = 1;
        for (int j = i; j > std::max(i - mod_num, static_cast<int>(negative) - 1); j--) {
            flag |= static_cast<int>(s[j] - '0');
            tmp += static_cast<int>(s[j] - '0') * cnt;
            cnt *= 10;
            // std::cerr << "tmp = " << tmp << std::endl;
        }
        if (flag)
        v.push_back(tmp);
    }
    if (!flag) {
        negative = false;
    }
}

void int2048::print() {
    if (!v.size()) {
        std::cout << 0;
        return;
    }
    if (negative) {
        if (v.size() == 1 && v[0] == 0) {
            std::cout << 0;
            return;
        }
        std::cout << '-';
    }
    for (int i = v.size() - 1; i >= 0; i--) {
        if (i != v.size() - 1) {
            long long tmp = mod / 10;
            while(true) {
                if (v[i] / tmp == 0) std::cout << 0;
                else break;
                tmp /= 10;
            }
        }
        std::cout << v[i];
    }
}

template <typename T>
void int2048::checkCarry(std::vector<T> &vt, int i, T &carry_over) {
    unsigned long long tmp;
    tmp = vt[i] + carry_over; // the change
    carry_over = tmp / mod;
    vt[i] = tmp % mod;
    /*
    T tmp = vt[i] / mod;
    vt[i] %= mod;
    vt[i] += carry_over;
    tmp += vt[i] / mod;
    carry_over = tmp;
    */
}

int2048 &int2048::add(const int2048 &other) {
    if (negative != other.negative) {
        int2048 tmp = other;
        tmp.negative = negative;
        // std::cout << "xxx " << this->v[0] << " " << tmp.v[0] << std::endl;
        this->minus(tmp);
        return *this;
    }
    int len1 = v.size(), len2 = other.v.size();
    int carry_over = 0;
    // std::cout << "myfault" << std::endl;
    for (int i = 0 ; i < std::min(len1, len2); i++) {
        v[i] += other.v[i];
        checkCarry(v, i, carry_over);
    }
    if (len2 > len1) {
        for (int i = len1; i < len2; i++) {
            v.push_back(other.v[i]);
            checkCarry(v, i, carry_over);
        }
    }
    // std::cerr << "xxx " << this->v[0] << " " << other.v[0] << std::endl;
    if (carry_over) {
        for (int i = len2; i < len1; i++) {
            checkCarry(v, i, carry_over);
        }
        if (carry_over) { // carry to createnew data
            v.push_back(carry_over);
        }
    }
    return *this;
}

int2048 add(int2048 add_1, const int2048 &add_2) {
    return add_1.add(add_2);
}

bool int2048::abscmp(std::vector<int> &v1, std::vector<int> &v2) {
    // std::cout << v1.size() << " size " << v2.size() << std::endl;
    if (v1.size() != v2.size()) {
        return v1.size() < v2.size();
    }
    else {
        for (int i = v1.size() - 1; i >= 0; i--) {
            if (v1[i] != v2[i]) {
                return v1[i] < v2[i];
            }
        }
    }
    return false;
}

void int2048::minusCheck(int2048 &a1, int2048 &a2) {
    // need further confirm
    bool flag;
    if (a1.negative) { // both negative numbers
        if (abscmp(a2.v, a1.v)) { // 加得比较少
            a1.negative = true;
            flag = false;
        }
        else {
            a1.negative = false;
            flag = true;
        }
    }
    else { // both positive numbers
        if (abscmp(a1.v, a2.v)) { // 减得比较多
            a1.negative = true;
            flag = true;
        }
        else {
            a1.negative  = false;
            flag = false;
        }
    }
    // std::cout << " xxx " << std::endl;
    if (flag) {
        int2048 tmp = a2;
        a2 = a1;
        a1 = tmp;
        a1.negative = a2.negative;
    }
}

void int2048::checkBorrow(std::vector<int> &v, int i, int &borrow) {
        if (borrow != 0) {
            v[i] -= borrow;
        }
        borrow = ((v[i] + mod) / mod) ^ 1;
        v[i] = (v[i] + mod) % mod;
        // std::cout << "todoborrow " << this->v.size() << std::endl;
}

int2048 &int2048::minus(const int2048 &other) {
    int2048 tmp = other;
    if (negative != other.negative) {
        tmp.negative = negative;
        this->add(tmp);
        return *this;
    }
    
    minusCheck(*this, tmp);
    // std::cout << v[0] << " " << tmp.v[0] << std::endl;
    // std::cout << "todo " << this->v.size() << " " << tmp.v.size() << std::endl;
    // this->print();
    // std::cout << std::endl;
    // tmp.print();
    // std::cout << std::endl;
    int borrow = 0;
    // std::cout << "todo " << this->v.size() << " " << tmp.v.size() << std::endl;
    for (int i = 0; i < v.size(); i++) {
        if (i < tmp.v.size()) {
            v[i] -= tmp.v[i];
        }
        // std::cout << "Anothertodo " << this->v[0] << " " << tmp.v[0] << std::endl;
        checkBorrow(v, i, borrow);
    }
    // std::cout << "anothertodo " << this->v[0] << std::endl;
    if (v[v.size() - 1] == 0) v.pop_back();
    return *this;
}

int2048 minus(int2048 to_be_subtracted, const int2048 &subtract) {
    return to_be_subtracted.minus(subtract);
}

int2048 int2048::operator+() const {
    return *this;
}

int2048 int2048::operator-() const {
    int2048 tmp = *this;
    if (!tmp.v.size()) return tmp;
    else {
        tmp.negative ^= 1;
        return tmp;
    }
}

int2048 &int2048::operator=(const int2048 &other) {
    v = other.v;
    negative = other.negative;
    return *this;
}

int2048 &int2048::operator+=(const int2048 &other) {
    return this->add(other);
}

int2048 operator+(int2048 a1, const int2048 &a2) {
    return a1.add(a2);
}

int2048 &int2048::operator-=(const int2048 &other) {
    return this->minus(other);
}

int2048 operator-(int2048 a1, const int2048 &a2) {
    return a1.minus(a2);
}

int2048 &int2048::operator*=(const int2048 &other) {
    if (negative == other.negative) {
        negative = false;
    }
    else {
        negative = true;
    }

    if (!v.size() || !other.v.size()) {
        v.clear();
        negative = false;
        return *this;
    }
    std::vector<long long> result;
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < other.v.size(); j++) {
            if (i + j >= result.size()) {
                result.push_back(static_cast<long long>(v[i]) * static_cast<long long>(other.v[j]));
            }
            else {
                result[i + j] += static_cast<long long>(v[i]) * static_cast<long long>(other.v[j]);
            }
        }
    }
    long long carry_over = 0;
    for (int i = 0; i < result.size(); i++) {
        checkCarry(result, i, carry_over);
    }
    if (carry_over) {
        result.push_back(carry_over);
    }
    v.clear();
    for (int i = 0; i < result.size(); i++) {
        this->v.push_back(result[i]);
    }
    return *this;
}

int2048 operator*(int2048 a1, const int2048 &a2) {
    a1 *= a2;
    return a1;
}

int2048 &int2048::operator/=(const int2048 &otherconst) {
    // 先找出除数的长度，在v中找到对应长度截出对应长度，再去剪掉除数的i倍，存储这一位答案，原数*10，再进行一次
    int2048 ans;
    if (negative == otherconst.negative) {
        ans.negative = false;
    }
    else {
        ans.negative = true;
    }
    int2048 tmp, other = otherconst;
    tmp.v.clear();
    tmp.negative = false;
    other.negative = false;
    bool flag = false;
    for (int i = v.size() - 1; i >= 0; i--) {
        int cnt = 0;
        tmp.v.insert(tmp.v.begin(), v[i]);
        if (tmp < other) {
            if (flag) {
                ans.v.insert(ans.v.begin(), 0);
            }
            else continue;
        }

        while (tmp >= other) {
            tmp -= other;
            cnt++;
        }
        if (cnt > 0) {
            ans.v.insert(ans.v.begin(), cnt);
            flag = true;
        }
    }
    *this = ans;
    return *this;
}

int2048 operator/(int2048 a1, const int2048 &a2) {
    a1 /= a2;
    return a1;
}

bool operator==(const int2048 &a1, const int2048 &a2) {
    if (a1.negative != a2.negative) return false;
    if (a1.v.size() != a2.v.size()) return false;
    for (int i = a1.v.size() - 1; i >= 0; i++) {
        if (a1.v[i] != a2.v[i]) return false;
    }
    return true;
}

bool operator!=(const int2048 &a1, const int2048 &a2) {
    return !(a1 == a2);
}

bool operator<(const int2048 &a1, const int2048 &a2) {
    if (a1.negative && !a2.negative) return true;
    if (!a1.negative && a2.negative) return false;
    if (!a1.negative && !a2.negative) {
        if (a1.v.size() != a2.v.size()) {
            return a1.v.size() < a2.v.size();
        }
        else {
            return a1.v[a1.v.size() - 1] < a2.v[a2.v.size() - 1];
        }
        return false;
    }
    if (a1.negative && a2.negative) {
        if (a1.v.size() != a2.v.size()) {
            return a1.v.size() > a2.v.size();
        }
        else {
            return a1.v[a1.v.size() - 1] > a2.v[a2.v.size() - 1];
        }
        return false;
    }
    return false;
}

bool operator<=(const int2048 &a1, const int2048 &a2) {
    return (a1 < a2) | (a1 == a2);
}

bool operator>=(const int2048 &a1, const int2048 &a2) {
    return !(a1 < a2);
}

bool operator>(const int2048 &a1, const int2048 &a2) {
    return !(a1 <= a2);
}

std::istream &operator>>(std::istream &is, int2048 &input) {
    std::string s;
    is >> s;
    input.read(s);
    return is;
}

std::ostream &operator<<(std::ostream &os, const int2048 &ans) {
    int2048 tmp = ans;
    
    std::streambuf* original_cout_buf = std::cout.rdbuf();
    std::cout.rdbuf(os.rdbuf());
    tmp.print();
    std::cout.rdbuf(original_cout_buf);

    return os;
}

} // namespace sjtu


#endif