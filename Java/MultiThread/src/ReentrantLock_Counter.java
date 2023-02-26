import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Counter {
    private final Lock lock = new ReentrantLock();
    private int count;

    public static void main(String[] args) throws InterruptedException {
        Counter counter = new Counter();
        new Thread(() -> {
            for(int i = 0; i < 100000; i++) {
                counter.add(1);
            }
        }).start();
        new Thread(() -> {
            for(int i = 0; i < 100000; i++) {
                counter.add(1);
            }
        }).start();

        Thread.sleep(2000);
        System.out.print(counter.getCount());
    }
    public int getCount() {
        return count;
    }
    public void add(int n) {
        try {
            if (lock.tryLock(5, TimeUnit.MICROSECONDS)) {
                try {
                    count += n;
                } finally {
                    lock.unlock();
                }
            } else {
                System.out.println("fail");
            }
        } catch (InterruptedException e) {
            System.out.printf("Interrupted");
        }

    }
}