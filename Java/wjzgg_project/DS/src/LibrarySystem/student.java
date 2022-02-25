package LibrarySystem;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

import javax.swing.*;
import javax.swing.table.TableColumn;

import LibrarySystem.Book.Node;

class searchBookIn implements ActionListener {
    int flag = 0;
    JFrame frame1_2 = new JFrame("查阅图书-用户");
    JButton button1 = new JButton("查询");
    JButton button2 = new JButton("退出");
    JRadioButton button3 = new JRadioButton("书名");
    JRadioButton button4 = new JRadioButton("作者");
    JRadioButton button5 = new JRadioButton("出版社");
    JRadioButton button6 = new JRadioButton("类别");
    ButtonGroup group = new ButtonGroup();
    JTextField field = new JTextField(15);
    JPanel panel1 = new JPanel();
    JPanel panel2 = new JPanel();
    JPanel panel3 = new JPanel();
    JPanel panel4 = new JPanel();
    JPanel panel5 = new JPanel();

    public searchBookIn() {
        // TODO Auto-generated constructor stub
        Container contentPane = frame1_2.getContentPane();
        contentPane.setLayout(new GridLayout(5, 4));
        group.add(button3);
        group.add(button4);
        group.add(button5);
        group.add(button6);

        field.setEditable(true);
        panel1.add(new JLabel("请选择查询方式（单选）："));
        panel2.add(button3);
        panel2.add(button4);
        panel2.add(button5);
        panel2.add(button6);
        panel3.add(new JLabel("请输入完整的查询关键字："));
        panel4.add(field);
        panel5.add(button1);
        panel5.add(button2);

        contentPane.add(panel1);
        contentPane.add(panel2);
        contentPane.add(panel3);
        contentPane.add(panel4);
        contentPane.add(panel5);

        ButtonListener listener = new ButtonListener();
        button1.addActionListener(listener);
        button2.addActionListener(listener);
        button3.addActionListener(this);
        button4.addActionListener(this);
        button5.addActionListener(this);
        button6.addActionListener(this);

        frame1_2.setSize(250, 300);
        frame1_2.setVisible(true);
    }

    public void actionPerformed(ActionEvent e) {
        JRadioButton button0 = (JRadioButton) e.getSource();
        if (button0 == button3) {
            flag = 1;
        } else if (button0 == button4) {
            flag = 2;
        } else if (button0 == button5) {
            flag = 3;
        } else if (button0 == button6) {
            flag = 4;
        }
    }

    class ButtonListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            JButton button0 = (JButton) e.getSource();
            if (button0 == button1) {
                if (flag == 0) {
                    JOptionPane.showMessageDialog(frame1_2, "输入无效！", "An error", JOptionPane.ERROR_MESSAGE);
                } else {
                    searchBook searchone = new searchBook();
                    switch (flag) {
                        case 1:
                            searchone.ergodic1(field.getText());
                            break;
                        case 2:
                            searchone.ergodic2(field.getText());
                            break;
                        case 3:
                            searchone.ergodic3(field.getText());
                            break;
                        case 4:
                            searchone.ergodic4(field.getText());
                            break;
                    }
                    searchone.go();
                }
            } else if (button0 == button2) {
                frame1_2.setVisible(false);
            }
        }
    }
}

class searchBook implements ActionListener {
    JFrame frame1_2_1 = new JFrame("查询结果");
    ArrayList<books> booklist = new ArrayList<>();
    Map<String, JButton> buttonevent = new HashMap<>();
    Map<String, books> maplist = new HashMap<String, books>();
    ArrayList<JButton> buttonlist = new ArrayList<>();

    public void ergodic1(String name) {
//		System.out.println("“"+name+"”");
//		if(name.equals("百年孤独")) {System.out.println("名字匹配");}
        Node temp = userInterface.newBook.Head();
        for (int i = 0; i < userInterface.newBook.Getsize(); i++) {
//			System.out.println("TEST");
//			System.out.print(temp.t.bookk);
//			System.out.println(temp.t.abstract1);
//			if(temp.t.bookk.equals("百年孤独")) {System.out.println("链表匹配");}
            if (temp.t.bookk.equals(name)) {
//				System.out.println("IN IF AND MATCHED");
                booklist.add(temp.t);
                JButton button = new JButton("借阅");
                buttonlist.add(button);
            }
            temp = temp.next;
        }
    }

    public void ergodic2(String author) {
        Node temp = userInterface.newBook.Head();
        for (int i = 0; i < userInterface.newBook.Getsize(); i++) {
//			System.out.println("TEST");
//			System.out.print(temp.t.author);
            if (temp.t.author.equals(author)) {
//				System.out.println("IN IF AND MATCHED");
                booklist.add(temp.t);
                JButton button = new JButton("借阅");
                buttonlist.add(button);
            }
            temp = temp.next;
        }
    }

    public void ergodic3(String press) {
        Node temp = userInterface.newBook.Head();
        for (int i = 0; i < userInterface.newBook.Getsize(); i++) {
//			System.out.println("TEST");
//			System.out.print(temp.t.press);
            if (temp.t.press.equals(press)) {
//				System.out.println("IN IF AND MATCHED");
                booklist.add(temp.t);
                JButton button = new JButton("借阅");
                buttonlist.add(button);
            }
            temp = temp.next;
        }
    }

    public void ergodic4(String type) {
        Node temp = userInterface.newBook.Head();
        for (int i = 0; i < userInterface.newBook.Getsize(); i++) {
//			System.out.println("TEST");
            System.out.print(temp.t.type1);
            if (temp.t.type1.equals(type)) {
//				System.out.println("IN IF AND MATCHED");
                booklist.add(temp.t);
                JButton button = new JButton("借阅");
                buttonlist.add(button);
            }
            temp = temp.next;
        }
    }

    public void go() {
        String[] columnNames = {"ISBN", "书名", "作者", "出版社", "出版时间", "类别", "摘要"};
        String[][] obj = new String[booklist.size()][7];
        books enBook = new books();
        for (int i = 0; i < booklist.size(); i++) {
            for (int j = 0; j < 7; j++) {
                enBook = booklist.get(i);
                switch (j) {
                    case 0:
                        obj[i][j] = enBook.number;
                        break;
                    case 1:
                        obj[i][j] = enBook.bookk;
                        break;
                    case 2:
                        obj[i][j] = enBook.author;
                        break;
                    case 3:
                        obj[i][j] = enBook.press;
                        break;
                    case 4:
                        obj[i][j] = enBook.time;
                        break;
                    case 5:
                        obj[i][j] = enBook.type1;
                        break;
                    case 6:
                        obj[i][j] = enBook.abstract1;
                        break;
                }
            }
        }
        JTable table = new JTable(obj, columnNames);
        table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);  //关闭表格的自动调整功能，以便显示滚动条
        TableColumn column = null;
        int columns = table.getColumnCount();
        for (int i = 0; i < columns; i++) {
            column = table.getColumnModel().getColumn(i);
            switch (i) {
                case 0:
                    column.setPreferredWidth(70);
                    break;
                case 1:
                    column.setPreferredWidth(120);
                    break;
                case 2:
                    column.setPreferredWidth(70);
                    break;
                case 3:
                    column.setPreferredWidth(200);
                    break;
                case 4:
                    column.setPreferredWidth(70);
                    break;
                case 5:
                    column.setPreferredWidth(70);
                    break;
                case 6:
                    column.setPreferredWidth(600);
                    break;
            }
        }
        table.setRowHeight(30);
//		System.out.println("表格行高："+table.getRowHeight());
        Container contentPane = frame1_2_1.getContentPane();
        JScrollPane scrollpane = new JScrollPane(table);
        JPanel panel = new JPanel();
        JLabel label = new JLabel("");
        label.setPreferredSize(new Dimension(50, 12));
        panel.add(label);
        JButton button0;
        for (int i = 0; i < buttonlist.size(); i++) {
            button0 = buttonlist.get(i);
            panel.add(button0);
        }
        JSplitPane splitpane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, false, scrollpane, panel);
        splitpane.setDividerLocation(800);  //分割线的位置
        splitpane.setDividerSize(0);  //设置分割线的宽度
        splitpane.setEnabled(false);  //设置分割线不可拖动

        for (int i = 0; i < buttonlist.size(); i++) {
            button0 = buttonlist.get(i);
            enBook = booklist.get(i);
            button0.setActionCommand(String.valueOf(i));
            button0.addActionListener(this);
            buttonevent.put(String.valueOf(i), button0);
            maplist.put(String.valueOf(i), enBook);
        }

        contentPane.add(splitpane);
        frame1_2_1.setSize(900, 500);
        frame1_2_1.setVisible(true);
    }

    public void actionPerformed(ActionEvent e) {
        buttonevent.get(e.getActionCommand()).setText("Selected");  //得到button信息
        for (Map.Entry<String, JButton> item : buttonevent.entrySet()) {  //for-each遍历
            String key = item.getKey();  //得到key值
            JButton button = item.getValue();  //得到button值
          //  System.out.println(button);
          //  System.out.println(buttonevent.get(e.getActionCommand()));
            if (buttonevent.get(e.getActionCommand()).equals(button)) {
                System.out.println("Success");
                for (Map.Entry<String, books> item0 : maplist.entrySet()) {
                    String key0 = item0.getKey();
                    books book = item0.getValue();
                    if (key.equals(key0)) {
                        System.out.println("匹配");
                        readBook read = new readBook();  //匹配之后进入下一个类的界面
                        read.receiveBook(book);
                        read.go();
                    }
                }
            }
        }
//		String command=(String)e.getActionCommand();
        //for-each遍历 找出对应按钮响应的书本信息
//		for(Map.Entry<String, books>item:maplist.entrySet()) {
//			String key=item.getKey();
//			books book=item.getValue();
//			if(key.equals(command)) {
//				readBook read=new readBook();
//				read.receiveBook(book);
//			}
//		}
    }
}

class readBook {
    private books receiver = new books();
    JFrame frame1_2_2 = new JFrame("借阅书籍-用户");

    public void receiveBook(books book) {
        receiver = book;
    }

    public void go() {
        if (receiver.in == 0) {
            JOptionPane.showMessageDialog(frame1_2_2, "抱歉，该书已被借阅！", "An notice", JOptionPane.WARNING_MESSAGE);
        } else if (receiver.in == 1) {
            String message = "借阅成功！\n";
            message += "编号：" + receiver.number + "\n";
            message += "书名：" + receiver.bookk + "\n";
            message += "作者：" + receiver.author + "\n";
            message += "出版：" + receiver.press + "\n";
            message += "时间：" + receiver.time + "\n";
            message += "类型：" + receiver.type1 + "\n";
            message += "摘要：" + receiver.abstract1 + "\n";
            JOptionPane.showMessageDialog(frame1_2_2, message);
//			Node temp=userInterface.newBook.Head();
//			for(int i=0; i<userInterface.newBook.Getsize(); i++) {
//				if(receiver.number.equals(temp.t.number)) {
//					
//				}
//			}
        }
    }
}

class returnBookIn {
    JFrame frame1_3 = new JFrame("归还图书-用户");
    JPanel panel = new JPanel();

    public returnBookIn() {
        // TODO Auto-generated constructor stub
        Container contentPane = frame1_3.getContentPane();
        contentPane.setLayout(new GridLayout(2, 1));
        panel.add(new JLabel("您的借阅信息如下;"));
        String[] columnNames = {"ISBN", "书名", "作者", "出版社", "类别", "  "};
        String[][] obj = new String[2][6];
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 6; j++) {
                switch (j) {
                    case 0:
                        obj[i][j] = "00001";
                        break;
                    case 1:
                        obj[i][j] = "百年孤独";
                        break;
                    case 2:
                        obj[i][j] = "马尔克斯";
                        break;
                    case 3:
                        obj[i][j] = "陕西人民出版社";
                        break;
                    case 4:
                        obj[i][j] = "文学";
                        break;
                    case 5:
                        obj[i][j] = "归还";
                        break;
                }
            }
        }
        JTable table = new JTable(obj, columnNames);
        TableColumn column = null;
        int columns = table.getColumnCount();
        for (int i = 0; i < columns; i++) {
            column = table.getColumnModel().getColumn(i);
            column.setPreferredWidth(100);
        }
        contentPane.add(panel);
        contentPane.add(table);
        frame1_3.setSize(500, 300);
        frame1_3.setVisible(true);
    }
}

class giveBookIn implements ActionListener {
    JFrame frame1_4 = new JFrame("捐赠图书-用户");
    JButton button1 = new JButton("提交");
    JButton button2 = new JButton("退出");
    JPanel panel1 = new JPanel();
    JPanel panel2 = new JPanel();
    JPanel panel3 = new JPanel();
    JPanel panel4 = new JPanel();
    JPanel panel5 = new JPanel();
    JPanel panel6 = new JPanel();
    JPanel panel7 = new JPanel();
    JPanel panel8 = new JPanel();
    JPanel panel9 = new JPanel();
    JTextField field1 = new JTextField(15);
    JTextField field2 = new JTextField(15);
    JTextField field3 = new JTextField(15);
    JTextField field4 = new JTextField(15);
    JTextField field5 = new JTextField(15);
    JTextField field6 = new JTextField(15);
    JTextField field7 = new JTextField(15);

    public giveBookIn() {
        // TODO Auto-generated constructor stub
        Container contentPane = frame1_4.getContentPane();
        contentPane.setLayout(new GridLayout(9, 2));

        field1.setEditable(true);
        field2.setEditable(true);
        field3.setEditable(true);
        field4.setEditable(true);
        field5.setEditable(true);
        field6.setEditable(true);
        field7.setEditable(true);

        panel1.add(new JLabel("请完整填写所捐赠的图书信息"));
        panel2.add(new JLabel("编号"));
        panel2.add(field1);
        panel3.add(new JLabel("书名"));
        panel3.add(field2);
        panel4.add(new JLabel("作者"));
        panel4.add(field3);
        panel5.add(new JLabel("出版"));
        panel5.add(field4);
        panel6.add(new JLabel("时间"));
        panel6.add(field5);
        panel7.add(new JLabel("摘要"));
        panel7.add(field6);
        panel8.add(new JLabel("类别"));
        panel8.add(field7);
        panel9.add(button1);
        panel9.add(button2);

        button1.addActionListener(this);
        button2.addActionListener(this);

        contentPane.add(panel1);
        contentPane.add(panel2);
        contentPane.add(panel3);
        contentPane.add(panel4);
        contentPane.add(panel5);
        contentPane.add(panel6);
        contentPane.add(panel7);
        contentPane.add(panel8);
        contentPane.add(panel9);

        frame1_4.setSize(300, 450);
        frame1_4.setVisible(true);
    }

    public void actionPerformed(ActionEvent e) {
        JButton button = (JButton) e.getSource();
        if (button == button1) {
            if (field2.getText().equals("") || field3.getText().equals("") || field4.getText().equals("") || field7.getText().equals("")) {
                JOptionPane.showMessageDialog(frame1_4, "输入无效！", "An error", JOptionPane.ERROR_MESSAGE);
            } else {
                books added = new books();
                added.number = field1.getText();
                added.bookk = field2.getText();
                added.author = field3.getText();
                added.press = field4.getText();
                added.time = field5.getText();
                added.abstract1 = field6.getText();
                added.type1 = field7.getText();

                userInterface.newBook.addLast(added);
                frame1_4.dispose();
                JOptionPane.showMessageDialog(frame1_4, "捐赠成功！", "An notice", JOptionPane.WARNING_MESSAGE);
                System.out.println(added.bookk);
                userInterface.newBook.ergodic();
            }
        } else if (button == button2) {
            frame1_4.setVisible(false);
        }
    }
}

public class student implements ActionListener {
    JFrame frame1_1 = new JFrame("图书馆借阅系统-用户");
    JButton button1 = new JButton("查阅图书");
    JButton button2 = new JButton("归还图书");
    JButton button3 = new JButton("捐赠图书");
    JButton button4 = new JButton("退出系统");

    JPanel panel1 = new JPanel();
    JPanel panel2 = new JPanel();
    JPanel panel3 = new JPanel();
    JPanel panel4 = new JPanel();
    JPanel panel5 = new JPanel();

    public student() {
        // TODO Auto-generated constructor stub
        Container contentPane = frame1_1.getContentPane();
        contentPane.setLayout(new GridLayout(5, 2));

        panel1.add(button1);
        panel2.add(button2);
        panel3.add(button3);
        panel4.add(button4);
        panel5.add(new JLabel("遇到问题请电话咨询0349-1008677"));
        contentPane.add(panel1);
        contentPane.add(panel2);
        contentPane.add(panel3);
        contentPane.add(panel4);
        contentPane.add(panel5);

        button1.addActionListener(this);
        button2.addActionListener(this);
        button3.addActionListener(this);
        button4.addActionListener(this);

        frame1_1.setSize(300, 300);
        frame1_1.setVisible(true);
    }

    public void actionPerformed(ActionEvent e) {
        JButton button0 = (JButton) e.getSource();
        int tag = 0;
        if (button0 == button1) {
//			frame1_1.setVisible(false);
            searchBookIn search = new searchBookIn();
        } else if (button0 == button2) {
//			frame1_1.setVisible(false);
            returnBookIn returnB = new returnBookIn();
        } else if (button0 == button3) {
//			frame1_1.setVisible(false);
            giveBookIn give = new giveBookIn();
        } else if (button0 == button4) {
            frame1_1.setVisible(false);
        }
    }
//	public static void main(String[] args) {
//		// TODO Auto-generated method stub
//
//	}

}
