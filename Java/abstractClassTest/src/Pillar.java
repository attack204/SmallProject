/**
 * @author attack204
 * date:  2021/11/9
 * email: 757394026@qq.com
 */
public class Pillar {
    Geometry bottom;
    Double height;
    Pillar(Geometry g, Double h) {
        bottom = g;
        height = h;
    }
    public Double getVolume() {
        return bottom.getArea() * height;
    }
}
