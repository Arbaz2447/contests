// 2,3
// 3649. Number of Perfect Pairs 
//main reason of i < j enforces to not to consider duplicate and same pairs 
/*min(|a - b|, |a + b|) <= min(|a|, |b|) 
    this statement can be broken into 2:
        case 1: if both a and b have same sign then : min(|a-b|) <= min(|a|,|b|)
        case 2: if both have diff sign then min(|a+b|) <= min(a,b)
        
        no assume for case 1 : say a is minimum
            a - b <= a (or) b - a <= a --> b <= 2a (largest value <= 2*smallest value)
            This is the valid condition !
         
        case 2: for diff signs i.e a > 0 & b < 0 and valid condition 'min(|a+b|) <= min(|a|,|b|)'
            b is for sure neg so we must apply |b| every where for simplicity say c = |b|
            (|a| is a (>0)) and (c = |b| == -b) because -(b) is positive (b is < 0)

            min(|a-c|) <= min(a,c) // Both are positive take a as min or c both cases !
                sub case-1 : a - c or c - a <= a then c <= 2a (Larger value <= 2 * smaller value)
                sub case-2 : a - c or c - a <= c then a <= 2c (Larger value <= 2 * smaller value)
So in all the three cases a larger pair can only be atmost 2 * smaller!
*/
class Solution {
public:
    long long perfectPairs(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end(), [](int& a , int& b){
            return abs(a) < abs(b);
        });
        int j = 1;
        long long cnt = 0;
        for(int  i = 0; i < n; i++){
            while(j < n && abs(nums[j]) <= 2LL * abs(nums[i])){
                j++;
            }
            cnt += (j - 1 - i); // i and j are excluded in pair cnt !
        }
        return cnt;
    }


// 3650. Minimum Cost Path with Edge Reversals
class Solution {
public:
    using ll = long long;
    int minCost(int n, vector<vector<int>>& edges) {

        // Adj List
        vector<pair<int,int>> adj[n];
        for(int i = 0; i < edges.size(); i++){ // Im traversing Edges not the nodes here !
            adj[edges[i][0]].push_back({edges[i][1], edges[i][2]});
            adj[edges[i][1]].push_back({edges[i][0], 2 * edges[i][2]});
        }

        // standred Dijakstra algo {total Cost , nodeNum};
        using p = pair< long long , int > ;
        priority_queue < p, vector<p> , greater<p> > pq;
        pq.push({0LL, 0});

        vector<ll> minCost(n,LLONG_MAX);
        minCost[0] = 0LL;

        // Heap Expands the shortest Path Available ! 
        while(!pq.empty()){
            auto data = pq.top(); pq.pop();
            ll newCost = data.first;
            int nextNode = data.second;

            if(newCost > minCost[nextNode]) continue; // Lazy Deletion 

            if(nextNode == n - 1) return newCost; // Heap Gureentees Minimum Cost !

            // minCost[nextNode] = newCost;


            for(auto& N : adj[nextNode]){ // Traverses Adjacency List Not the heap !
                ll cost = N.second;
                int node = N.first;

                // if already i have shortest path to a node then why to push greater path etc node ?
                if(newCost+cost < minCost[node]){
                    minCost[node] = newCost + cost;
                    pq.push({newCost + cost, node});
                }   
            }
        }

        return (minCost[n-1] == LLONG_MAX) ? -1 : minCost[n-1];
    }
};
};
