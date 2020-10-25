#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int dp[10000];
string str;

void reset_values()
{
    str.clear();
    memset(dp, -1, 10000 * sizeof(int));
}

void get_inputs()
{
    cin >> str;
}

int get_difficulty(string s)
{
    bool flag = true;

    if (s == string(s.size(), s[0]))
        return 1;

    for (int i = 1; i < s.size(); ++i) {
        if (s[i] - s[i-1] != s[1] - s[0]) {
            flag = false;
        }
    }

    if (flag && abs(s[1] - s[0]) == 1)
        return 2;

    bool flag2 = true;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] != s[i%2])
            flag2 = false;
    }

    if (flag2) return 4;

    if (flag) return 5;

    return 10;
}

int solve(int idx)
{
    if (idx == str.size()) {
        return 0;
    }

    if (dp[idx] != -1)
        return dp[idx];

    int mmin = 987654321;

    for (int i = 3; i <= 5; ++i) {
        if (str.size() >= idx + i) {
            mmin = min(mmin, get_difficulty(str.substr(idx, i))
                             + solve(idx+i));
        }
    }

    dp[idx] = mmin;

    return mmin;
}

int main()
{
    freopen("input.txt", "r", stdin);

    int tc;

    cin >> tc;

    for (int i = 0; i < tc; ++i) {
        reset_values();
        get_inputs();
        cout << solve(0) << "\n";
    }
}
