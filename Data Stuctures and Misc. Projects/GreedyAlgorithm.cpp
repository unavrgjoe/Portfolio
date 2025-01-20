#include <iostream>
#include <vector>
#include <algorithm>

/**********************************************
 * Description: Just a short greedy algorithm example for a class lab
 **********************************************/

using namespace std;

vector<int> greedyChange(vector<int> coins, int target){
    vector<int> result;
    // In place sort on my coin vector
    sort(coins.rbegin(),coins.rend()); //largest->smallest
    for(int coin : coins){
        while(target >= coin){
            result.push_back(coin);
            target-=coin;
        }
    }
    return result;
}

int main(){
    vector<int> vec1 = {1,5,10,25};
    int target1 = 69;
    vector<int> result1 = greedyChange(vec1, target1);
    for(int coin : result1) {
        cout << coin << " ";
    }
    cout << endl;

    vector<int> vec2 = {1, 3, 5, 15};
    int target2 = 24;
    vector<int> result2 = greedyChange(vec2, target2);
    for(int coin : result2) {
        cout << coin << " ";
    }
    cout << endl;
}

