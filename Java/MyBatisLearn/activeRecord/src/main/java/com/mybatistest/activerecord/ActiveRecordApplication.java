package com.mybatistest.activerecord;

import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
@MapperScan(value = "com.mybatistest")
public class ActiveRecordApplication {

    public static void main(String[] args) {
        SpringApplication.run(ActiveRecordApplication.class, args);
        System.out.println("HelloWorld");
    }

}
