## exp

1. Date数据在前后端交互的时候不好处理

可以指定数据格式，即在后端的实体类上加入@DateTimeFormat(pattern = "yyyy-MM-dd")注解

```java
@Data
public class Click implements Serializable {
    @DateTimeFormat(pattern = "yyyy-MM-dd") //使用此注解，可以避免日期格式问题
    private Date time;
    private String username;
}
```

2. redis可以存任意类型的数据，直接set即可

3. 错误的返回值

405: 提交方法错误
415: 数据类型不一致

4. Integer类型与int的比较

Integer类型相比于int携带了更多的信息

比如我们可以用Interger类型来判断null，而int不可

即
```java
Integer a = 1;
boolean flag = (a == null);//合法

int b = 1;
boolean flag2 = (b == null);//不合法
```
