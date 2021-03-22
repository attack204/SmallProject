package com.druid.bean;

import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

//默认的table_name就是类名，如果要重新指定的话需要使用TableName注解
@Data
@TableName(value = "t_user")
public class Account {
    private Integer id;
    private String userName;
    private String password;
}
