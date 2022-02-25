package LibrarySystem;

import java.io.*;
import java.util.*;

public class Book {
		
	protected class Node{
		protected books t = new books();//结点的值
		protected Node next;//类似指针
		public Node(books t,Node next) {
			this.t = t;
			this.next = next;
		}
		public Node(books t) {
			this(t,null);
		}
	}
	protected  Node head;//头节点
	protected  int size;//结点个数
	//构造函数
	public Book() {
		head = null;
		size = 0;
	}
	public Book(int size) {
		head = null;
		this.size = size;
	}
	public Book(Node head,int size) {
		this.head = head;
		this.size = size;
	}
	//获得首地址
	public Node Head() {
		return head;
	}
	
	//获得书本数
	public int Getsize() {
		return size;
	}
	
	//判断是否为空
	public boolean JudgeEmpty() {
		if(size == 0)return true;
		else return false;
	}
	
	//遍历
	public void ergodic() {
		if(JudgeEmpty() == true) 
		{System.out.print(1);
			return ;//判断是否为空
		}
		Node q = head;
		for (int i = 1 ; i <= size ; i++ ) {//循环输出，以后应该要改成别的
			System.out.println(q.t.bookk);
			q = q.next;
		}
	}
	
	//头插入（因为头节点没有加一个空结点，头插和后面的不一样）
	public void addFirst(books t) {
		Node node = new Node(t);
		node.next = this.head;
		this.head = node;
		this.size++;
	}
	//当无插入位置时，默认插入尾部
	public void addLast(books t) {
		this.add(t, this.size);
	}
	
	//剩余插法
	public void add(books t,int index) {//index为插入的位置
		//先对index进行判断
		if(index == 0) {
			this.addFirst(t);
			return;
		}
		if(index<0||index>size) {
			System.out.println("插入位置错误");
			return;
		}
		//找到插入前位置
		Node ci = this.head;
		for(int i = 0; i < index - 1 ;i++) {
			ci = ci.next;
		}
		Node node = new Node(t);
		//进行插入
		node.next = ci.next;
		ci.next = node;
		//插入完，书数加一
		this.size++;
	}
	
	//文件操作，添加十本书
	public void addbook() {
		books io[] = new books[10];
		for(int i = 0;i<10;i++)
			io[i] = new books();
		int j = 0;
		File file = new File("C:\\Users\\user\\Desktop\\SmallProject\\SmallProject\\Java\\wjzgg_project\\DS\\src\\LibrarySystem\\Books1.txt");
		FileReader f = null;
		BufferedReader f1 = null;
		try {
			f = new FileReader(file);
			f1 = new BufferedReader(f);
			while((io[j].number=f1.readLine())!=null) {
				io[j].number1 = j;
				io[j].bookk = f1.readLine();
				io[j].author = f1.readLine();
				io[j].press = f1.readLine();
				io[j].time = f1.readLine();
				io[j].abstract1 = f1.readLine();
				if(f1.readLine().equals("未借阅"))io[j].in = 1;
				//io[j].in = f1.readLine();
				io[j].type1 = f1.readLine();
				j++;
			}
		}
		catch (Exception e) {
		}
		finally {
			try {
			f1.close();
			f.close();
			}catch (Exception e2) {
		}
		}
		for(int i = 0;i<10;i++)
		this.add(io[i], i);
		this.ergodic();
	}
	//修改书本状态,xz为选择还书还是借书，如果xz==1为还，xz==0为借
	public void modifyIn(int number2,int xz) {
		Node cur = this.head;
		while(cur!=null) {
			if(cur.t.number1 == number2) {
				if(xz == 0)
					cur.t.in = 0;
				else cur.t.in = 1;
			}
			cur = cur.next;
		}
	}

}
class books{//等价于书的结构体
	String time,author,bookk,type1,number,press,abstract1;//时间，作者，书名，类型，编号,出版社,摘要
	int in,number1;//状态，1表示在，0表示不在,number1不显示在屏幕上，只用来排序
}
