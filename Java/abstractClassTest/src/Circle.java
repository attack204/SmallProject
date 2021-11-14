/**
 * @author attack204
 * date:  2021/11/9
 * email: 757394026@qq.com
 */
public class Circle extends Geometry{
    Double radius;
    Circle(Double r) {
        radius = r;
    }
    @Override
    Double getArea() {
        return radius * radius * Math.acos(-1);

    }
}
