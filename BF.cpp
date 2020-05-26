#include<iostream>
#include<math.h>
int gcd(int a, int b){
	return b == 0 ? a : gcd(b, a%b);
}

int lcm(int a, int b){
	if (a%b == 0)return a;
	if (b%a == 0)return b;
	else return a * b / gcd(a, b);
}

int mlcm(int *first, int num) {
	int i,rec;
	rec = lcm(first[0], first[1]);
	for (i = 2; i < num; i++) {
		rec = lcm(rec, first[i]);
	}
	return rec;
}

void allPrimeSmallThanN(int n,int &length,int *store) {//求出小于n的所有素数
	int i,j,flag=0,storelength=1;
	store[0] = 2;
	for (i = 3; i <= n; i++) {
		for (j = 0; j < storelength; j++) {
			if (2 * store[j] > i)break;
			if (i%store[j] == 0)flag = 1;
		}
		if (!flag){
			store[storelength] = i;
			storelength++;
		}
		flag = 0;
	}
	length = storelength;
}

int max(int a, int b)//取最大值函数
{
	return a > b ? a : b;
}

int result(int n) {
	int length;//length表示小于n的所有素数个数
	int* store;
	store = (int*)malloc(n * sizeof(int));
	allPrimeSmallThanN(n, length, store);

	int dp[1001][1001];//前一项表示考虑的素数个数，后一项表示和,整体表示最小公倍数（乘积）
	//dp[0][0] = 0;//初始化二维数组
	for (int i = 0; i <= n; i++) dp[0][i] = 1;//初始化二维数组
	for (int i = 1; i <= length; i++)//循环每个物品，执行状态转移方程
	{
		for (int j = n; j >= store[i - 1]; j--)
		{
			int t = 1, tempmax = -1;
			while (j - pow(store[i - 1], t) >= 0) {
				tempmax = max(tempmax, pow(store[i - 1], t)*dp[i - 1][int(j - pow(store[i - 1], t))]);
				tempmax = max(tempmax, dp[i - 1][j]);
				t++;
			}
			dp[i][j] = tempmax;
		}
		for (int j = store[i - 1] - 1; j >= 0; j--)
		{
			dp[i][j] = dp[i - 1][j];
		}
	}
	return dp[length][n];
}

int main() {
	int n,length;//length表示小于n的所有素数个数
	int* store;
	printf_s("Please input N:");
	scanf_s("%d", &n);
	store = (int*)malloc(n * sizeof(int));
	allPrimeSmallThanN(n, length, store);
	printf_s("%d\n", length);
	for (int i = 0; i < length; i++)
	{
		printf_s("%d ", store[i]);
	}

	//int dp[1001][1001];//前一项表示考虑的素数个数，后一项表示和,整体表示最小公倍数（乘积）
	//for (int i = 0; i <= n; i++) dp[0][i] = 1;//初始化二维数组
	//for (int i = 1; i <= length; i++)//循环每个物品，执行状态转移方程
	//{
	//	for (int j = n; j >= store[i-1]; j--)
	//	{
	//		int t=1,tempmax=-1;
	//		while (j-pow(store[i-1],t)>=0){
	//			tempmax = max(tempmax, pow(store[i-1], t)*dp[i - 1][int(j - pow(store[i-1], t))]);
	//			tempmax = max(tempmax, dp[i - 1][j]);
	//			t++;
	//		}
	//		dp[i][j] = tempmax;
	//	}
	//	for (int j = store[i-1] - 1; j >= 0; j--)
	//	{
	//		dp[i][j] = dp[i - 1][j];
	//	}
	//}
	//printf("\n%d", dp[length][n]);
	printf_s("\n%d", result(n));

	return 0;
}