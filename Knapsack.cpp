#include <bits/stdc++.h>

using namespace std;

class Solution
{
    public:

    //recursion and memoization
    int maxcount(int wt[] ,int val[] ,int W ,int i,vector<vector<int>>& dpm)
    {
        if(i==0)
        {
            if(W>=wt[0])
            {
                return val[0];
            }
            return 0;
        }

        if(dpm[i][W]!=-1)
        {
            return dpm[i][W];
        }

        int nottake = 0+maxcount(wt,val ,W,i-1,dpm);

        int take =INT_MIN;
        if(W>=wt[i])
        {
            take =val[i]+maxcount(wt,val,W-wt[i],i-1,dpm);
        }

        dpm[i][W]=max(take,nottake);

        return dpm[i][W];
    }

    int knapSack(int W, int wt[], int val[], int n)
    {
        //tabulation

       // vector<vector<int>> dpm(n,vector<int>(W+1,-1)); // dp for memoization

       vector<vector<int>> dp(n+1,vector<int>(W+1,0));

       for(int i=0;i<=n;i++)
       {
           for(int weight =0;weight<=W;weight++)
           {
               if(i==0 or weight==0)
               {
                   dp[i][weight]=0;
               } 

               else if(wt[i-1]>weight)
               {
                   dp[i][weight]=dp[i-1][weight];
               }

               else
               {
                    int nottake = dp[i-1][weight];
                    int take =INT_MIN;

                    if(weight>=wt[i-1])
                    {
                        take =val[i-1]+dp[i-1][weight-wt[i-1]];
                    }

                    dp[i][weight]=max(take,nottake);
               }
                
           }
       }

       cout<<"in tabulation approach matrix look like"<<endl;

       for(int i=0;i<=n;i++)
       {
           for(int weight =0;weight<=W;weight++)
           {
                cout<<dp[i][weight]<<" ";
           }cout<<endl;
       }cout<<endl;
       

        cout<<"item that are selected"<<endl;
        vector<int>ans(n+1);
        int i=n,j=W;

        while(i>=1 and j>=1)
        {
            if(dp[i][j]==dp[i-1][j])
            {
                ans[i]=0;
                i--;
            }

            else
            {
                ans[i]=1;
                i--;
                j=j-wt[i];
            }
        }
       
       for(int i=1;i<=n;i++)
       {
          cout<<ans[i];
       }cout<<endl;

       return dp[n][W]; // tabulation
     
      //return maxcount(wt,val,W,n-1,dpm); // memoization

    }
};

int main()
{
    int n,W;
    cout<<"enter number of item and capacity of bag"<<endl;
    cin>>n>>W;

    int val[n];
    int wt[n];

    cout<<"enter profit associated with each and every item one by one "<<endl;
    for(int i=0;i<n;i++)
    {
        cin>>val[i];
    }

    cout<<"enter weight associated with each and every item one by one "<<endl;
    for(int i=0;i<n;i++)
    {
        cin>>wt[i];
    }

    Solution s;
    int tot= s.knapSack(W,wt,val,n);
    cout<<"total profit earn will be "<<tot<<endl;
    return 0;
}
