package com.attack204.fastjson;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.serializer.SerializerFeature;
import com.attack204.entity.Subject;
import com.attack204.entity.user;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

@SpringBootApplication
public class FastjsonApplication {

    public static void main(String[] args) {
        SpringApplication.run(FastjsonApplication.class, args);
        System.out.println(Arrays.stream(Subject.values()).toArray()[2].);
    }

}
