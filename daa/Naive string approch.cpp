#include <iostream>
#include <string>
using namespace std;

void NSM(string p, string t)
{
    int m = p.length();
    int n = t.length();
    for (int i = 0; i <= n - m; i++)
    {
        bool match = true;
        for (int j = 0; j <= m - 1; j++)
        {
            if (t[i + j] != p[j])
            {
                match = false;
                break;
            }
        }
        if (match == true)
        {
            cout << "Pattern found at index " << i << endl;
        }
    }
}

int main()
{
    string t;
    string p;
    getline(cin, t);
    getline(cin, p);
    NSM(p, t);
}
