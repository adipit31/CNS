#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,sum=0;
    cout<<"Enter value of n"<<endl;
    cin>>n;
    for(int j=1;j<n;j++)
    {
    int d = 0; 
    for(int i=1;i<=j;i++)
    {

        if(j%i==0)
        {
            d++;
        }
        
    }
    if(d==2)
    {
        cout<<j<<" is a prime number"<<endl;
        sum=sum+j;
    }
    cout<<"sum will be "<<sum<<endl;

    }   
}