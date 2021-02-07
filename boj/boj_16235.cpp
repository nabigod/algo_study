#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class land_info {
    public:
        int meal;
        vector <pair<int, int>> trees; // age, status;
};

int n, m, k;
int supply[10][10];
vector <vector <land_info>> land;

void reset_values()
{
    land.clear();

    n = m = k = 0;
}

void dump_status()
{
    cout << n << ' ' << m << ' ' << k << '\n';
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << land[i][j].meal << ' ';
        }

        cout << '\n';
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < land[i][j].trees.size(); ++k) {
                cout << i << ' ' << j << ' ';
                cout << land[i][j].trees[k].first;
                cout << ' '<< land[i][j].trees[k].second;
                cout << '\n';
            }
        }
    }
}

void get_inputs()
{
    cin >> n >> m >> k;

    land.resize(n);
    for (int i = 0; i < n; ++i) {
        land[i].resize(n);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> supply[i][j];
            land[i][j].meal = 5;
        }
    }

    for (int i = 0; i < m; ++i) {
        int x, y, z;

        cin >> x >> y >> z;
        land[x-1][y-1].trees.push_back({z, 1});
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            sort(land[i][j].trees.begin(), land[i][j].trees.end());
        }
    }
}

void add_tree(int x, int y)
{
    if (x < 0 || x >= n || y < 0 || y >= n) {
        return;
    }

    land[y][x].trees.push_back({1, 1});
}

int solve()
{
    for (int year = 0; year < k; ++year) {
        // spring
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int t = 0; t < land[i][j].trees.size(); ++t) {
                    if (land[i][j].meal >= land[i][j].trees[t].first){
                        land[i][j].meal -= land[i][j].trees[t].first;
                        land[i][j].trees[t].first++;
                    } else {
                        land[i][j].trees[t].second = 0;
                    }
                }
            }
        }

        // summer
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int t = 0; t < land[i][j].trees.size(); ++t) {
                    if (land[i][j].trees[t].second == 0){
                        land[i][j].meal += land[i][j].trees[t].first/2;
                    }
                }

                for (int t = land[i][j].trees.size()-1; t >= 0; --t) {
                    if (land[i][j].trees[t].second == 0){
                        land[i][j].trees.erase(land[i][j].trees.begin() + t);
                    }
                }
            }
        }

        // fall
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int t = 0; t < land[i][j].trees.size(); ++t) {
                    if ((land[i][j].trees[t].first % 5) == 0){
                        add_tree(j-1, i-1);
                        add_tree(j, i-1);
                        add_tree(j+1, i-1);
                        add_tree(j-1, i);
                        add_tree(j+1, i);
                        add_tree(j-1, i+1);
                        add_tree(j, i+1);
                        add_tree(j+1, i+1);
                    }
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                sort(land[i][j].trees.begin(), land[i][j].trees.end());
            }
        }

        // winter
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                land[i][j].meal += supply[i][j];
            }
        }

        //dump_status();
    }

    int ret = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int t = 0; t < land[i][j].trees.size(); ++t) {
                if (land[i][j].trees[t].second){
                    ret++;
                }
            }
        }
    }

    return ret;
}

int main()
{
    freopen("input.txt", "r", stdin);

    //int tc;

    //scanf("%d\n", &tc);

    //for (int i = 0; i < tc; ++i) {
        reset_values();
        get_inputs();
        cout << solve() << '\n';
    //}
}
