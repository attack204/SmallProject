## README

## 使用方法

[官方文档](https://mp.baomidou.com/guide/generator.html)

1. 引入pom依赖

```xml
<!--mp代码生成器-->
<!--代码生成器-->
<dependency>
    <groupId>com.baomidou</groupId>
    <artifactId>mybatis-plus-generator</artifactId>
    <version>3.2.0</version>
</dependency>
<!--用于生成文件的引擎-->
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-freemarker</artifactId>
</dependency>
```


2. 将CodeGenerator.java放到自己的工作目录中

需要设置的地方有很多，你可以使用Ctrl+F搜索"!!"，所有带有"!!"的地方都是可能有需要设置的地方

3. 运行CodeGenerator.java中的main方法，即可自动生成类

**默认生成类的名称是数据表名+相应字段**，比如表名为user，则会生成


![](http://cdn.attack204.com/20210216194509.png)

