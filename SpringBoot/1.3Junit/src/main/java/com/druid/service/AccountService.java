package com.druid.service;

import com.druid.bean.Account;
import com.druid.dao.AccountQuery;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;


@Service
public class AccountService {
    @Autowired
    public AccountQuery accountQuery;

    public Account Query(Integer id) {
        return accountQuery.selectById(id);
    }

    public Account Insert(Account newAccount) {
        accountQuery.insert(newAccount);
        return newAccount;
    }

}
