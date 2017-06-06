#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Solution {
public:
	vector<pair<int, int>> getSkyline(vector<vector<int>>& Buildings) {
		vector<pair<int, int>> res;
		priority_queue<pair<int, int>> active;
		int i = 0, n = Buildings.size(), x, y;
		while (i < n || !active.empty()) {
			x = active.empty() ? Buildings[i][0] : active.top().second; 
			if (i >= n || Buildings[i][0] > x) {
				while (!active.empty() && active.top().second <= x) // PQ �е����߶ȵĽ�������x֮ǰ��ȫ���Ƴ�
					active.pop();
			}
			else { // Buildings[i][0] <= x && i < n // �ڴ����µ�building
				x = Buildings[i][0];
				while (i < n && Buildings[i][0] == x) {  // �Դ˸߶ȣ����������н����������ж������������ PQ ��
					active.push({ Buildings[i][2], Buildings[i][1] });
					i++;
				}
			}
			y = active.empty() ? 0 : active.top().first;  // ����ؼ���ĸ߶�
			if (res.empty() || res.back().second != y) {  // �շŽ�ȥ��Ԫ�ظ߶Ȳ�ͬ
				res.push_back({ x, y });
			}
		}
		return res;
	}
};

int main(int argc, char *argv[]){
	Solution s;
	vector<vector<int>> buildings{ { 1, 2, 3 }, { 1, 3, 5 }, {1, 5, 4} };
	s.getSkyline(buildings);
	return 0;
}
