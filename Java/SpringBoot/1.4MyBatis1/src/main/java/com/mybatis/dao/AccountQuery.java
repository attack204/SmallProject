package com.mybatis.dao;

import com.mybatis.bean.Account;
import org.apache.ibatis.annotations.Mapper;


@Mapper
public interface AccountQuery {
    public Account Query(Integer id);
}
