#include<iostream> //相比BF有更小的空间复杂度
#include<math.h>

void allPrimeSmallThanN(int n, int &length, int *store) {//求出小于n的所有素数
	int i, j, flag = 0, storelength = 1;
	store[0] = 2;
	for (i = 3; i <= n; i++) {
		for (j = 0; j < storelength; j++) {
			if (2 * store[j] > i)break;
			if (i%store[j] == 0)flag = 1;
		}
		if (!flag) {
			store[storelength] = i;
			storelength++;
		}
		flag = 0;
	}
	length = storelength;
}

long long int max(long long int a, long long int b)//取最大值函数
{
	return a > b ? a : b;
}

long long int result(int n) {
	int length;//length表示小于n的所有素数个数
	int* store;
	store = (int*)malloc(n * sizeof(int));
	allPrimeSmallThanN(n, length, store);

	long long int dp[2][20001];//前一项表示考虑的素数个数，后一项表示和,整体表示最小公倍数（乘积）
	for (int i = 0; i <= n; i++) dp[0][i] = 1;//初始化二维数组
	for (int i = 1; i <= length; i++)//循环每个物品，执行状态转移方程
	{
		for (int j = n; j >= store[i - 1]; j--)
		{
			int t = 1;
			long long int tempmax = -1;
			while (j - pow(store[i - 1], t) >= 0) {
				tempmax = max(tempmax, pow(store[i - 1], t)*dp[(i - 1)%2][int(j - pow(store[i - 1], t))]);
				tempmax = max(tempmax, dp[(i - 1)%2][j]);//取模降低空间复杂度
				t++;
			}
			dp[i%2][j] = tempmax;
		}
		for (int j = store[i - 1] - 1; j >= 0; j--)
		{
			dp[i%2][j] = dp[(i - 1)%2][j];
		}
	}
	printf_s("\ng(x):");
	for (int i = 1; i <= n; i++) {
		printf_s("%lld ", dp[length % 2][i]);
	}
	return dp[length%2][n];
}

int main() {
	int n, length;//length表示小于n的所有素数个数
	int* store;
	printf_s("Please input N:");
	scanf_s("%d", &n);
	store = (int*)malloc(n * sizeof(int));
	allPrimeSmallThanN(n, length, store);
	printf_s("all prime less than n:");
	for (int i = 0; i < length; i++)
	{
		printf_s("%d ", store[i]);
	}
	printf_s("\n%lld", result(n));
	return 0;
}