package com.attack204.test;

import com.attack204.test.service.userService;
import com.attack204.test.test.MyMap;
import com.attack204.test.test.Person;
import com.attack204.test.test.PersonImpl;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.ConfigurableApplicationContext;

import java.math.BigDecimal;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;

@SpringBootApplication(scanBasePackages = "com.attack204.test")
public class TestApplication {
    public static void main(String[] args) {
        ConfigurableApplicationContext run = SpringApplication.run(TestApplication.class, args);
        PersonImpl<String> person = new PersonImpl<>();
        System.out.println(person.show("attack204"));
    }

}
