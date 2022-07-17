import java.util.concurrent.Callable;

public class Calculate implements Callable<Long> {
    private Long l;
    private Long r;

    private Long limit;

    public Calculate(Long l, Long r, Long limit) {
        this.l = l;
        this.r = r;
        this.limit = limit;
    }
    @Override
    public Long call(){
        Long ans = 0L;
        for(Long i = l; i <= r; i++) {
            ans += i ^ limit;
        }
        return ans;
    }
}
