package com.attack204.test.test;

import lombok.Data;

/**
 * Created with IntelliJ IDEA
 * <p>
 * Author attack204 attack204.com
 * Description
 * Date 2021/3/6
 * Time 10:03
 */
@Data
public class Person<T> {
    private T name;
    private T address;
    //以下两种方法都可以
    public String show(T inputName) {
        return inputName + "is showing";
    }
    public <E> String show2(E input) {
        return input + "is showing two";
    }
}
