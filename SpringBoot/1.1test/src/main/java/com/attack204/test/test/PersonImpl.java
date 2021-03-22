package com.attack204.test.test;

/**
 * Created with IntelliJ IDEA
 * <p>
 * Author attack204 attack204.com
 * Description
 * Date 2021/3/6
 * Time 10:56
 */
public class PersonImpl<T> implements PersonInt<T> {
    @Override
    public String show(T name) {
        return name + "is showing three";
    }
}
