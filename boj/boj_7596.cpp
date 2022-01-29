#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

#define NR_NEXT 6

struct pos {
    int x;
    int y;
    int z;
};

queue <struct pos> q;

int n, m, h;
// m - horizontal
// n - vertical
// h - height
int visited[100][100][100];
int tomatos[100][100][100];
int dx[NR_NEXT] = {-1, 1, 0, 0, 0, 0};
int dy[NR_NEXT] = {0, 0, -1, 1, 0, 0};
int dz[NR_NEXT] = {0, 0, 0, 0, -1, 1};

void reset_values()
{
    n = m = h = 0;

    memset(tomatos, 0, 100 * 100 * 100 * sizeof(int));
    memset(visited, 0, 100 * 100 * 100 * sizeof(int));
}

void get_inputs()
{
    cin >> m >> n >> h;

    for (int hei = 0; hei < h; ++hei) {
        for (int ver = 0; ver < n; ++ver) {
            for (int hor = 0; hor < m; ++hor) {
                cin >> tomatos[hei][ver][hor];

                if (tomatos[hei][ver][hor] == 1) {
                    visited[hei][ver][hor] = 1;
                    q.push({hor, ver, hei});
                }
            }
        }
    }
}

bool check_status()
{
   for (int hei = 0; hei < h; ++hei) {
        for (int ver = 0; ver < n; ++ver) {
            for (int hor = 0; hor < m; ++hor) {
                if (tomatos[hei][ver][hor] == 0)
                    return false;
            }
        }
    }

   return true;
}

bool is_valid_pos(int x, int y, int z)
{
    bool ret = ((x < m) && (x >= 0)) &&
               ((y < n) && (y >= 0)) &&
               ((z < h) && (z >= 0));

    return ret;
}

int one_day(int q_sz)
{
    struct pos *p;

    for (int i = 0; i < q_sz; ++i) {
        p = new struct pos;
        //printf("%d\n", i);

        *p = q.front();
        q.pop();

        for (int j = 0; j < NR_NEXT; ++j) {
            int nx = p->x + dx[j];
            int ny = p->y + dy[j];
            int nz = p->z + dz[j];

            if (is_valid_pos(nx, ny, nz)) {
                if (tomatos[nz][ny][nx] == 0 && visited[nz][ny][nx] == 0) {
                    tomatos[nz][ny][nx] = 1;
                    visited[nz][ny][nx] = 1;
                    q.push({nx, ny, nz});
                }
            }
        }
    }

    return 0;
}

int solve()
{
    int days = -1;

    while (!q.empty()) {
#if 0
        printf("day %d -------- \n", days);
        for (int hei = 0; hei < h; ++hei) {
            for (int ver = 0; ver < n; ++ver) {
                for (int hor = 0; hor < m; ++hor) {
                    cout << tomatos[hei][ver][hor] << " ";
                }
                cout << endl;
            }
        }
        printf("---------------- \n");
#endif
        one_day(q.size());
        days++;
    }

    if (check_status() == false) {
        days = -1;
    }

    return days;
}

int main(void)
{
    freopen("input.txt", "r", stdin);

    int tc;

    //scanf("%d\n", &tc);

    //for (int i = 0; i < tc; ++i) {
        reset_values();
        get_inputs();
        cout << solve() << endl;
    //}

        return 0;
}
