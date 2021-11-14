import java.io.*;

/**
 * @author attack204
 * date:  2021/11/13
 * email: 757394026@qq.com
 */
public class readFile {

    public static void main(String[] args) {
        try {
            FileInputStream fis = new FileInputStream("name.txt");
             byte[] buffer = new byte[2048];
            Integer num = 0;
            while ((num = fis.read(buffer)) != -1) {
                System.out.println(new String(buffer, 0, num));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
