#include <iostream>
#include <cstring>
using namespace std;

struct position {
    int x;
    int y;
};
typedef struct position pos_t;

struct block {
    pos_t pos[3];
};
typedef struct block blk_t;

int c, h, w;
char board[21][21];
blk_t blk_list[] = {
    {{{0, 0}, {1, 0}, {0, 1}}},
    {{{0, 0}, {1, 0}, {1, 1}}},
    {{{0, 0}, {0, 1}, {1, 1}}},
    {{{0, 0}, {0, 1}, {-1, 1}}},
    {{{0, 0}, {-1, 0}, {-1, 1}}},
    {{{0, 0}, {-1, 0}, {-1, 1}}}
};

void refresh()
{
    for (int i = 0; i < h; ++i) {
        memset(board[i], 0, 21);
    }

    h = w = 0;
}

void get_input()
{
    for (int i = 0; i < h; ++i) {
        scanf("%s\n", board[i]);
    }
}

bool is_impossible()
{
    int cnt = 0;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (board[i][j] == '.')
                cnt++;
        }
    }

    return (cnt % 3) != 0;
}

bool find_white(int *x, int *y)
{
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (board[i][j] == '.') {
                *x = j;
                *y = i;

                return true;
            }
        }
    }

    return false;
}

bool is_in_board(int nx, int ny) {
    return nx >= 0 && nx < w && ny >= 0 && ny < h;
}

bool cover(int x, int y, blk_t block)
{
    bool can_cover = true;

    for (int i = 0; i < 3; ++i) {
        int nx = x + block.pos[i].x;
        int ny = y + block.pos[i].y;

        can_cover &= is_in_board(nx, ny) && board[ny][nx] == '.';
    }

    if (can_cover) {
        for (int i = 0; i < 3; ++i) {
            int nx = x + block.pos[i].x;
            int ny = y + block.pos[i].y;

            board[ny][nx] = '#';
        }

        return true;
    }

    return false;
}

bool uncover(int x, int y, blk_t block)
{
    for (int i = 0; i < 3; ++i) {
        int nx = x + block.pos[i].x;
        int ny = y + block.pos[i].y;

        board[ny][nx] = '.';
    }
}

int calc_cases()
{
    int x, y;
    int ret = 0;

    if (find_white(&x, &y)) {
        for (int i = 0; i < 6; ++i) {
            if (cover(x, y, blk_list[i])) {
                ret += calc_cases();
                uncover(x, y, blk_list[i]);
            }
        }
    } else {
        return 1;
    }

    return ret;
}

int solve()
{
    if (is_impossible()) {
        return 0;
    }

    return calc_cases();
}

int main()
{
    freopen("input.txt", "r", stdin);

    scanf("%d\n", &c);

    for (int i = 0; i < c; ++i) {
        refresh();

        scanf("%d %d\n", &h, &w);

        get_input();

        printf("%d\n", solve());
    }

}
