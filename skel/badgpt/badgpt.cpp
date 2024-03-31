#include <bits/stdc++.h>
#include <cstdint>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

#define MOD 1000000007
using namespace std;

void multiply_m(int64_t A[3][3], int64_t B[3][3], int64_t C[3][3]) {
    int64_t aux[3][3];
    for ( int i = 0; i < 3; ++ i ) {
        for ( int j = 0; j < 3; ++j ) {
            int64_t s = 0;
            for ( int k = 0; k < 3; ++ k ) {
                s = s + 1LL * (A[i][k] * B[k][j]) % MOD;
            }
            aux[i][j] = s % MOD;
        }
    }
    memcpy(C, aux, sizeof(aux));
}

void power_m(int64_t AUX[3][3], int64_t n, int64_t REZ[3][3]) {
    // matricea identitate I 1 0 0 | 0 1 0 | 0 0 1
    int64_t I[3][3];
    for ( int i = 0; i < 3; ++ i ) {
        for ( int j = 0; j < 3; ++j ) {
            I[i][j] = (i == j) ? 1 : 0;
        }
    }
    // A^n = 1 DACA n=0 || A*A^(n-1) daca n impar || (A^(n/2))^2 daca n e par
    while (n != 1) {
        if ( n % 2 == 0 ) {
            multiply_m(AUX, AUX, AUX);  // aux devine AUX*AUX
            n = n / 2;
        } else {
            multiply_m(I, AUX, I);  // I devine I*AUX
            -- n;
        }
    }
    // o parte din rezultat ramane in AUX si o parte in I
    multiply_m(AUX, I, REZ);
}

int64_t calculate_comb(int64_t x) {
    // conditionam cazurile de baza
    if ( x == 1 ) {
        return 1;
    }
    if ( x == 2 ) {
        return 2;
    }
    if ( x == 3 ) {
        return 3;
    }
    int64_t C[3][3] = { {0, 0, 0}, {1, 0, 1}, {0, 1, 1} };
    // comb[n]          comb[1]         0 0 0
    // comb[n-1] =      comb[2]    *    1 0 1  ^(n-3)
    // comb[n-2]        comb[3]         0 1 1
    power_m(C, (x - 3), C);
    int64_t rez = 1 * C[0][2] + 2 * C[1][2] + 3 * C[2][2];
    // returnam primul element de pe prima coloana a rezultatului,
    // adica comb[n], care va fi egal cu comb[n-1]+comb[n-2]
    return rez % MOD;
}

int64_t solve_gpt(vector<pair<char, int64_t>> &input) {
    int64_t n = input.size();
    int64_t x = 1;
    int64_t res = 1;
    for ( int64_t i = 0; i < n; i ++ ) {
        if ( input[i].first == 'n' || input[i].first == 'u' ) {
            x = calculate_comb(input[i].second);
        } else {
            x = 1;
        }
        // nr total de variante ale sirului initial este produsul
        // dintre combinarile de interpretare total posibile
        // ale fiecarui sir de litere
        res = ((res % MOD) * (x % MOD)) % MOD;
    }
    return res % MOD;
}


int main() {
    ifstream fin("badgpt.in");
    ofstream fout("badgpt.out");

    vector<pair <char, int64_t>> input;
    int64_t i = 0;
    char C;
    vector<char> c;
    int64_t N;
    vector<int64_t> n;
    while ( fin >> C >> N ) {
        input.push_back(make_pair(C, N));
    }
    auto res = solve_gpt(input);
    fout << res << "\n";

    return 0;
}
