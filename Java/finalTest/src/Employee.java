import java.io.DataOutputStream;
import java.io.FileOutputStream;

/**
 * @author attack204
 * date:  2021/11/14
 * email: 757394026@qq.com
 */
public class Employee {

    static  int a = 1;
    public class Manager extends Employee {
        public static final int b = 2;

    }
    public class Director extends Employee {
        public static final int c = 3;
    }

    public static void main(String[] args) {
        Employee employee = new Employee();
        employee.go();
    }
    public void go() {
        Employee employee = new Manager();
        System.out.println(employee.getClass().getName());
//        DataOutputStream
    }
}
