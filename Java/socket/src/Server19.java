/**
 * @author attack204
 * date:  2021/11/12
 * email: 757394026@qq.com
 */

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Server19 {
    DataInputStream dis;
    DataOutputStream dos;

    public static void main(String[] args) {
        Server19 ss = new Server19();
        ss.go();
    }

    public void go() {
        try {
            ServerSocket ss = new ServerSocket(8080);
            Socket s = ss.accept();
            System.out.println("连接成功!");
            dis = new DataInputStream(s.getInputStream());
            dos = new DataOutputStream(s.getOutputStream());
            int n = dis.readInt();//n 用来计算接受的整数的数量 int sum = 0;
            Integer sum = 0;
            for (int i = 0; i < n; i++)
                sum = Math.max(sum, dis.readInt());
            dos.writeInt(sum);
            dos.close();
            dis.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}