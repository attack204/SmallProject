package com.attack204.test.test;

import lombok.Data;

/**
 * Created with IntelliJ IDEA
 * <p>
 * Author attack204 attack204.com
 * Description
 * Date 2021/3/6
 * Time 10:14
 */
@Data
public class MyMap<K, V> {
    private K key;
    private V value;
    public void setKeyAndValue(K key, V value) {
        this.key = key;
        this.value = value;
    }
}
