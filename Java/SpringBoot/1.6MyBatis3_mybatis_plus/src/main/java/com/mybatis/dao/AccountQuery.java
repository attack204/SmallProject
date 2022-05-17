package com.mybatis.dao;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.mybatis.bean.Account;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Options;


@Mapper
public interface AccountQuery extends BaseMapper<Account> {

}
