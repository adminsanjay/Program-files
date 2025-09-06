#include <iostream>
#include <climits>
#include <vector>
using namespace std;

int cutRod(vector<int>& p, int n)
{
    int B[n];
    B[0] = 0;
    for (int j = 1; j <= n; j++)
    {
        int q = INT_MIN;
        for (int i = 1; i <= j; i++)
        {
            q = max(q, p[i - 1] + B[j - i]);
            B[j] = q;
        }
    }
    return B[n];
}

int main()
{
    vector<int> p;
    int x;
    while (cin >> x)
    {
        p.push_back(x);
    }
    int n = p.size();
    int ans = cutRod(p, n);
    cout << ans << endl;
    return 0;
}
