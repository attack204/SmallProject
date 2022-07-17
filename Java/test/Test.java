import java.util.concurrent.*;

class Test {
    private int SIZE = 4;
    private Long limit = 4000000000L;
    private Long ans[] = new Long[SIZE];
    public static void main(String[] args) {
        long startTime = System.currentTimeMillis();
        Test test = new Test();
        test.run();
        long endTime = System.currentTimeMillis();
        System.out.println("程序运行时间： "+(endTime - startTime)+"ms");
    }

    void run() {
        ThreadPoolExecutor executor = new ThreadPoolExecutor(
                SIZE,
                20,
                100,
                TimeUnit.SECONDS,
                new LinkedBlockingQueue<>(100),
                new ThreadPoolExecutor.AbortPolicy()); //拒绝策略
        Long base = limit / SIZE;

        Future<Long> []future = (Future<Long>[]) new Future<?> [SIZE];
        try {
            for(Integer i = 0; i < SIZE; i++) {
                Long l = i * base + 1, r = l + base;
                future[i] = executor.submit(new Calculate(l, r, limit));
            }
            Long ans = 0L;
            for(Integer i = 0; i < SIZE; i++) {
                ans += future[i].get();
            }
            System.out.println(ans);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
