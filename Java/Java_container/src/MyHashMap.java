import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.concurrent.ConcurrentHashMap;

/**
 * @author attack204
 * date:  2021/10/31
 * email: 757394026@qq.com
 */
public class MyHashMap {
    public static void main(String[] args) {
        LinkedHashMap<String, Integer> myHashMap = new LinkedHashMap<>();
        myHashMap.put("1", 2);
     //   myHashMap.put(22222, "2332");
        System.out.println(myHashMap.get("1"));
        System.out.println(myHashMap.get(22222));

        ConcurrentHashMap<String, Integer> myConcrrentHashMap = new ConcurrentHashMap<>();

        myConcrrentHashMap.put("123", 456);
        System.out.println(myConcrrentHashMap.get("123"));
    }
}
