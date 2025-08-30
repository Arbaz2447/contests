// 3659. Partition Array Into K-Distinct Groups
class Solution {
public:
    bool partitionArray(vector<int>& nums, int k) {
        int n = nums.size();
        if(n % k != 0) return false;

       
        unordered_map<int,int> freq;
        for(int i = 0; i < n; i++) freq[nums[i]]++;

        int maxGroups = n / k;

        for(auto& [key,i] : freq)
        if(i > maxGroups) return false;

        return true;
    }
};

// 3660. Jump Game IX
