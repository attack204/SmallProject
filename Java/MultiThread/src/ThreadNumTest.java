/**
 * @author attack204
 * date:  2021/11/5
 * email: 757394026@qq.com
 */
public class ThreadNumTest {
//    public
    public static void main(String[] args) {
        int count = 0;
        while(true) {

            System.out.println(++count);
            Thread t = new Thread(()-> {
              //  tt--;
            });
            System.out.println(count);
        }
    }
}
