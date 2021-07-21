/**
 * @author attack204
 * date:  2021/11/9
 * email: 757394026@qq.com
 */

public class test {
    public static void main(String[] args) {
        Circle circle = new Circle(1.23);
        System.out.println(circle.getArea());
        Rectangle rectangle = new Rectangle(1.1, 2.2);
        Pillar pillar = new Pillar(circle, 2.2);
        System.out.println(rectangle.getArea());
        System.out.println(pillar.getVolume());
    }
}
