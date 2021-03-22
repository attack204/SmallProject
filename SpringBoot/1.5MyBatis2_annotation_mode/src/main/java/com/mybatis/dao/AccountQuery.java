package com.mybatis.dao;

import com.mybatis.bean.Account;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Options;


@Mapper
public interface AccountQuery {
    public Account Query(Integer id);

    @Insert("INSERT INTO t_user(`id`, `user_name`, `password`) values(#{id},#{userName},#{password})")
    @Options(useGeneratedKeys = true, keyProperty = "id")
    public void Insert(Account newAccount);
}
