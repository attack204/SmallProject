package com.mybatistest.po;

import com.baomidou.mybatisplus.annotation.TableName;
import com.baomidou.mybatisplus.extension.activerecord.Model;
import lombok.Data;
import lombok.EqualsAndHashCode;
import org.apache.ibatis.annotations.Mapper;

import java.io.Serializable;

/**
 * @author attack204
 * date:  2021/7/14
 * email: 757394026@qq.com
 */
@Data
@TableName("t_user")
@EqualsAndHashCode(callSuper = true)
@Mapper
public class User extends Model<User> implements Serializable {
    private Long id;
    private String userName;
    private String password;
    private Long sex;
    @Override
    protected Serializable pkVal() {
        return id;
    }

}
