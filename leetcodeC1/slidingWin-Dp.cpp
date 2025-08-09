3633. Earliest Finish Time for Land and Water Rides I
3634. Minimum Removals to Balance Array
3635. Earliest Finish Time for Land and Water Rides II

3639. Minimum Time to Activate String
3640. Trionic Array II(hard dp) 

// This Pattern ( New Found ) !
209. Minimum Size Subarray Sum (pend ..!)
904. Fruit Into Baskets (Sliding window ) (Daily Question)






// 904. Fruit Into Baskets (Sliding window )
class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int left = 0;
        unordered_map < int , int > freq;
        int n = fruits.size();
        int maxi = INT_MIN;
        for(int right = 0; right < n; right++){
            freq[fruits[right]]++;

            // Invalid Window ?
            while(!freq.empty() && freq.size() >  2){
                freq[fruits[left]]--;
                if(freq[fruits[left]] == 0) freq.erase(fruits[left]);
                left++;
                if(left > right) break;
            }
            // Valid Window ?
            if(left <= right){
                maxi = max(maxi , right - left + 1);
            }
        }
        return maxi;
    }
};
// 3634. Minimum Removals to Balance Array (Sliding Window)
class Solution {
public:
    int minRemoval(vector<int>& nums, int k) {
        // reverse the Q. Consider finding MAX balanced array ! 
        int left = 0;
        int n = nums.size();
        if(n == 1) return 0;
        sort(nums.begin(),nums.end());
        int len = 0;
        for(int right = 0; right < n; right++){
            int mini = nums[left] , maxi = nums[right];

            // window is invalid ?
            while((1LL * mini * k) < maxi){
                left++;
                if(left > right) break;
                mini = nums[left];
            }

            if(left <= right){
                len = max(len, right - left + 1);
            } 
        }
       return n - len;
    }
};
// 2106. Maximum Fruits Harvested After at Most K Steps (Sliding Window Hard (Daily Q Day 2))
class Solution {
public:
    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
        int n = fruits.size();
        long long maxi = 0;
        // prefix sum to calc total fruits in a window
        vector<long long> prefix(n + 1 , 0);
        for(int i = 0; i < n; i++){
            prefix[i + 1] = prefix[i] + fruits[i][1];
        }

        int left = 0;
        for(int right = 0; right < n; right++){

            int fruitLeft = fruits[left][0];
            int fruitRight = fruits[right][0];

            
            long long cost_to_left = abs( startPos - fruitLeft) + (fruitRight - fruitLeft);
            long long cost_to_right = abs( fruitRight - startPos ) + (fruitRight - fruitLeft);
            long long cost = min(cost_to_left, cost_to_right);

            // what if the whole window is unreachable ? udjust it to make valid
            while(left <= right && cost > k ){
                left++; // To reduce cost
                if(left > right) break;

                 fruitLeft = fruits[left][0];
                  cost_to_left = abs( startPos - fruitLeft) + (fruitRight - fruitLeft);
                 cost_to_right = abs( fruitRight - startPos ) + (fruitRight - fruitLeft);
                 cost = min(cost_to_left, cost_to_right);
            }
            // Now we got a valid window which all areas are reachable ! 
            // precomputed in prefix sum right ? !
            if(left <= right){
                long long total = prefix[right + 1] - prefix[left];
                maxi =  max(maxi , total);
            }
        }
        return maxi;
    }
};


// 3639. Minimum Time to Activate String
// DSU approach ! pending 
class Solution {
public:
    int minTime(string s, vector<int>& order, int k) {
        
    }
};
/*
// Binary Search On Answer ! 
// ant any time t to any time t + 1 , the soln it gives say X then for other its > X 
// so binary search on ans can be applied 
class Solution {
private:
    
    bool isValid(int time, vector<int>& order , int& k, int strLen){
        vector< bool > arr(strLen,false);

        // Mark all starts true
        for(int t = 0; t <= time; t++){
            arr[order[t]] = true;
        }
        long long total = 1LL * strLen * (strLen + 1) / 2;
        
        long long inv = 0;
        int c = 0;
        for(int i = 0; i < strLen; i++){
            if(arr[i] == false){
                 c++;
            }else{
                inv += 1LL * c * (c + 1) / 2;
                c = 0;
            } 
        }
        if(arr[strLen - 1] == false) inv += 1LL * c * (c + 1) / 2;
        return (total - inv >= k);
    }
public:
    int minTime(string s, vector<int>& order, int k) {
        
        int low = 0, high = s.length() - 1;
        int ans = -1;
        while(low <= high){
            int mid = low + (high - low) / 2; // mid -  time interval (active)
            if(isValid(mid,order,k,s.length())){
                ans = mid;
                high = mid - 1;
            }else{
                low = mid + 1;
            }
        }
        return ans;
    }
};

// Mathematical Thinking !

// arbaz [3,1,0] -> arb*z => valid = Total - invalid substrings ?
// Total = n * (n + 1) / 2 right and subarray can be can be calc by same !
// keep track of where and where is the * mark or basically 
// how many continous parts remain after placing a '*';
// How about scanning a string and finding how many contigious blocks > 1 ?
// n ^ 2 right ! using a map is Good ! 

class Solution {
public:
    int minTime(string s, vector<int>& order, int k) {
        int strLen = s.length();
        int n = order.size();
        long long total = 1LL * strLen * (strLen + 1) / 2; // remove invalid substr
        int t = 0;
        map < int, int > pos; // smartly tracking the indices ! is the key !
        pos[0] = strLen - 1;
        long long totalInv = total;

        
        for(int a = 0; a < n ; a++){
            int index = order[a];
            // faster traversal of blocks
            auto data = pos.upper_bound(index);
            data--;

            int i = data -> first;
            int j = data -> second;
            pos.erase(data);
            int len = j - i + 1;
            long long subTotal = 1LL * len * ( len + 1 ) / 2;
            totalInv -= subTotal;

                // basically the ranges right ! 
                pair<int,int> p1 = {i , index - 1};
                pair<int,int> p2 = {index + 1 , j};
            
                // basically youre checking range !
                if(i <= index - 1){
                    int l1 = p1.second - p1.first + 1;
                    totalInv += 1LL * l1 * (l1 + 1) / 2;
                    pos[p1.first] = p1.second; 
                }
                if(index + 1 <= j){
                    int l2 = p2.second - p2.first + 1;
                    totalInv +=1LL * l2 * (l2 + 1) / 2;
                    pos[p2.first] = p2.second;  
                }        
            if((total - totalInv) >= k) return a;
        }
        return -1;
    }
};

*/
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





