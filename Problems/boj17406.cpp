//Problem Number : 17406
//Problem Title : None
//Problem Link : https://www.acmicpc.net/problem/17406

#include <iostream>
#include <algorithm>

#define INF 1234567890

using namespace std;

int n, m, k;
int a[55][55];
int tmp[55][55];
int rcs[11][3];
int check[11];
int tt[6];

const int goY[] = { 1,0,-1,0 };
const int goX[] = { 0,1,0,-1 };

void rotate(int r, int c, int s)
{
	for (int i = 1; i <= s; i++) {
		int y = r - i;
		int x = c - i;
		int t = tmp[y][x];
		int l = i * 2;

		for (int j = 0; j < 4; j++) {
			for (int ii = 0; ii < l; ii++) {
				int yy = y + goY[j];
				int xx = x + goX[j];

				tmp[y][x] = tmp[yy][xx];

				y = yy;
				x = xx;
			}
		}
		tmp[y][x + 1] = t;
	}
}

int calcul(void)
{
	int ret = INF;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			tmp[i][j] = a[i][j];
		}
	}

	for (int i = 0; i < k; i++) {
		int order = tt[i];
		rotate(rcs[order][0], rcs[order][1], rcs[order][2]);
	}
	
	for (int i = 1; i <= n; i++) {
		int t = 0;
		for (int j = 1; j <= m; j++) {
			t += tmp[i][j];
		}
		ret = min(ret, t);
	}

	return ret;
}

int findMin(int idx)
{
	int ret = INF;
	if (idx == k) {
		return calcul();
	}

	for (int i = 0; i < k; i++) {
		if (check[i]) continue;
		check[i] = 1;
		tt[idx] = i;
		ret = min(ret, findMin(idx + 1));
		check[i] = 0;
	}

	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> a[i][j];
		}
	}
	
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> rcs[i][j];
		}
	}

	cout << findMin(0);

	return 0;
}