#include<bits/stdc++.h>
using namespace std;

bool isPrime(int n)
{

    for(int i = 2;i < n;i++)
    {
        if(n % i == 0)
        {
            return false;
        }
    }
        return true;
    
}

vector<vector<int>> getoddpair(int k)
{

    vector<vector<int>> ans;

    int half = k/2;

    for(int i = 1; i <= half; i++)
    {
        int rem = k - i;

        if(isPrime(rem))
        {
            vector<int>temp = {i,rem};

            ans.push_back(temp);
        }

        /*if(rem % 2 != 0)
        {
            vector<int>temp = {i,rem};

            ans.push_back(temp);
        }*/
        
    }
    return ans;
}

int main()
{
    int k = 16;
    vector<vector<int>> ans = getoddpair(k);
    for(auto it: ans)
    {
        for(auto it2: it)
        {
            cout<<it2<<" ";
        }
            cout<<endl;
    }
    return 0;
}



