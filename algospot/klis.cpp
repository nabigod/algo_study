#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

int n, k;
vector <int> seq;

int cache[501];
int cache_cnt[501];

void reset_values()
{
    memset(cache, -1, 501 * sizeof(int));
    memset(cache_cnt, -1, 501 * sizeof(int));
    seq.clear();
    n = k = 0;
}

void get_inputs()
{
    int temp;

    cin >> n >> k;

    for (int i = 0; i < n; ++i) {
        cin >> temp;
        seq.push_back(temp);
    }
}

int lis(int start)
{
    int& ret = cache[start+1];

    if (ret != -1) {
        return ret;
    }

    ret = 1;

    for (int next = start + 1; next < n; ++next) {
        if (start == -1 || seq[start] < seq[next]) {
            ret = max(ret, lis(next) + 1);
        }
    }

    return ret;
}

int cnt(int start)
{
    int& ret = cache_cnt[start+1];

    if (lis(start) == 1) {
        return 1;
    }

    if (ret != -1) {
        return ret;
    }

    ret = 0;

    for (int next = start + 1; next < n; ++next) {
        if ((start == -1 || seq[start] < seq[next]) &&
                (lis(start) == lis(next)+1)) {
            ret = min<long long>(INT_MAX, (long long)ret + cnt(next));
        }
    }

    return ret;
}

void rec(int start, int skip, vector <int> &lis_list)
{
    if (start != -1) {
        lis_list.push_back(seq[start]);
    }

    vector <pair <int, int>> fol;

    for (int next = start + 1; next < n; ++next) {
        if ((start == -1 || seq[start] < seq[next]) &&
                (lis(start) == lis(next)+1)) {
            fol.push_back({seq[next], next});
        }
    }

    sort(fol.begin(), fol.end());

    for (int i = 0; i < fol.size(); ++i) {
        int idx = fol[i].second;
        int count = cnt(idx);

        if (count <= skip) {
            skip -= count;
        } else {
            rec(idx, skip, lis_list);
            break;
        }
    }
}

int solve()
{
    vector <int> lis_list;
    //cout << lis(-1) << '\n';
    //cout << cnt(-1) << "\n\n";

    //for (int i = 0; i < n; ++i) {
    //    cout << cnt(i) << " ";
    //}
    //cout << '\n';

    rec(-1, k-1, lis_list);

    //cout << "lis_list size : " << lis_list.size() << '\n';
    cout << lis_list.size() << '\n';
    for (int i = 0; i < lis_list.size(); ++i) {
        cout << lis_list[i] << ' ';
    }
    cout << '\n';

    return 0;
}

int main()
{
    freopen("input.txt", "r", stdin);

    int tc;

    scanf("%d\n", &tc);

    for (int i = 0; i < tc; ++i) {
        reset_values();
        get_inputs();
        solve();
    }
}
