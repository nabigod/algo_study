#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

typedef struct item {
    string name;
    int vol;
    int need;
} item_t;

int n, w;
int dp[1001][101];
vector <item_t *> item_list;
vector <int> picked;

void reset_values()
{
    for (int i = 0; i < item_list.size(); ++i) {
        delete item_list[i];
    }
    item_list.clear();
    picked.clear();

    memset(dp, -1, 1001 * 101 * sizeof(int));

    n = w = 0;
}

void get_inputs()
{
    cin >> n >> w;

    for (int i = 0; i < n; ++i) {
        item_t *item = new item_t;

        cin >> item->name >> item->vol >> item->need;

        item_list.push_back(item);
    }
}

int solve(int remain_w, int idx)
{
    int ret = 0;

    if (idx == n) {
        return 0;
    }

    if (dp[remain_w][idx] != -1) {
        return dp[remain_w][idx];
    }

    ret = solve(remain_w, idx + 1);

    if (remain_w >= item_list[idx]->vol) {
        ret = max(ret, solve(remain_w - item_list[idx]->vol, idx + 1) + item_list[idx]->need);
    }

    dp[remain_w][idx] = ret;

    return ret;
}

void reconstruct(int remain_w, int idx)
{
    if (idx == n) {
        return;
    }

    if (solve(remain_w, idx) == solve(remain_w, idx+1)) {
        reconstruct(remain_w, idx+1);
    } else {
        picked.push_back(idx);
        reconstruct(remain_w - item_list[idx]->vol, idx+1);
    }
}

int main()
{
    freopen("input.txt", "r", stdin);

    int tc;

    scanf("%d\n", &tc);

    for (int i = 0; i < tc; ++i) {
        reset_values();
        get_inputs();
        cout << solve(w, 0) << ' ';

        reconstruct(w, 0);

        cout << picked.size() << '\n';

        for (int i = 0; i < picked.size(); ++i) {
            cout << item_list[picked[i]]->name << '\n';
        }
    }
}
