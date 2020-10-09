#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int n, m, min_val = 987654321;
char office[9][9];

int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};
int rotate_cnt[] = {0, 4, 2, 4, 4, 1};

typedef struct {
    int type;
    int x;
    int y;
} CAM;

vector < CAM > cam_list;

void add_cam(int x, int y, int type)
{
    CAM *cam;

    cam = new CAM;

    cam->type = type;
    cam->x = x;
    cam->y = y;

    cam_list.push_back(*cam);
}

void refresh()
{
    cam_list.clear();

    for (int i = 0; i < n; ++i) {
        memset(office[i], 0, m);
    }

    n = m = 0;
}

void get_input()
{
    scanf("%d %d\n", &n, &m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%c \n", &office[i][j]);

            if (office[i][j] >= '1' && office[i][j] <= '5') {
                add_cam(j, i, office[i][j] - '0');
            }
        }
    }
}

int calc_blind_spot()
{
    int cnt = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (office[i][j] == '0')
                cnt++;
        }
    }

    return cnt;
}

void check(int dir, CAM cam)
{
    dir = dir % 4;
    int nx, ny;

    nx = cam.x;
    ny = cam.y;

    while (1) {
        nx += dx[dir];
        ny += dy[dir];

        if (nx < 0 || nx >= m || ny < 0 || ny >= n)
            break;

        if (office[ny][nx] == '6')
            break;

        office[ny][nx] = '#';
    }
}

void set_cam(int dir, int cam_idx, CAM cam)
{
    switch (cam_list[cam_idx].type) {
        case 1:
            check(dir, cam_list[cam_idx]);
            break;

        case 2:
            check(dir, cam_list[cam_idx]);
            check(dir + 2, cam_list[cam_idx]);
            break;

        case 3:
            check(dir, cam_list[cam_idx]);
            check(dir + 1, cam_list[cam_idx]);
            break;

        case 4:
            check(dir, cam_list[cam_idx]);
            check(dir + 1, cam_list[cam_idx]);
            check(dir + 2, cam_list[cam_idx]);
            break;

        case 5:
            check(dir, cam_list[cam_idx]);
            check(dir + 1, cam_list[cam_idx]);
            check(dir + 2, cam_list[cam_idx]);
            check(dir + 3, cam_list[cam_idx]);
            break;
    }
}

void dfs(int cam_idx)
{
    char temp_office[9][9];

    if (cam_idx == cam_list.size()) {
        int t = calc_blind_spot();

        min_val = (min_val > t) ? t : min_val;

        return;
    }

    int nr_rotate = rotate_cnt[cam_list[cam_idx].type];

    for (int i = 0; i < nr_rotate; ++i) {
        memcpy(temp_office, office, 9 * 9 * sizeof(char));

        set_cam(i, cam_idx, cam_list[cam_idx]);

        dfs(cam_idx + 1);

        memcpy(office, temp_office, 9 * 9 * sizeof(char));
    }

    return;
}

int main()
{
    freopen("input.txt", "r", stdin);

    for (int i = 0 ; i < 1; ++i) {
        refresh();
        get_input();
        dfs(0);

        printf("%d\n", min_val);
    }

    return 0;
}
