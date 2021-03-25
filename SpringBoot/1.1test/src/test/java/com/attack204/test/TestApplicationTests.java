package com.attack204.test;

import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

@SpringBootTest
class TestApplicationTests {

    @Test
    void contextLoads() {
        List<String> list = new ArrayList<>(233);
        list.add("1");
        list.add("233");
        list.add("234");
        Iterable iter = list;

        List<String> listCpy = (List<String>) iter;
        for(String s: listCpy) {
            System.out.println(s);
        }

        Iterator<String> iterator = iter.iterator();
        while(iterator.hasNext()) {
            System.out.println(iterator.next());
            iterator.remove();
        }
    }

}
