#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	int countRangeSum(vector<int>& nums, int lower, int upper) {
		const int n = nums.size();
		if (n <= 0){
			return 0;
		}
		vector<long long> sums(n+1, 0);
		for (int i = 0; i < n; ++i){
			sums[i + 1] = sums[i] + nums[i];
		}
		return merge(sums, 0, n, lower, upper);
	}
private:
	int merge(vector<long long>& sums, int start, int end, int lower, int upper){
		if (start >= end){
			return 0;
		}
		int mid = start + (end - start) / 2;
		int count = merge(sums, start, mid, lower, upper) 
			+ merge(sums, mid+1, end, lower, upper); // ���� 

		vector<long long> tmp(end - start + 1, 0);  // �ϲ� 
		int j = mid + 1, k = mid + 1, t = mid + 1, r = 0; // i ���������飬 j��k˫ָ����������飬i���ӣ�jk���ô�ͷ��ʼ
		for (int i = start; i <= mid; ++i, ++r){
			while (j <= end && sums[j] - sums[i] <= upper) {
				++j;
			}
			while (k <= end && sums[k] - sums[i] < lower) {
				++k;
			}
			count += j - k;  // ����˫ָ���������sum���Ź������Ժ���ִ��sum�Ĺ鲢����
			while (t <= end && sums[t] <= sums[i]) { // t��mid+1��ʼ, i��start��ʼ�����sum[t] < sum[i]����˵��
				tmp[r++] = sums[t++]; // ��ʱsum[t] < sum[i], tmp[r]�д洢���������и�С�ģ���ʵ������
			}
			tmp[r] = sums[i]; // ��ʱsum[i] < sum[t]
		}

		for (int i = 0; i < r; ++i){  // �����ź�����鸳ֵ��sum
			sums[start + i] = tmp[i];
		}
		return count;
	}
};

int main(int argc, char *argv[]){
	Solution s;
	cout << s.countRangeSum(vector<int>{-2, 5, -1}, -2, 2) << endl;
	system("pause");
	return 0;
}