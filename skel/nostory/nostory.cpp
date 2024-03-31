/*
 * Acest schelet citește datele de intrare și scrie răspunsul generat de voi,
 * astfel că e suficient să completați cele două funcții.
 *
 * Scheletul este doar un punct de plecare, îl puteți modifica oricum doriți:
 * puteți schimba parametrii, reordona funcțiile etc.
 */
#include <bits/stdc++.h>
#include <cstdint>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

int64_t SolveTask1(const vector<int>& a, const vector<int>& b) {
    int n = a.size();
    vector<int> A = a;
    vector<int> B = b;
    sort(A.begin(), A.end());
    sort(B.begin(), B.end(), greater<int>());
    int64_t sum = 0;
    for ( int i= 0; i < n; i ++ ) {
        sum += max(A[i], B[i]);
    }
    return sum;
}

int64_t SolveTask2(const vector<int>& a, const vector<int>& b, int moves) {
    int n = a.size();
    int64_t sum = 0;
    vector<int> max_values(n);
    vector<int> min_values(n);
    for ( int i = 0; i < n; i ++ ) {
        max_values[i] = max(a[i], b[i]);
        min_values[i] = min(a[i], b[i]);
    }
    sort(max_values.begin(), max_values.end());
    sort(min_values.begin(), min_values.end(), greater<int>());
    for ( int i = 0; i < moves; i ++ ) {
        for ( int j = i; j < min_values.size(); j ++ ) {
            if ( max_values[i] < min_values[j] ) {
                // daca exista un element care nu a fost selectat
                // ca fiind maxim, dar este mai mare decat elem curent
                // din vectorul de valori maxime
                max_values[i] = min_values[j];
                break;
            }
        }
        sum += max_values[i];
    }
    // calculam suma pentru restul elementelor care nu au fost schimbate
    for ( int k = moves; k < n; k ++ ) {
        sum += max_values[k];
    }
    return sum;
}

vector<int> ReadVector(istream& is, int size) {
    vector<int> vec(size);
    for (auto& num : vec) {
        is >> num;
    }
    return vec;
}

int main() {
    ifstream fin("nostory.in");
    ofstream fout("nostory.out");

    int task;
    fin >> task;

    int n, moves;
    if (task == 1) {
        fin >> n;
    } else {
        fin >> n >> moves;
    }

    auto a = ReadVector(fin, n);
    auto b = ReadVector(fin, n);

    auto res = task == 1 ? SolveTask1(a, b) : SolveTask2(a, b, moves);
    fout << res << "\n";

    return 0;
}
