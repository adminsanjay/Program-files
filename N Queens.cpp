#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int x[100];

bool Place(int k, int i)
{
    for (int j = 1; j <= k - 1; j++)
    {
        if (x[j] == i || abs(x[j] - i) == abs(j - k))
        {
            return false;
        }
    }
    return true;
}

void NQueens(int k, int n)
{
    for (int i = 1; i <= n; i++)
    {
        if (Place(k, i))
        {
            x[k] = i;
            if (k == n)
            {
                for (int j = 1; j <= n; j++)
                {
                    if(j != n)
                    {
                        cout << x[j] << " ";
                    }
                    else
                    {
                        cout <<x[j]<< endl;                    
                    }
                }
            }            
            else
            {
                NQueens(k + 1, n);
            }
        }
    }
}

int main()
{
    int n;
    cin >> n;
    NQueens(1, n);
    return 0;
}
