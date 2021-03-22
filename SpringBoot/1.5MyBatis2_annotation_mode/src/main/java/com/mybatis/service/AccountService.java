package com.mybatis.service;

import com.mybatis.bean.Account;
import com.mybatis.dao.AccountQuery;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;


@Service
public class AccountService {
    @Autowired
    public AccountQuery accountQuery;

    public Account Query(Integer id) {
        return accountQuery.Query(id);
    }

    public Account Insert(Account newAccount) {
        accountQuery.Insert(newAccount);
        return newAccount;
    }

}
