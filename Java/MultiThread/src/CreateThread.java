/**
 * @author attack204
 * date:  2021/11/13
 * email: 757394026@qq.com
 */
public class CreateThread {

    public class MyThread extends Thread {//继承Thread类
        public void run() {
            System.out.println("extends Thread to create Thread");
        }
    }
    public class MyTread2 implements Runnable {
        public void run() {
            System.out.println("implements Runnable to create Thread");
        }
    }
    public static void main(String[] args) {
        CreateThread createThread = new CreateThread();
        createThread.go();
    }
    public void go() {
    //type1
        MyThread myThread = new MyThread();
        myThread.run();
    //type2
        MyTread2 myTread2 = new MyTread2();
        Thread thread = new Thread(myTread2);
        thread.start();

    }

}
