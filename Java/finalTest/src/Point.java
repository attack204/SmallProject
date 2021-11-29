/**
 * @author attack204
 * date:  2021/11/14
 * email: 757394026@qq.com
 */
public class Point extends Object{

    public static void main(String[] args) {
        Point point = new Point();
        point.go();
    }
    public void go() {
        Object[] P = new Point[10];
        System.out.println(P.length);
        //the code below is incorrect
//        Point P[] = new Object[10];
//        System.out.println(P.length);
    }
}
