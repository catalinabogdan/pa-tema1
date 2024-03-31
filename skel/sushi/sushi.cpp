#include <bits/stdc++.h>
#include <cstdint>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

int task1(int n, int m, int x, vector <int>& p, vector <vector <int> >& g) {
	int B = n * x;  // buget total
	vector< vector<int> > dp(m+1, vector<int>(B+1, 0));
	vector<int> t_grades(m+1, 0);  // suma notelor penru fiecare produs
	t_grades[0] = 0;
	for ( int j = 0; j < m; j ++ ) {
		int sum = 0;
		for ( int i = 0; i < n; i ++ ) {
			sum += g[i][j];
		}
		t_grades[j] = sum;
	}
	// cazul de baza
	for ( int b = 0; b < B; b ++ ) {
		dp[0][b] = 0;
	}
	// cazul general
	for ( int i = 1; i <= m; i ++ ) {
		for ( int b = 0; b <= B; b ++ ) {
			// daca aleg sa nu cumpar platoul i
			// pastrez cat am cheltuit la iteratia anterioara
			dp[i][b] = dp[i-1][b];
			// daca mai raman bani pt obiectul i
			if (b - p[i-1] >= 0) {
				// sol auxiliara este rez partial cu
				// suma ramasa de cheltuit anterioara - pret platou
				// si adaugam suma notelor obiectului
				int sol_aux = dp[i-1][b - p[i-1]] + t_grades[i-1];
				// alegem solutia cea mai buna dintre rezultatul anterior
				// si sol auxiliara
				dp[i][b] = max(dp[i][b], sol_aux);
			}
		}
	}
	return dp[m][B];
}

int task2(int n, int m, int x, vector <int> &p, vector <vector <int> > &g) {
	int B = n * x;  // buget total
	vector< vector<int> > dp(m + 1, vector<int>(B+1, 0));
	vector<int> t_grades(m + 1, 0);  // suma notelor penru fiecare produs
	t_grades[0] = 0;
	for ( int j = 0; j < m; j ++ ) {
		int sum = 0;
		for ( int i = 0; i < n; i ++ ) {
			sum += g[i][j];
		}
		t_grades[j] = sum;
	}
	// cazul de baza
	for ( int b = 0; b <= B; b ++ ) {
		dp[0][b] = 0;
	}
	for ( int i = 1; i <= m; i ++ ) {
		for ( int b = 0; b <= B; b ++ ) {
			// daca aleg sa nu cumpar platoul i
			// pastrez cat am cheltuit la iteratia anterioara
			dp[i][b] = dp[i-1][b];
			// daca mai raman bani pt obiectul i
			if ( b - p[i-1] >= 0 ) {
				int sol_aux = dp[i-1][b - p[i-1]] + t_grades[i-1];
				dp[i][b] = max(dp[i][b], sol_aux);
				// daca raman bani si este optima cumpararea
				// a unui al doilea platou din acelasi tip
				if ( b - 2 * p[i-1] >= 0 ) {
					int sol_aux2 = dp[i-1][b- (2 * p[i-1])] + 2 * t_grades[i-1];
					dp[i][b] = max(dp[i][b], sol_aux2);
				}
			}
		}
	}
	return dp[m][B];
}

int task3(int n, int m, int x, vector <int> &p, vector <vector <int> > &g) {
	vector<int> t_grades(m + 1, 0);  // suma notelor penru fiecare produs
	t_grades[0] = 0;
	for ( int j = 0; j < m; j ++ ) {
		int sum = 0;
		for ( int i = 0; i < n; i ++ ) {
			sum += g[i][j];
		}
		t_grades[j] = sum;
	}
	int B = n * x;
	vector< vector <vector<int> > > dp;
	dp.assign(m + 1, vector<vector<int> >(B + 1, vector<int>(n + 1, 0)));
	// cazul de baza
	for ( int b = 0; b <= B; b ++ ) {
		dp[0][b][0] = 0;
	}
	for ( int i = 1; i <= m; i ++ ) {
		for ( int b = 0; b <= B; b ++ ) {
			for ( int count = n; count > 1; count -- ) {
			// pentru maxim n platouri
			dp[i][b][count] = dp[i-1][b][count];
			if ( b - p[i-1] >= 0 ) {
				int sol_aux = dp[i-1][b - p[i-1]][count - 1] + t_grades[i-1];
				dp[i][b][count] = max(dp[i][b][count], sol_aux);
				// verificam daca ne avantajeaza si ne permitem sa cumparam
				// doua platouri de acelasi tip
				if ( b - 2 * p[i-1] >= 0 ) {
					int sol_aux2 = dp[i-1][b - (2 * p[i-1])][count - 2] + 2 * t_grades[i-1];
					dp[i][b][count] = max(dp[i][b][count], sol_aux2);
					}
				}
			}
		}
	}
	return dp[m][B][n];
}

int main() {
	freopen("sushi.in", "r", stdin);
	freopen("sushi.out", "w", stdout);

	int task;  // task number

	int n;  // number of friends
	int m;  // number of sushi types
	int x;  // how much each of you is willing to spend

	vector <int> prices;  // prices of each sushi type
	// the grades you and your friends gave to each sushi type
	vector <vector <int> > grades;

	cin >> task;
	cin >> n >> m >> x;

	prices.assign(m, 0);
	grades.assign(n, vector <int> (m, 0));

	// price of each sushi
	for(int i = 0; i < m; ++i) {
		cin >> prices[i];
	}

	// each friends rankings of sushi types
	for ( int i = 0; i < n; ++ i ) {
		for ( int j = 0; j < m; ++ j ) {
			cin >> grades[i][j];
		}
	}

	int ans = -1;

	switch(task) {
		case 1:
			ans = task1(n, m, x, prices, grades);
			break;
		case 2:
			ans = task2(n, m, x, prices, grades);
			break;
		case 3:
			ans = task3(n, m, x, prices, grades);
			break;
		default:
			cout << "wrong task number" << endl;
	}

	cout << ans << endl;

	return 0;
}
