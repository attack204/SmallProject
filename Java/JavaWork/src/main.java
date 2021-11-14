/**
 *
 */


import java.util.Random;
import java.util.Scanner;

/**
 * @author 安彤
 *
 */
public class main {

    /**
     * @param args
     */
    public static void main(String[] args) {
        // TODO Auto-generated method stub
        //question1();
        //question2();
        //question3();
        //question4();
        //question5();
        //question6();
        //question7(5,200,100);
        question8();

    }

    private static void question8() {
        // TODO Auto-generated method stub
        System.out.println("请输入第一个矩阵的行数与列数：");
        Scanner input=new Scanner(System.in);
        int h1=input.nextInt();
        int l1=input.nextInt();
        System.out.println("请输入第二个矩阵的行数与列数：（小提示：第一个矩阵的列数需要等于第二个矩阵的行数）");
        int h2=input.nextInt();
        int l2=input.nextInt();
        int [][]a=new int[h1][l1];
        int [][]b=new int[h2][l2];
        if(h1!=l2)
            System.out.println("第一个矩阵的列数不等于第二个矩阵的行数，不可以做矩阵的乘法");
        else {
            System.out.println("请输入第一个矩阵:");
            for(int i=0;i<h1;i++)
                for(int j=0;j<l1;j++)
                    a[i][j]=input.nextInt();
            System.out.println("请输入第二个矩阵:");
            for(int i=0;i<h2;i++)
                for(int j=0;j<l2;j++)
                    b[i][j]=input.nextInt();
            int[][] c=new  int[h1][l2];
            for(int i=0;i<h1;i++)
                for(int j=0;j<l2;j++)
                    for(int k=0;k<l1;k++)
                        c[i][j] += a[i][k] * b[k][j];
            System.out.println("输出乘法矩阵:");
            for(int i=0;i<h1;i++) {
                for(int j=0;j<l2;j++)
                    System.out.printf("%d ",c[i][j]);
                System.out.println("");
            }
        }
    }

    private static void question7(int n,int max,int min) {
        int[] arr=new int[max-min+1];
        Random r = new Random();
        int x;
        for(int i=0;i<n;i++) {
            x=r.nextInt(max+1-min)+min;
            if(arr[x-min]==1)
                continue;
            else {
                System.out.println(x);
                arr[x-min]=1;
            }
        }
    }

    private static void question6() {
        // TODO Auto-generated method stub
        int[] n = new int[100];
        int[] m = new int[1000];
        int i,j;
        for(i=0;i<1000;i++) {
            m[i]=(int)(Math.random()*100);
        }
        for(i=0;i<100;i++) {
            for(j=0;j<1000;j++) {
                if((i+1)==m[j]) {
                    n[i]+=1;
                }
            }
            System.out.println(i+1+"出现了"+n[i]);
        }
    }

    private static void question5() {
        // TODO Auto-generated method stub
        Scanner input=new Scanner(System.in);
        System.out.println("请输入正整数n：");
        int n=input.nextInt();
        int i,j;
        for(i=2;i<=n;i++) {
            for(j=2;j<i;j++) {
                if(i%j==0)
                    break;
            }
            if(j==i)
                System.out.println(i);
        }

    }

    private static void question4() {
        // TODO Auto-generated method stub
        Scanner input=new Scanner(System.in);
        System.out.println("请输入正整数n：");
        int n=input.nextInt();
        int i,j,sum=0;
        System.out.println("输出1-n所有完全数");
        for(i=1;i<=n;i++) {
            sum=0;
            for(j=1;j<i;j++) {
                if(i%j==0) {
                    sum+=j;
                }
            }
            if(i==sum) {
                System.out.println(i);
            }
        }
    }

    private static void question3() {
        // TODO Auto-generated method stub
        int i;
        int x,y,z;
        System.out.println("输出三位数水仙数:");
        for(i=100;i<=999;i++) {
            x=i%10;
            y=((i-x)/10)%10;
            z=(i-x)/100;
            if(i==x*x*x+y*y*y+z*z*z) {
                System.out.println(i);
            }
        }
    }

    private static void question1() {
        // TODO Auto-generated method stub
        int i;
        float sum=0;
        Scanner input=new Scanner(System.in);
        System.out.println("请输入n：");
        int n=input.nextInt();
        for(i=1;i<=n;i++) {
            sum+=(float)1/(2*i-1);
        }
        System.out.println(sum);
    }

    private static void question2() {
        // TODO Auto-generated method stub
        Scanner input=new Scanner(System.in);
        System.out.println("请输入正整数m：");
        int m=input.nextInt();
        System.out.println("请输入正整数n：");
        int n=input.nextInt();
        int p=0, x=m,y=n;
        //辗转相除法求最大公约数
        if(m<n) {
            p=m;
            m=n;
            n=p;
        }
        while(m%n!=0) {
            p=m%n;
            m=n;
            n=p;
        }
        System.out.println("最小公倍数："+x*y/n);
        System.out.println("最大公约数："+n);
    }
}
