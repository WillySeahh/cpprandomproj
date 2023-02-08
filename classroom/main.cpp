#include <iostream>
#include <vector>
#include <map>

/**
 *
 * This is last question of monceros coding interview
 * @param v
 * @return
 */

int calc (std::vector<int> v);
int dfs(std::vector<int> v, std::vector<bool>& used, int numUsed, int currCost);

int res = INT_MAX;

std::map<std::vector<bool>, int> dp;

int main() {
    std::vector<int> v {90,3,90,65,48,73,10,43,56,1,64};
    std::vector<int> v2 {4,2,8,1,9};

    std::cout << calc(v) << std::endl;
    return 0;
}

int calc (std::vector<int> v) {
    int n = v.size();
    std::vector<bool> used (n, false);
    return dfs(v, used, 0, 0);
    //return res;
}

int dfs(std::vector<int> v, std::vector<bool>& used, int numUsed, int currCost) {
    if (numUsed == (v.size() - 1)) {
        //return currCost;
        return 0;
    }

    if (dp.find(used) != dp.end()) {
        return dp[used];
    }

    int minNum = INT_MAX;
    for(int i = 0; i < v.size(); i++) {
        for(int j = i + 1; j < v.size(); j++) {

            if (used[i] == false && used[j] == false) {
                //can use this 2 index lets try
                used[i] = true;
                used[j] = true;
                numUsed += 2;
                //currCost += std::abs(v[i] - v[j]);
                int resultFromDfs = dfs(v, used, numUsed, currCost);
                int curr = resultFromDfs + std::abs(v[i] - v[j]);
                if (dp.find(used) != dp.end()) {
                    dp[used] = std::min(resultFromDfs, dp[used]);
                } else {
                    dp[used] = resultFromDfs;
                }
                minNum = std::min(curr, minNum);
                used[i] = false;
                used[j] = false;
                numUsed -= 2;
                //currCost -= std::abs(v[i] - v[j]);
            }
        }
    }

    return minNum;
}

