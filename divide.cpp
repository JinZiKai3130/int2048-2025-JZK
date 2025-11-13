int2048 &int2048::operator/=(const int2048 &other) {
    // 先找出除数的长度，在v中找到对应长度截出对应长度，再去剪掉除数的i倍，存储这一位答案，原数*10，再进行一次
    int2048 ans;
    if (negative == other.negative) {
        negative = false;
    }
    else {
        negative = true;
    }
    if (v.empty()) { // 特判0
        negative = false;
        return *this;
    }
    int2048 tmp;
    tmp.negative = false;
    bool flag = false;
    for (int i = v.size() - 1; i >= 0; i--) {
        tmp *= mod; tmp += v[i]; // 每次往里面放入下一个
        while (tmp.v.size() >= 1 && tmp.v.back() == 0) { // 清空前导0
            tmp.v.pop_back();
        }
        if (tmp < other) { // 如果当前被除数不够大
            if (flag) {
                ans.v.push_back(0);
                continue;
            }
            else continue;
        }
        flag = true;
        long long l = 1, r = 1e9;
        long long mid;
        int2048 t;
        while (l < r) {
            mid = l + (r - l + 1) / 2;
            t = mid * other;
            t.negative = false;
            if (t <= tmp) {
                l = mid;
            }
            else {
                r = mid - 1;
            }
        }
        ans.v.push_back(l);

        t = int2048(l) * other;
        t.negative = false;
        tmp -= t;
        
        while (tmp.v.size() >= 1 && tmp.v.back() == 0) { // 清空前导0
            tmp.v.pop_back();
        }
    }
    
    while (tmp.v.size() >= 1 && tmp.v.back() == 0) { // 清空前导0
        tmp.v.pop_back();
    }
    v.clear();
    for (int i = ans.v.size() - 1; i >= 0; i--) { // 重新赋值
        v.push_back(ans.v[i]);
    }
    if (negative && !tmp.v.empty()) { // 负数判断
        *this -= 1;
    }
    return *this;
}