package com.mybatistest.activerecord;

import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;
import com.mybatistest.po.User;

@SpringBootTest
class ActiveRecordApplicationTests {

    @Test
    void contextLoads() {
    }
    @Test
    public void testInsert() {
        User user = new User();
        user.setUserName("attack204");
        user.setPassword("1234");
        user.setSex(1L);
        user.setId(233L);
        user.insert();
    }
    @Test
    public void testSelect() {
        User user = new User();
        user.setId(1L);
        User res = user.selectById();
        System.out.println(res);
    }
}
