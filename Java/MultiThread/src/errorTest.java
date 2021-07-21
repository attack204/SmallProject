/**
 * @author attack204
 * date:  2021/11/5
 * email: 757394026@qq.com
 */
public class errorTest {
        // 对象的成员变量
        private static int count = 0;

        public static void main(String[] args) throws InterruptedException {
            // t1线程对变量+5000次
            Thread t1 = new Thread(() -> {
                for (int i = 0; i < 5000; i++) {
                    count++;
                }
            });
            // t2线程对变量-5000次
            Thread t2 = new Thread(() -> {
                for (int i = 0; i < 5000; i++) {
                    count--;
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
