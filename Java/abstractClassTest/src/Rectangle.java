/**
 * @author attack204
 * date:  2021/11/9
 * email: 757394026@qq.com
 */
public class Rectangle extends Geometry{
    Double height, weight;
    Rectangle(Double a, Double b) {
        height = a;
        weight = b;
    }
    @Override
    Double getArea() {
        return height * weight;
    }
}
