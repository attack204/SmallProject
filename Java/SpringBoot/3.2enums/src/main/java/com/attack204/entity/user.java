package com.attack204.entity;

import lombok.Data;

import java.math.BigDecimal;

/**
 * @author attack204 (attack204.com)
 * <p>
 * date 2021/2/15
 */
@Data
public class user {
    private String name;
    private Integer age;
    private BigDecimal score;
}
