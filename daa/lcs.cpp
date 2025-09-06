#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

pair<int, string> LCS_length (string s1, string s2)
{
    int m = s1.length();
    int n = s2.length();
    vector<vector<int>> c(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                c[i][j] = c[i - 1][j - 1] + 1;
            }
            else
            {
                c[i][j] = max(c[i - 1][j], c[i][j - 1]);
            }
        }
    }
    
    int l = c[m][n];
    string lcs = "";
    int i = m, j = n;
    while (i > 0 && j > 0)
    {
        if (s1[i - 1] == s2[j - 1])
        {
            lcs = s1[i - 1] + lcs;
            i--;
            j--;
        }
        else if (c[i - 1][j] > c[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }
    return make_pair(l, lcs);
}

int main()
{
    string s1, s2;
    cin >> s1;
    cin >> s2;
    pair<int, string> ans = LCS_length(s1, s2);
    cout << ans.first << endl;
    cout << ans.second << endl;
    return 0;
}
