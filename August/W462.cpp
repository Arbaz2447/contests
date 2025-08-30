// 2,3
// 3644. Maximum K to Sort a Permutation
class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        // Main Observation At each index i the value must be 'i' Then Its in correct place
        // if a value is in wrong place then and the pair Right acc to Question !

        // set all to 1's by -1
        int k = -1;
        int i = 0, n = nums.size();
        int val1 = -1, val2 = -1;
        while(i < n){
            if(nums[i] != i){ // main observation !
                if(val1 == -1){
                    val1 = nums[i];
                }else if(val2 == -1){
                    val2 = nums[i];
                }else{
                    k = k & (val1 & val2);
                    val1 = nums[i];
                    val2 = -1;
                }
            }
            i++;
        }
        if(val1 != -1) k = k & val1;
        if(val2 != -1) k = k & val2;
        
        return (k == -1)? 0 : k;
    }


// 3645. Maximum Total from Optimal Activation Order
class Solution {
public:
    // https://www.notion.so/Topics-To-Make-Documentation-25b1c7bed8958030bee3c11c51f2c32d
    // Why can we blindly assume each limit is independent , This Becomes easy 
    long long maxTotal(vector<int>& value, vector<int>& limit) {
        int n = value.size();
        unordered_map<int ,vector<int> > entry ;
        for(int i = 0; i < n; i++){
            entry[limit[i]].push_back(value[i]);
        }
        long long ans = 0;
        for(auto& [key, values] : entry){
            int mini = min({key,
            (int) values.size()});
            sort(values.rbegin(), values.rend());
            for(int i = 0; i < mini; i++){
                ans += values[i];
            }
        }
        return ans;
    }
};



};
