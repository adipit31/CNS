#include<bits/stdc++.h>
using namespace std;


// 12

// 12 % 2 ==0 
bool isPrime(int n){

    for (int i = 2; i < n; i++)
    {
        if(n % i == 0) return false;
    }
    return true;
}

vector<vector<int>> getPrimePair(int k){// k = 18

    vector<vector<int>> ans;

    int half = k/2;

    for (int i = 1; i <= half; i++)
    {
        int rem = k - i;

        if(isPrime(rem)){
            vector<int> temp = {i, rem};
            ans.push_back(temp);
        }
    }

    return ans;

}





int numToChar(vector<int> arr){
    string str = "";

    for (int i = 0; i < arr.size(); i++)
    {
        char c = arr[i];
        str.push_back(c);
    }

    unordered_map<char,int> mpp;

    for(auto ch : str){
        mpp[ch]++;
    }

    int maxi = 0;

    for(auto it : mpp){
        maxi = max(maxi,it.second);
    }
    return maxi;
}




int main(){
    int k = 18;


    /*
    [1,7]
    [2,6]
    [3,5]
    [4,4]
    [5,3]
    [6,2]
    [7,1]
    */

    vector<int> arr= {65,66,67,68,65,68,69,70,70,70,70};

    cout<<numToChar(arr)<<endl;

    return 0;
}