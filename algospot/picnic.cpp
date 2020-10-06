#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int n;
int m;
bool fri[10][10];
bool has_fri[10];
int sel;
int res;

void refresh()
{
    n = 0;
    m = 0;
    sel = 0;
    res = 0;

    memset(fri, 0, sizeof(bool) * 10 * 10);
    memset(has_fri, 0, sizeof(bool) * 10);
}

void get_input()
{
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int a, b;

        cin >> a >> b;

        fri[a][b] = 1;
        fri[b][a] = 1;
    }
}

int find_free()
{
    for (int i = 0; i < n ; ++i) {
        if (!has_fri[i]) {
            return i;
        }
    }

    return -1;
}

int get_nr_cases()
{
    int ret = 0;
    int first_free;

    first_free = find_free();

    if (first_free == -1) {
        return 1;
    }

    for (int i = first_free + 1; i < n; ++i) {

        if (!fri[first_free][i] || has_fri[i]) {
            continue;
        }

        has_fri[first_free] = 1;
        has_fri[i] = 1;

        ret += get_nr_cases();

        has_fri[first_free] = 0;
        has_fri[i] = 0;
    }

    return ret;
}

int main()
{
    freopen("input.txt", "r", stdin);

    int c;

    cin >> c;

    for (int i = 0; i < c; ++i) {
        refresh();

        get_input();

        cout << get_nr_cases() << '\n';
    }

}
