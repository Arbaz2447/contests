3633. Earliest Finish Time for Land and Water Rides I
3634. Minimum Removals to Balance Array
3635. Earliest Finish Time for Land and Water Rides II

3638. Maximum Balanced Shipments(dp + stack)
3640. Trionic Array II(hard dp)
3639. Minimum Time to Activate String

// This Pattern ( New Found ) !
209. Minimum Size Subarray Sum

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
