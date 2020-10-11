#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

string pattern;
vector <string> names;

void refresh()
{
    pattern = "";

    names.clear();
}

void get_input()
{
    int n;

    cin >> pattern >> n;

    for (int i = 0; i < n; ++i) {
        string temp;

        cin >> temp;
        names.push_back(temp);
    }
}

bool are_match(string p, string w)
{
    int pos = 0;

    while ( pos < p.size() &&
            pos < w.size() &&
            (p[pos] == w[pos] || p[pos] == '?')) {
        pos++;
    }

    if (pos == p.size() && pos == w.size()) {
        return true;
    }

    if (p[pos] == '*') {
        for (int i = 0; i <= w.size()-pos; ++i) {
            if (are_match(p.substr(pos+1), w.substr(pos+i))) {
                return true;
            }
        }
    }

    return false;
}


void solve()
{
    vector <string> ans;

    for (int i = 0; i < names.size(); ++i) {
        if (are_match(pattern, names[i])) {
            ans.push_back(names[i]);
        }
    }

    sort(ans.begin(), ans.end());

    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << '\n';
    }
}

int main()
{
    freopen("input.txt", "r", stdin);

    int tc;

    cin >> tc;

    for (int i = 0; i < tc; ++i) {
        refresh();
        get_input();
        solve();
    }

}
