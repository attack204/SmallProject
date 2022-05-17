package com.logger_usage.logger;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;


@SpringBootApplication
public class LoggerApplication {

    private static final Logger logger = LoggerFactory.getLogger(LoggerApplication.class);

    public static void main(String[] args) {
        SpringApplication.run(LoggerApplication.class, args);
        String name = "第一天打卡";
        logger.error("This is a test, name: {}", name);
//        System.out.println("gg");
    }

}
