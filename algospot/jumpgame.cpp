#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int n;
int board[100][100];
bool visited[100][100];

void refresh()
{
    memset(board, 0, 100*100);
    memset(visited, 0, 100*100);
    n = 0;
}

void get_input()
{
    scanf("%d\n", &n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d \n", &board[i][j]);
        }
    }
}

bool is_valid_pos(int x, int y)
{
    return x >= 0 && x < n && y >= 0 && y < n;
}

void push_next(vector <pair <int, int>> &nodes)
{
    pair <int, int> p = nodes.back();

    nodes.pop_back();

    int x = p.first;
    int y = p.second;
    int d = board[y][x];

    if (visited[n-1][n-1]) {
        nodes.clear();
        return;
    }

    if (is_valid_pos(x + d, y) && !visited[y][x + d]) {
        visited[y][x + d] = true;
        nodes.push_back({x + d, y});
    }

    if (is_valid_pos(x, y + d) && !visited[y + d][x]) {
        visited[y + d][x] = true;
        nodes.push_back({x, y + d});
    }
}

void solve()
{
    pair <int, int> node;
    vector <pair<int, int>> nodes;

    nodes.push_back({0, 0});

    while (nodes.size()) {
        push_next(nodes);
    }
}

int main()
{
    //freopen("input.txt", "r", stdin);

    int tc;

    scanf("%d\n", &tc);

    for (int i = 0 ; i < tc; ++i) {
        refresh();
        get_input();
        solve();

        printf("%s\n", visited[n-1][n-1] ? "YES" : "NO");
    }
}
