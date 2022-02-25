package LibrarySystem;

import LibrarySystem.Book.Node;
import LibrarySystem.books;
import java.io.*;
import java.util.*;

public class manager extends Book{
	public manager(Node head,int size) {
		this.head = head;
		this.size = size;
	}
	//删除第一本书,返回书名
	public String removeFirst() {
		if(this.head == null) {
			System.out.println("无树可删除");
			return "无";
		}
		Node delNode = this.head;
		this.head = this.head.next;
		delNode.next = null;
		this.size--;
		return delNode.t.bookk;
	}
	
	//删除最后一本本书,返回书名
	public String removeLast() {
		if(this.head == null) {
			System.out.println("无树可删除");
			return "无";
			}
		//当只有一本书
		if(this.Getsize() == 1)
			return this.removeFirst();
		Node cur = this.head;
		Node pre = this.head;
		while(cur.next != null) {
			pre = cur;
			cur = cur.next;
		}
		pre.next = cur.next;
		this.size--;
		return cur.t.bookk;
		
	}
	
	//删除书,返回书名
	public String remove(String q) {
		if(this.head == null) {
			System.out.println("无树可删除");
			return "无";
			}
		//先判断删除的结点是不是头结点
		while(head!=null&&head.t.number.equals(q)) {
			head = head.next;
			this.size--;
		}
		Node p = this.head;
		while(p!=null&&p.next!=null) {//对链表进行遍历查找
			if(p.next.t.number.equals(q)) {
				this.size--;
				Node qp = p.next;
				p.next = p.next.next;
				return qp.t.number;
			}
			else p = p.next;
		}
		return "此编号的书不存在或已经借出";	
	}
	
	//排序，通过sumber1序号,调用时用list
	public Node List(Node head) {
		quickSort(head,null);
		return head;
	}
	public void quickSort(Node head,Node end) {
		if(head != end) {
			Node node = partion(head,end);
			quickSort(head,node);
			quickSort(node.next,end);
		}
	}
	public static Node partion(Node head,Node end) {
		Node p1 = head,p2 = head.next;
		//到队尾才停
		while(p2 != end) {
			if(p2.t.number1 < head.t.number1) {
				p1 = p1.next;
				books temp = p1.t;
				p1.t = p2.t;
				p2.t = temp;
			}
			p2 = p2.next;
		}
		if(p1 != head) {
			books temp = p1.t;
			p1.t = head.t;
			head.t = temp;
		}
		return p1;
	}
	
	//用于输入所要插入的书的数据，先调用此函数再插入
	public void addbook(books book) {
		//time,author,bookk   时间，作者，书名
		//type1,number,press,abstract1   类型，编号,出版社,摘要
		//in,number1;//状态，1表示在，0表示不在,number1不显示在屏幕上，只用来排序
		Scanner input = new Scanner(System.in);
		System.out.println("输入书籍编号(不用加0000，会自动增加):");
		book.number1 = input.nextInt();
		if(book.number1<10)
			book.number = "0000"+String.valueOf(book.number1);
		else if(book.number1>9&&book.number1<100)
			book.number = "000"+String.valueOf(book.number1);
		else
			book.number = "00"+String.valueOf(book.number1);
		System.out.println("输入书名");
		book.bookk = input.next();
		System.out.println("输入作者名");
		book.author = input.next();
		System.out.println("输入出版社");
		book.press = input.next();
		System.out.println("输入时间");
		book.time = input.next();
		System.out.println("输入摘要");
		book.abstract1 = input.next();
		System.out.println("输入类别");
		book.type1 = input.next();
		book.in = 1;
	}
	
	//更新数据
	/*public void renew()
	{
		
	}*/
	
	
	
	public static void main(String[] args) {
		//文件操作
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
		//建立链表
		Book p = new Book();
		for(int i = 0;i<10;i++)
		p.add(io[i], i);
		p.ergodic();
		
		//
		//到管理员操作
		
		manager ip = new manager(p.Head(),p.Getsize());
		/*ip.remove("00077");
		System.out.println(ip.Head().t.bookk);
		books book1 = new books();
		ip.addbook(book1);
		ip.add(book1, 10);
		ip.List(ip.Head());
		ip.ergodic();*/
}
}
