#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <sstream>
using namespace std;

void printOptimalParens(const vector<vector<int>>& s, int i, int j)
{
    if (i == j)
    {
        cout << char('A' + i);
    }
    else
    {
        cout << "(";
        printOptimalParens(s, i, s[i][j]);
        printOptimalParens(s, s[i][j] + 1, j);
        cout << ")";
    }
}
void matrixChainOrder(const vector<int>& arr)
{
    int n = arr.size() - 1;
    vector<vector<int>> m(n, vector<int>(n, 0));
    vector<vector<int>> s(n, vector<int>(n, 0));
    
    for (int l = 2; l <= n; l++)
    {
        for (int i = 0; i <= n - l; i++)
        {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++)
            {
                int q = m[i][k] + m[k + 1][j] + arr[i] * arr[k + 1] * arr[j + 1];
                if (q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    cout << m[0][n - 1] << endl;
    printOptimalParens(s, 0, n - 1);
}

int main()
{
    string input;
    getline(cin, input);
    stringstream ss(input);
    vector<int> arr;
    int num;
    while (ss >> num)
    {
        arr.push_back(num);
    }
    matrixChainOrder(arr);
    return 0;
}
