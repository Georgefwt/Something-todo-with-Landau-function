import java.math.BigInteger;
import java.util.Scanner;

public class result {
	public static BigInteger max(BigInteger a, BigInteger b)//ȡ���ֵ����
	{
		return a.max(b);
	}
	
	public static int[] allPrimeSmallThanN(int n) {//���С��n����������
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
		int length,i=0;//length��ʾС��n��������������
		int[] store=allPrimeSmallThanN(n);
		while(store[i]>0) i++;
		length=i;
		
		BigInteger[][] dp=new BigInteger[2][20001];//ǰһ���ʾ���ǵ�������������һ���ʾ��,�����ʾ��С���������˻���
		for (i = 0; i <= n; i++) dp[0][i] = new BigInteger("1") ;//��ʼ����ά����
		for (i = 1; i <= length; i++)//ѭ��ÿ����Ʒ��ִ��״̬ת�Ʒ���
		{
			for (int j = n; j >= store[i - 1]; j--)
			{
				int t = 1;
				BigInteger tempmax =new BigInteger("-1");
				while (j -  Math.pow(store[i - 1], t) >= 0) {
					double tempvalue=Math.pow(store[i - 1], t);
					long targetvalue=(long)tempvalue;
					tempmax = max(tempmax, BigInteger.valueOf(targetvalue).multiply(dp[(i - 1)%2][(int)(j - Math.pow(store[i - 1], t))]));
					tempmax = max(tempmax, dp[(i - 1)%2][j]);//ȡģ���Ϳռ临�Ӷ�
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
        System.out.println("����nֵ��");
    	int num=scan.nextInt();
    	scan.close();
		BigInteger n=tempresult(num);
		System.out.println(n);
	}
}