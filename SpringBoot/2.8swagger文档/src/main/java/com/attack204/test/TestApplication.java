package com.attack204.test;

import com.attack204.test.service.userService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.ConfigurableApplicationContext;
import springfox.documentation.swagger2.annotations.EnableSwagger2;

import java.math.BigDecimal;
import java.util.HashMap;

@SpringBootApplication(scanBasePackages = "com.attack204.test")
@EnableSwagger2
public class TestApplication {
    public static void main(String[] args) {
        ConfigurableApplicationContext run = SpringApplication.run(TestApplication.class, args);
    }

}
