package LibrarySystem;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;

import javax.swing.*;

public class userInterface implements ActionListener{
	static Book newBook=new Book();
	JFrame frame=new JFrame("图书馆管理系统-首页");
	JButton button1=new JButton("用户登录");
	JButton button2=new JButton("管理登录");
	JButton button3=new JButton("使用指南");
	JButton button4=new JButton("退出系统");
	public userInterface() {
		// TODO Auto-generated constructor stub
		newBook.addbook();
	}
	public void go() {
		Container contentPane=frame.getContentPane();
		contentPane.setLayout(new GridLayout(5,2));
		
		JPanel panel1=new JPanel();
		JPanel panel2=new JPanel();
		JPanel panel3=new JPanel();
		JPanel panel4=new JPanel();
		JPanel panel5=new JPanel();
		
		button1.addActionListener(this);
		button2.addActionListener(this);
		button3.addActionListener(this);
		button4.addActionListener(this);
		
		panel1.add(new JLabel("欢迎使用图书馆管理系统!"));
		panel2.add(button1);
		panel3.add(button2);
		panel4.add(button3);
		panel5.add(button4);
		
		contentPane.add(panel1);
		contentPane.add(panel2);
		contentPane.add(panel3);
		contentPane.add(panel4);
		contentPane.add(panel5);
		
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(300,300);
		frame.setVisible(true);
	}
	public void actionPerformed(ActionEvent e) {
		JButton button=(JButton)e.getSource();
		if(button==button1) {
			studentLogin log=new studentLogin();
		}
		else if(button==button2) {
			managerLogin log=new managerLogin();
		}
		else if(button==button3) {
			String message="图书馆入馆须知：\n";
			message+="1.读者凭本人有效校园卡、借书证入馆；校外读者在学府大道校区图书馆办公室办理相关手续入馆\n";
			message+="2.注意仪容仪表，言谈举止文明大方，衣着整洁，勿穿背心、拖鞋入馆，勿在馆内座位躺卧和有其\n它不雅举止\n";
			message+="3.图书馆是重点防火单位，严禁在馆内任何地方吸烟、用火\n";
			message+="4.保持图书馆内安静，手机或电脑等设备调至静音。禁止在馆内喧哗、朗读或大声接打手机，尤其\n禁止在阅览区域接打手机\n";
			message+="用户使用指南：\n";
			message+="1.登录系统需要提供有效的账号密码，本系统不支持在线修改密码\n";
			message+="2.所借图书在指定日期未归还时会自动变为归还状态，请及时将书籍送回图书馆\n";
			message+="3.图书馆类别分布可向前台工作人员咨询，捐赠图书在系统内部填写信息后请在三个工作日之内将\n书交给管理人员\n";
			message+="4.馆藏中暂时未有的书籍可以及时向管理人员反馈，待反馈数量到一定程度时会更新馆藏";
			JOptionPane.showMessageDialog(frame, message);
		}
		else {
			System.exit(0);
		}
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		userInterface interface0=new userInterface();
		interface0.go();
	}
}
