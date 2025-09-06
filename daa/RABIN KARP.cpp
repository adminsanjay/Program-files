#include <iostream>
#include <string>
using namespace std;

void Rabin_Karp(const string& T, const string& P, int d, int q)
{
    int n = T.length();
    int m = P.length();
    int i = 0, j = 0;
    int p = 0;
    int t = 0;
    int h = 1;
    for (i = 0; i < m - 1; i++)
    {
        h = (h * d) % q;
    }
    for (i = 0; i < m; i++)
    {
        p = (d * p + P[i]) % q;
        t = (d * t + T[i]) % q;
    }
    for (i = 0; i <= n - m; i++)
    {
        if (p == t)
        {
            for (j = 0; j < m; j++)
            {
                if (T[i + j] != P[j])
                {
                    break;
                }
            }
            if (j == m)
            {
                cout << "Pattern found at index " << i << endl;
            }
        }
        if (i < n - m)
        {
            t = (d * (t - (long long)T[i] * h % q + q)) % q;
            t = (t + T[i + m]) % q;
        }
    }
}

int main()
{
    string P;
    string T;
    getline(cin, T);
    getline(cin, P);
    int d = 10;
    int q = 13;
    Rabin_Karp(T, P, d, q);
    return 0;
}
