3640. Trionic Array II
// Hard
// You are given an integer array nums of length n.

// A trionic subarray is a contiguous subarray nums[l...r] (with 0 <= l < r < n) for which there exist indices l < p < q < r such that:

// nums[l...p] is strictly increasing,
// nums[p...q] is strictly decreasing,
// nums[q...r] is strictly increasing.
// Return the maximum sum of any trionic subarray in nums.


class Solution {
public:
    long long maxSumTrionic(vector<int>& a) {
        int n = a.size();
        /*
                                  /dp[3]
                       /\        /
                dp[1] /  \      /
        ------       /   dp[2]
        dp[0]
        dp[0] = start phase
        dp[1] = 1st increaseing phase
        dp[2] = 1st decreaseing phase
        dp[3] = 2nd increasing
        */
        
        vector<vector<long long>> dp(4, vector<long long>(n, -1e18));

        long long ans = -1e18;
        for(int i = 0; i < n; i++) {
            dp[0][i] = a[i];
            if(i > 0) {
                //start increasing here OR we are alreading in increasing phase
                if(a[i] > a[i - 1])
                 dp[1][i] = max(dp[0][i - 1] + a[i], dp[1][i - 1] + a[i]);
                //start decreasing phase here OR we are alreading in it
                if(a[i] < a[i - 1])
                 dp[2][i] = max(dp[1][i - 1] + a[i], dp[2][i - 1] + a[i]);
                //start 2nd increasing phase or continue prev 2nd increasing phase
                if(a[i] > a[i - 1])
                 dp[3][i] = max(dp[2][i - 1] + a[i], dp[3][i - 1] + a[i]); 
            }
            ans = max(ans, dp[3][i]);
        }

        return ans;
    }
};

// https://g.co/gemini/share/ebdec7284a51 

// 0 - 1 Knapsack Problem

class Solution {
  public:
  
    int getMax(int w, int item, vector<int> &val, vector<int> &wt,vector<vector<int>> &dp){
        if(item == 0){
            if(wt[item] <= w){
                return val[item];
            }
            return 0;
        }
        if(dp[item][w] != -1) return dp[item][w];
       
        int maxOnEx = getMax(w, item - 1,val, wt,dp);
        int maxOnIn = 0;
        if(wt[item] <= w){
             maxOnIn = val[item] + getMax(w - wt[item], item - 1,val , wt,dp);
        }
        
        return dp[item][w] = max(maxOnEx,maxOnIn);
    }
    int knapsack(int W, vector<int> &val, vector<int> &wt) {
        vector< vector<int> > dp(val.size(), vector<int>(W + 1,-1));
        return getMax(W,val.size() - 1, val, wt,dp);
    }
};
// Prac lc 416 !

