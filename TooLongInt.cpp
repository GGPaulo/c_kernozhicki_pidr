#if __has_include(<bits/stdc++.h>)
    #include <bits/stdc++.h>
#else
    #include "my_lib.h"
#endif

using namespace std;

void file_input() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

class TooLong { public:
    int BASE_LOG = 18; // всегда четный!
    __int128 BASE = 1e18;
    
    vector<__int128> a;
    bool negative = false;
    
    // Перегрузка операторов == != > < >= <=
    
    bool operator == (const TooLong &other) const {
        return a == other.a && negative == other.negative;
    }
    
    bool operator != (const TooLong &other) const {
        return a != other.a || negative != other.negative;
    }
    
    bool operator > (const TooLong &other) const {
        if (a.size() != other.a.size()) return a.size() > other.a.size();
        
        for (int i = (int) a.size()-1; i >= 0; i--) {
            if (a[i] != other.a[i]) return a[i] > other.a[i];
        }
        
        return false;
    }
    
    bool operator < (const TooLong &other) const {
        if (a.size() != other.a.size()) return a.size() < other.a.size();
        
        for (int i = (int) a.size()-1; i >= 0; i--) {
            if (a[i] != other.a[i]) return a[i] < other.a[i];
        }
        
        return false;
    }
    
    bool operator >= (const TooLong &other) const {
        return !(*this < other);
    }
    
    bool operator <= (const TooLong &other) const {
        return !(*this > other);
    }
    
    // Перегрузка операторов (унарный минус) + - / *
    
    TooLong operator - () const {
        TooLong ret = *this;
        ret.negative = !ret.negative;
        return ret;
    }
    
    TooLong operator + (const TooLong &other) const {
        int mx = (int) max(a.size(), other.a.size());
        TooLong ret;
        
        __int128 add = 0;
        for (int i = 0; i < mx; i++) {
            __int128 cur = (i < other.a.size() ? other.a[i] : 0) + (i < a.size() ? a[i] : 0) + add;
            add = cur / BASE;
            ret.a.push_back(cur % BASE);
        }
        
        if (add) ret.a.push_back(add);
        
        return ret;
    }
    
    TooLong operator - (const TooLong &other) const {
        TooLong ret;
        
        __int128 take = 0;
        for (int i = 0; i < min(a.size(), other.a.size()); i++) {
            if (a[i] - take > other.a[i]) {
                ret.a.push_back(a[i] - take - other.a[i]);
                take = 0;
            } else {
                take += other.a[i] - (a[i] - take);
            }
        }
        
        return ret;
    }
    
    TooLong& operator += (const TooLong &other) {
        a.resize(max(a.size(), other.a.size()));
        
        __int128 add = 0;
        for (int i = 0; i < a.size(); i++) {
            __int128 cur = (i < other.a.size() ? other.a[i] : 0) + a[i] + add;
            add = cur / BASE;
            a[i] = cur % BASE;
        }
        
        if (add) a.push_back(add);
        
        return *this;
    }

    // Представление в виде строки, ввод/вывод
    
    string print(const __int128 &x, bool zero_full_flag = 1) const {
        string a = to_string((long long) x);
        if (zero_full_flag) {
            while (a.size() < BASE_LOG) {
                a = '0' + a;
            }
        }
        
        return a;
    }
    
    string to_str() const {
        string ret;
        if (negative) ret = '-';
        
        ret += print(a.back(), 0);
        for (int i = (int) a.size()-2; i >= 0; i--) ret += print(a[i]);
        
        return ret;
    }
    
    friend ostream& operator << (ostream &os, TooLong &value) {
        os << value.to_str();
        return os;
    }
    
    friend istream& operator >> (istream &is, TooLong &value) {
        string s;
        is >> s;
        
        value = s;
        
        return is;
    }
    
    // Экземпляры класса
    
    TooLong (string s = "") {
        if (!s.empty() && s[0] == '-') {
            negative = true;
            s.erase(0, 1);
        }
        
        __int128 pwr = 1;
        for (int i = (int) s.size()-1; i >= 0; i--) {
            if (a.empty() || pwr >= BASE) {
                a.push_back(s[i] - '0');
                pwr = 1;
            } else {
                a.back() = a.back() + (s[i] - '0') * pwr;
            }
            pwr *= 10;
        }
    }
    
    void operator = (string s) {
        if (!s.empty() && s[0] == '-') {
            negative = true;
            s.erase(0, 1);
        }
        
        __int128 pwr = 1;
        for (int i = (int) s.size()-1; i >= 0; i--) {
            if (a.empty() || pwr >= BASE) {
                a.push_back(s[i] - '0');
                pwr = 1;
            } else {
                a.back() = a.back() + (s[i] - '0') * pwr;
            }
            pwr *= 10;
        }
    }
    
    
    template <typename T, typename = enable_if_t<is_integral_v<T>>>
    TooLong (T value) {
        while (value > 0) {
            a.push_back(value % BASE);
            value /= BASE;
        }
    }
    
    template <typename T, typename = enable_if_t<is_integral_v<T>>>
    void operator = (T value) {
        a.clear();
        while (value > 0) {
            a.push_back(value % BASE);
            value /= BASE;
        }
    }
    
    TooLong (const TooLong &other) {
        a = other.a;
        negative = other.negative;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    
    return 0;
}
