#include <bits/stdc++.h>
#include <cstdint>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

const int mod = 1000000007;
int comb(int n, int y) {
	vector< vector<int> > dp(n + 1, vector<int>(y + 1));
	// cazurile de baza
	// oricare ar fi n, daca y este 0 atunci
	// combinari de n luate cate 0 = 0
	for (int i = 0; i <= n; i ++) {
		dp[i][0] = 1;
	}
	// combinari de 0 luate cate y = 0
	for (int j = 1; j <= y; j ++) {
		dp[0][j] = 0;
	}
	// combinari de n luate cate y =
	// combinari de n - 1 luate cate y - 1 + combinari de n - 1 luate cate y
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= y; j ++) {
			dp[i][j] = ((dp[i - 1][j - 1] % mod) + (dp[i - 1][j] % mod)) % mod;
		}
	}
	return dp[n][y] % mod;
}
int type1(int x, int y) {
	// tratam cazurile de baza
	if (y > (x + 1)) {
		return 0;
	}
	if (y == 0 || y == (x + 1) || (x + 1) == 0) {
		return 1;
	}
	if (y == 1) {
		return (x + 1);
	}
	// pentru a nu a nu avea 2 de 1 consecutiv
	// fiecare trebuie sa aiba in stanga si dreapta un 0
	// -> x + 1 pozitii posibile in care pot fi asezati y de 1
	return comb(x + 1, y);
}

int type2(int x, int y) {
    return 0;
}

int main() {
    freopen("semnale.in", "r", stdin);
	freopen("semnale.out", "w", stdout);

	int sig_type, x, y;

	cin >> sig_type >> x >> y;

    switch (sig_type) {
		case 1:
			cout << type1(x, y);;
			break;
		case 2:
			cout << type2(x, y);
			break;
		default:
			cout << "wrong task number" << endl;
	}

    return 0;
}
