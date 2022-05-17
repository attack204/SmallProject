package com.attack204.entity;

import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import java.io.Serializable;
import java.util.Date;

@Data
public class Click implements Serializable {
    @DateTimeFormat(pattern = "yyyy-MM-dd") //使用此注解，可以避免日期格式问题
    private Date time;
    private String username;
}
