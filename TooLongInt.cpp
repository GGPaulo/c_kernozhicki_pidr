#include "too_long.h"

bool TooLong::operator == (const TooLong &other) const {
    return a == other.a && negative == other.negative;
}

bool TooLong::operator != (const TooLong &other) const {
    return a != other.a || negative != other.negative;
}

bool TooLong::operator > (const TooLong &other) const {
    if (a.size() != other.a.size()) return a.size() > other.a.size();
    for (int i = (int) a.size()-1; i >= 0; i--) {
        if (a[i] != other.a[i]) return a[i] > other.a[i];
    }
    return false;
}

bool TooLong::operator < (const TooLong &other) const {
    if (a.size() != other.a.size()) return a.size() < other.a.size();
    for (int i = (int) a.size()-1; i >= 0; i--) {
        if (a[i] != other.a[i]) return a[i] < other.a[i];
    }
    return false;
}

bool TooLong::operator >= (const TooLong &other) const {
    return !(*this < other);
}

bool TooLong::operator <= (const TooLong &other) const {
    return !(*this > other);
}

TooLong TooLong::operator - () const {
    TooLong ret = *this;
    ret.negative = !ret.negative;
    return ret;
}

TooLong TooLong::operator + (const TooLong &other) const {
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

TooLong TooLong::operator - (const TooLong &other) const {
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

TooLong& TooLong::operator += (const TooLong &other) {
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

string TooLong::to_str() const {
    string ret;
    if (negative) ret = '-';

    ret += to_string((long long)a.back());
    for (int i = (int)a.size() - 2; i >= 0; i--) {
        string part = to_string((long long)a[i]);
        while (part.size() < BASE_LOG) part = '0' + part;
        ret += part;
    }

    return ret;
}

ostream& operator << (ostream &os, TooLong &value) {
    os << value.to_str();
    return os;
}

istream& operator >> (istream &is, TooLong &value) {
    string s;
    is >> s;
    value = s;
    return is;
}

TooLong::TooLong(string s) {
    if (!s.empty() && s[0] == '-') {
        negative = true;
        s.erase(0, 1);
    }

    __int128 pwr = 1;
    for (int i = (int) s.size() - 1; i >= 0; i--) {
        if (a.empty() || pwr >= BASE) {
            a.push_back(s[i] - '0');
            pwr = 1;
        } else {
            a.back() = a.back() + (s[i] - '0') * pwr;
        }
        pwr *= 10;
    }
}
