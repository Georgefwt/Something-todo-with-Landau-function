import java.math.BigInteger;
import java.util.Scanner;

public class result {
	public static BigInteger max(BigInteger a, BigInteger b)//取最大值函数
	{
		return a.max(b);
	}
	
	public static int[] allPrimeSmallThanN(int n) {//求出小于n的所有素数
		int i, j, flag = 0, storelength = 1;
		int[] store=new int[n];
		store[0] = 2;
		for (i = 3; i <= n; i++) {
			for (j = 0; j < storelength; j++) {
				if (2 * store[j] > i)break;
				if (i%store[j] == 0)flag = 1;
			}
			if (flag==0) {
				store[storelength] = i;
				storelength++;
			}
			flag = 0;
		}
		return store;
	}
	
	public static BigInteger tempresult(int n) {
		int length,i=0;//length表示小于n的所有素数个数
		int[] store=allPrimeSmallThanN(n);
		while(store[i]>0) i++;
		length=i;
		
		BigInteger[][] dp=new BigInteger[2][20001];//前一项表示考虑的素数个数，后一项表示和,整体表示最小公倍数（乘积）
		for (i = 0; i <= n; i++) dp[0][i] = new BigInteger("1") ;//初始化二维数组
		for (i = 1; i <= length; i++)//循环每个物品，执行状态转移方程
		{
			for (int j = n; j >= store[i - 1]; j--)
			{
				int t = 1;
				BigInteger tempmax =new BigInteger("-1");
				while (j -  Math.pow(store[i - 1], t) >= 0) {
					double tempvalue=Math.pow(store[i - 1], t);
					long targetvalue=(long)tempvalue;
					tempmax = max(tempmax, BigInteger.valueOf(targetvalue).multiply(dp[(i - 1)%2][(int)(j - Math.pow(store[i - 1], t))]));
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
		return dp[length%2][n];
	}
	
	public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        System.out.println("输入n值：");
    	int num=scan.nextInt();
    	scan.close();
		BigInteger n=tempresult(num);
		System.out.println(n);
	}
}