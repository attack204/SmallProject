package LibrarySystem;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

class managerAccount{
	protected String name[];
	protected String password[];
	
	public managerAccount() {
		// TODO Auto-generated constructor stub
		name=new String[2];
		password =new String[2];
		name[0]="202100040301";
		name[1]="202100040302";
		password[0]="1234";
		password[1]="5678";
	}
}

public class managerLogin implements ActionListener{
	JFrame frame2=new JFrame("管理员系统-登录");
	JButton button1=new JButton("提交");
	JButton button2=new JButton("退出");
	
	JLabel label1=new JLabel("请提供正确的管理员账户，切勿泄露！");
	JLabel label2=new JLabel("账户");
	JLabel label3=new JLabel("密码");
	JTextField field1=new JTextField(15);
	JTextField field2=new JPasswordField(15);
	
	JPanel panel1=new JPanel();
	JPanel panel2=new JPanel();
	JPanel panel3=new JPanel();
	JPanel panel4=new JPanel();
	
	managerAccount accounts=new managerAccount();
	public managerLogin() {
		// TODO Auto-generated constructor stub
		
		Container contentPane=frame2.getContentPane();
		contentPane.setLayout(new GridLayout(4,2));
		
		field1.setEditable(true);
		field2.setEditable(true);
		
		panel1.add(label1);
		panel2.add(label2);
		panel2.add(field1);
		panel3.add(label3);
		panel3.add(field2);
		panel4.add(button1);
		panel4.add(button2);
		
		contentPane.add(panel1);
		contentPane.add(panel2);
		contentPane.add(panel3);
		contentPane.add(panel4);
		
		button1.addActionListener(this);
		button2.addActionListener(this);
		frame2.setSize(300,200);
		frame2.setVisible(true);
	}
	public void actionPerformed(ActionEvent e) {
		JButton button0=(JButton)e.getSource();
		int tag=0;
		if(button0==button1) {
			for(int i=0; i<2; i++) {
				if(accounts.name[i].equals(field1.getText())&&
						accounts.password[i].equals(field2.getText()))
				{
					tag=1;
				}
			}
			if(tag==0) {
				JOptionPane.showMessageDialog(frame2,"账号或密码错误","An error",JOptionPane.ERROR_MESSAGE);
			}
		}
		else if(button0==button2) {
			frame2.setVisible(false);
		}
	}
}
