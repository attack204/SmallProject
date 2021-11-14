import java.io.*;
import java.util.ArrayList;

/**
 * @author attack204
 * date:  2021/11/13
 * email: 757394026@qq.com
 */
public class fileTest {
    public class Student {
        String number;
        String name;
        String age;
        String averageScore;
        Student(String number, String name, String age, String averageScore) {
            this.number = number;
            this.name = name;
            this.age = age;
            this.averageScore = averageScore;
        }
        String getNumber() {
            return this.number;
        }
        String getName() {
            return this.name;
        }
        String getAge() {
            return this.age;
        }
        String getAverageScore() {
            return this.averageScore;
        }
    }

    public void addBooks(String fileName) {
        try {
            FileOutputStream fileOutputStream = new FileOutputStream(fileName);
            DataOutputStream dos = new DataOutputStream(fileOutputStream);
            ArrayList<Student> arrayList = new ArrayList<>();
            arrayList.add(new Student("151110101", "张三", "21", "80.5"));
            arrayList.add(new Student("151110102", "李四", "21", "83.0"));
            arrayList.add(new Student("151110103", "王五", "22", "95.6"));
            for (Student student : arrayList) {
                dos.writeUTF(student.getNumber());
                dos.writeUTF(student.getName());
                dos.writeUTF(student.getAge());
                dos.writeUTF(student.getAverageScore());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
    public void getBooks(String fileName) {
        try {
            FileInputStream fileInputStream = new FileInputStream(fileName);
            DataInputStream dis = new DataInputStream(fileInputStream);
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 4; j++) {
                    System.out.println(dis.readUTF());
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        fileTest fileTest = new fileTest();
        fileTest.go();
    }
    public void go() {
        addBooks("name.txt");
        getBooks("name.txt");
    }
}
