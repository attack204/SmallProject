package com.attack204.fastjson;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.serializer.SerializerFeature;
import com.attack204.entity.user;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.List;

@SpringBootApplication
public class FastjsonApplication {

    public static void main(String[] args) {
        SpringApplication.run(FastjsonApplication.class, args);
        user test = new user();
        test.setName("attack204");
        //test.getAge(Integer.valueOf(34));
        test.setAge(34);
        test.setScore(BigDecimal.valueOf(100.0));
        String jsonString = JSON.toJSONString(test);
        System.out.println(jsonString);
        user revert = JSON.parseObject(jsonString, user.class);
        System.out.println(revert.getScore());
        //基本用法

        List<user> list = new ArrayList<>();
        list.add(test);
        list.add(test);
        String jsonStringList = JSON.toJSONString(list, SerializerFeature.DisableCircularReferenceDetect);
        //防止重复引用，若去掉，则会发生list=[{"name":"bb","code":"22"},{"$ref":"$[0]"}]这类错误
        System.out.println(jsonStringList);

        List<user> listRevert = JSON.parseArray(jsonStringList, user.class);
        System.out.println(listRevert.get(1).getScore());
        //数组用法
    }

}
