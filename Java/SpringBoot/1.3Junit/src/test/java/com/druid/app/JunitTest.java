package com.druid.app;

import com.druid.dao.AccountQuery;
import org.junit.jupiter.api.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
@DisplayName("Junit单元测试")
public class JunitTest {
    public int x = 0;
    @Autowired
    public AccountQuery accountQuery;


    @BeforeAll()
    public static void beforeAll() {
        System.out.println("测试开始");
    }

    @AfterAll()
    public static void afterAll() {//必须是静态的
        System.out.println("测试结束");
    }

    @BeforeEach()
    public void beforeEach() {
        System.out.println("第" + (++x) + "次测试开始");
    }

    @AfterEach()
    public void afterEach() {
        System.out.println("第" + x + "次测试结束");
    }

    @Test
    @DisplayName("第一次测试")
    public void Test1() {
        System.out.println(accountQuery);
    }

    @DisplayName("第二次测试")
    @RepeatedTest(5)
    public void Test2() {
        System.out.println("第二次测试123");
    }


}
