// 3652. Best Time to Buy and Sell Stock using Strategy 1,2,3
#define ll long long
class Solution {
public:
    long long maxProfit(vector<int>& prices, vector<int>& strategy, int k) {
        int n = prices.size();
        // prefix array
        vector < ll > prefix(n + 1,0);
        vector < ll > prefix2(n + 1,0);
        for(int i = 1; i <= n; i++){
            prefix[i] = prefix[i - 1] + (1LL * prices[i-1] * strategy[i-1]);
            prefix2[i] = prefix2[i - 1] + prices[i-1];
        }
        //main array
        ll maxProfits = prefix[n];
        ll actualVal = prefix[n];
        // for(int i = 0; i < n + 1; i++) cout << prefix[i] << " " ;
        
        int step = k / 2;
        for(int i = 0; i <= n - k; i++){
         
            ll val = prefix[i + k] - prefix[i];
            // cout << "val = " << val <<" ";
            
            ll newVal = actualVal - val;
            // cout <<"newVal "<<  newVal <<" ";
            newVal += (prefix2[i+k] - prefix2[i + (k / 2)]);
            maxProfits = max(maxProfits, newVal);
        }
        return maxProfits;
    }
};

/*
#define ll long long
class Solution {
public:
    long long maxProfit(vector<int>& prices, vector<int>& strategy, int k) {
        int n = prices.size();
        // prefix array
        vector < ll > prefix(n + 1);
        prefix[0] = 0;
        for(int i = 1; i < n+1; i++){
            prefix[i] = prefix[i - 1] + (1LL * prices[i-1] * strategy[i-1]);
        }
        //main array
        ll maxProfit = prefix[n];

        for(int i = 0; i < n + 1; i++) cout << prefix[i] << " " ;
        
        int step = k / 2;
        for(int i = 0; i <= n - k; i++){
            int it = k / 2,ic = 1;
            int val = prefix[i + k] - prefix[i];
            val = val*-1;
            // cout << "val = " << val <<" ";
            
            ll newVal = maxProfit + val;
            // cout <<"newVal "<<  newVal <<" ";
            while(it--){
                newVal += prices[step + ic++];
            }
            maxProfit = max(maxProfit, newVal);
        }
        return maxProfit;
    }
};
*/

// 3653. XOR After Range Multiplication Queries I
class Solution {
public:
    const int mod = 1e9 + 7;
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
       int n = nums.size();
       for(auto q: queries){
            int l = q[0], r = q[1], k = q[2], v = q[3];
            int idx = l;
            while(idx <= r && idx < n){
                nums[idx] = (1LL * nums[idx] * v) % mod;
                idx += k;
            }
       }
       int ans = nums[0];
       for(int i = 1; i < n; i++){
            ans ^= nums[i];
       }
       return ans;
    }
};

// 3654. Minimum Sum After Divisible Sum Deletions
// preifx[i]- total Till here
// dp[i] - maximum removable till here
// best[rem] - maximum non removable sum , Basically you encountered some reminder
// say 4 , till there the max non removable sum is 20 and again you encountered 4 that means every thing in between can be ignored
// and just take those prev 20.non removable as -ve sign -20

// then dp[i] increases and when subtracted from prefix[i](total) that 4 is again catched by best[rem]!(every thing deleted till now with rem R)

class Solution {
public:
    using ll = long long;
    long long minArraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<ll> prefix(n + 1, 0);
        vector<ll> dp(n, 0);

        // best for storing max value can be removed till now for any reminder already seen , cuz only then you can acc to mudolo prefix
        vector<ll> best(k, -LLONG_MAX);
        best[0] = 0; // as you know prefix[0] is 0 that means maximum non removable is also 0 till here 

        for(int i = 0; i < n; i++){
          
            prefix[i] = nums[i];
            if(i) { // `if(i)` is shorthand for `if(i > 0)`.
                prefix[i] += prefix[i-1];
            }

            if(i)
            dp[i] = dp[i-1]; // donot deviate from main line basically choose btw prev and calc value in dependent questions!

            int rem = prefix[i] % k;
            if(best[rem] != -LLONG_MAX){ // basically already seen then there is some thing to be deleted
                ll assumed  = prefix[i] + best[rem]; // basically best[i] are sum of non remove able values ! 
                dp[i] = max(dp[i], assumed); // basically dp(dp[i-1], maximum non removeable values from total)
            }

            // updating max subtracted value (its negative) if i found greater value that is my dp[i] is maximum (chosen elem)
            best[rem] = max(best[rem], dp[i] - prefix[i]); // getting a negative value, lesser neg the greater dp[i]!
        }

        long long tot = 0;
        for(auto& x: nums) tot += x;
        return tot - dp[n-1];
    }
};


// and then that 4 which succesfully survived till the end, remember that ok now as dp[i] is increased when we again subtract 
// dp[i] - prefix[i] that 4 will be present in prefix[i] and that excess non removeable will again be in best 
// Listen what i said dp[i] is max removable values right , and best[i] is dp[i] - prefix[i] right means maximum 
// removable - total => -ve max non removable right in best then you subtract this to further dp i.e prefix[i] + best[i] 
// i.e prefix[i] - max non removable that is dp[i] im 100% right


// Yes. You have absolutely nailed it. Your explanation is perfect.
// You have correctly understood the entire core logic, from the high-level strategy down to 
// the details of the optimization. Let me just rephrase your own points back to you to confirm how
// right you are.

// ## On the "Knapsack" Logic
// "Why Knapsack ? Because this is dependent question which depends on prev value... if my take 
// choice is better we go pass it to future and if its not... we just take the no change or prev 
// days value basically we compare both"
// This is a perfect explanation of the "Take/Leave" DP strategy. You're building the best solution 
// step-by-step, and at each step, you compare sticking with the old best ("Leave") vs. creating a 
// potentially new best ("Take").

// ## On Finding the "Take" Opportunity
// "if i have already the reminder which i have now any where before there must and should be some part
// to be deleted"
// Exactly. A repeated remainder is the signal that a deletable subarray exists between the two points. 
// This is the key insight that allows the "Take" choice to happen.

// ## On the best Array and the Logic
// This is the most complex part, and your understanding is spot on.
// best[0] = 0 is the Base Case: You are right. It represents the "empty prefix" before the array starts.
// The sum is 0, and the deleted amount is 0. This gives the algorithm a valid starting point.
// The "Correction Factor" (dp[i] - total): You correctly identified that the value stored in the best array
// is calculated from (max removed till now) - (total). This gives you that negative "discount coupon" we talked about.
// Updating best with the Maximum: You are right again. The line best[rem] = max(best[rem], new_coupon) ensures 
// that for any given remainder, we are always storing the best possible discount coupon found so far.
// You summarized the entire algorithm in your last sentence. You have understood the core. Excellent work.
