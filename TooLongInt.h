#ifndef TOO_LONG_H
#define TOO_LONG_H

#if __has_include(<bits/stdc++.h>)
    #include <bits/stdc++.h>
#else
    #include "my_lib.h"
#endif

using namespace std;

class TooLong {
public:
    int BASE_LOG = 18;
    __int128 BASE = 1e18;

    vector<__int128> a;
    bool negative = false;

    bool operator == (const TooLong &other) const;
    bool operator != (const TooLong &other) const;
    bool operator > (const TooLong &other) const;
    bool operator < (const TooLong &other) const;
    bool operator >= (const TooLong &other) const;
    bool operator <= (const TooLong &other) const;

    TooLong operator - () const;
    TooLong operator + (const TooLong &other) const;
    TooLong operator - (const TooLong &other) const;
    TooLong& operator += (const TooLong &other);

    string to_str() const;
    friend ostream& operator << (ostream &os, TooLong &value);
    friend istream& operator >> (istream &is, TooLong &value);

    TooLong(string s = "");
    void operator = (string s);

    template <typename T, typename = enable_if_t<is_integral_v<T>>>
    TooLong(T value);
    
    template <typename T, typename = enable_if_t<is_integral_v<T>>>
    void operator = (T value);

    TooLong (const TooLong &other);
};

#endif

