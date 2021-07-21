/**
 * @author attack204
 * date:  2021/11/12
 * email: 757394026@qq.com
 */

import java.io.*;
import java.net.*;
import java.util.*;


public class Client19 {
    DataInputStream dis;
    DataOutputStream dos;

    public static void main(String[] args) {
        Client19 ss = new Client19();
        ss.go();
    }

    public void go() {
        try {
            Socket s = new Socket("localhost", 8080);

            dis = new DataInputStream(s.getInputStream());
            dos = new DataOutputStream(s.getOutputStream());
            System.out.println("连接成功!");
            Scanner in = new Scanner(System.in);
            System.out.println("请输入整数的数量:");
            int n = in.nextInt();
            dos.writeInt(n);
            for (int i = 0; i < n; i++) {
                dos.writeInt(in.nextInt());
            }
            System.out.println("这组整数的和是:" + dis.readInt());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}