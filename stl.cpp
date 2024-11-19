#include<bits/stdc++.h>
#include<string>

using namespace std;


int main()
{
    unordered_map<char,int> mpp;
    string name = "initially";
    char target;
    cout<<"Enter no. to be found:"<<endl;
    cin>>target;

    for(auto it: name)
    {
        mpp[it]++;
    }

   if(mpp.find(target) != mpp.end())
   {
    cout<<mpp[target]<<endl;
   }
   else
   {
    cout<<"not present"<<endl;
   }   
}