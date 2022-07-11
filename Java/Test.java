import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutionException;

class Test {

    public static void main(String []args) {
        Test test = new Test();
        test.run();
    }

    public abstract class AbstractCalculate<T> {
        private String calculateName;
        private int calculateId;
        public void setCalculateName(String _calculateName) {
            this.calculateName = _calculateName;
        }
        //abstract class不实现的方法需要生命为abstract methods
        public abstract T calcSum(T a, T b) throws Exception;
    }
    public class SumCalculate extends AbstractCalculate<Integer> {
        @Override
        public Integer calcSum(Integer a, Integer b) throws Exception{
            if(a < 0 || b < 0) {
                throw new Exception("both number aren't allow less than zero");
            }
            return a + b;
        }
    }
    void run() {
        SumCalculate sumCalculate = new SumCalculate();
        try {
            Integer ans = sumCalculate.calcSum(1, 2);
            System.out.println(ans);
            Integer ansTest2 = sumCalculate.calcSum(-1, 0);
            System.out.println(ansTest2);
        } catch (Exception e) {
            e.printStackTrace();
        }

    }
}