/**
 * @author attack204
 * date:  2021/11/5
 * email: 757394026@qq.com
 */
public class safeTest {
    private static int count = 0;

    private static Object lock = new Object();

    private static Object lock2 = new Object();

    // t1线程和t2对象都是对同一对象加锁。保证了线程安全。此段代码无论执行多少次，结果都是0
    public static void main(String[] args) throws InterruptedException {
        Thread t1 = new Thread(() -> {
            for (int i = 0; i < 5000; i++) {
                synchronized (lock) {
                    count++;
                    System.out.println("add");
                }
            }
        });
        Thread t2 = new Thread(() -> {
            for (int i = 0; i < 5000; i++) {
                synchronized (lock) {
                    count--;
                    System.out.println("desc");
                }
            }
        });

        t1.start();
        t2.start();

        // 让t1 t2都执行完
        t1.join();
        t2.join();
        System.out.println(count);
    }
}
