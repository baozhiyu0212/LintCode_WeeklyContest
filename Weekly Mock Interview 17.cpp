///Result for contest might not be the best solution but should be the most straightforward and easy to come up with
///rank 3rd total cost time: 28min


////problem 1 : twitch words
class Solution {
public:
    /**
     * @param str: the origin string
     * @return: the start and end of every twitch words
     */
    vector<vector<int>> twitchWords(string &str) {
        // Write your code here
        vector<vector<int>> res;
        if(str.size()<3) return res;
        char cur = str[0];
        int count = 1, i;
        for(i=1;i<str.size();i++){
            if(str[i]==str[i-1]) count++;
            else{
                if(count<3){
                    cur = str[i];
                    count = 1;
                }
                else{
                    res.push_back({i-count,i-1});
                    cur = str[i];
                    count = 1;
                }
            }
        }
        if(count>=3) res.push_back({i-count,i-1});
        return res;
    }
};


///////problem 2: Take Coins
class Solution {
public:
    /**
     * @param list: The coins
     * @param k: The k
     * @return: The answer
     */
    int takeCoins(vector<int> &list, int k) {
        // Write your code here
        vector<int> dp(list.size(),0);
        dp[0]=list[0];
        for(int i=1;i<dp.size();i++){
            dp[i] = dp[i-1] + list[i];
        }
        int len=dp.size(),maxi = dp[len-1]-dp[len-1-k];
        for(int i=1;i<=k;i++){
            int cur = dp[i-1] + dp[len-1]-dp[len-1-k+i];
            maxi = max(maxi,cur);
        }
        return maxi;
    }
};

///////problem 3: Recommend Friends
class Solution {
public:
    /**
     * @param friends: people's friends
     * @param user: the user's id
     * @return: the person who most likely to know
     */
    int recommendFriends(vector<vector<int>> &friends, int user) {
        // Write your code here 
        map<int,set<int>> m;
        int maxi = 0, res = -1;
        for(int i=0;i<friends.size();i++){
            for(auto j:friends[i]){
                m[i].insert(j);
            }
        }
        set<int> target;
        for(auto iter=m[user].begin();iter!=m[user].end();iter++){
            target.insert(*iter);
        }
        m.erase(user);
        for(auto iter = m.begin();iter!=m.end();iter++){
            if(iter->second.count(user)) continue;
            else{
                int temp = commonfriends(target,iter->second);
                if(temp>maxi){
                    maxi = temp;
                    res = iter->first;
                }
            }
        }
        return res;
    }
    
    int commonfriends(set<int> s1,set<int> s2){
        int count = 0;
        for(auto iter = s1.begin();iter!=s1.end();iter++){
            if(s2.count(*iter)) count++;
        }
        return count;
    }
};

////problem 4 was skipped by me since I'm tired of writing BFS :(
////Additional: Number of Atoms: Did it in Leetcode competition ago.
class Solution {
public:
    string countOfAtoms(string formula) {
        string ans;
        auto m= helper(formula, 0);
        for(auto e :m) ans+=e.first+ (e.second==1? "":to_string(e.second));     
        return ans;
    }
    
    map<string, int> helper(string& s, int& i) {
        string ans;
        int n =s.size();
        
        auto getNum =[&] (int& i){
            int cnt=0;
            while(i<n && isdigit(s[i])) cnt = cnt*10 + s[i++]-'0';
            return max(cnt,1);
        };
        auto getElement =[&] (int& i){
             string elem;
            if(i<n &&isupper(s[i]))  elem+=s[i++];            
            while(i<n && islower(s[i]))elem+=s[i++];
            return elem;
        };

         map<string, int> m;
         while (i < n && s[i] != ')'){              
             string element = getElement(i); 
             if(!element.empty())m[element] +=getNum(i);
             if(s[i]=='('){
                 i++;
                 auto m1=decode(s,i);
                 i++; 
                 int cnt =getNum(i);
                 for(auto e :m1)  m[e.first]+=e.second*cnt;
             }
            }
   
        return m; 
     }
};
