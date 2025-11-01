#include "include/int2048.h"
#include <vector>

namespace sjtu {

int2048::int2048() : negative(false) {
    v.clear();
    v.push_back(0);
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
    if (s[0] == '0') {
        v.push_back(0);
        return;
    }
    if (s[0] == '-') {
        negative = true;
        if(s[1] == '0') {
            v.push_back(0);
            negative = false;
            return;
        }
    }
    int tmp, cnt;
    for (int i = len - 1; i >= static_cast<int>(negative); i -= mod_num) {
        tmp = 0, cnt = 1;
        for (int j = i; j > std::max(i - mod_num, static_cast<int>(negative) - 1); j--) {
            tmp += static_cast<int>(s[j] - '0') * cnt;
            cnt *= 10;
            // std::cerr << "tmp = " << tmp << std::endl;
        }
        if (tmp != 0)
        v.push_back(tmp);
    }
}

int2048::int2048(const int2048 &tmp) : v(tmp.v), negative(tmp.negative) {
}

void int2048::read(const std::string &s) {
    v.clear();
    negative = false;
    int len = s.size();
    if (s[0] == '0') {
        v.push_back(0);
        return;
    }
    if (s[0] == '-') {
        negative = true;
        if(s[1] == '0') {
            v.push_back(0);
            negative = false;
            return;
        }
    }
    int tmp, cnt;
    for (int i = len - 1; i >= static_cast<int>(negative); i -= mod_num) {
        tmp = 0, cnt = 1;
        for (int j = i; j > std::max(i - mod_num, static_cast<int>(negative) - 1); j--) {
            tmp += static_cast<int>(s[j] - '0') * cnt;
            cnt *= 10;
            // std::cerr << "tmp = " << tmp << std::endl;
        }
        if (tmp != 0)
        v.push_back(tmp);
    }
}

void int2048::print() {
    if (negative) {
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


} // namespace sjtu
