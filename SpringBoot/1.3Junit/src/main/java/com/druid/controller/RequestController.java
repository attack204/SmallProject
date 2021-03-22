package com.druid.controller;

import com.druid.bean.Account;
import com.druid.service.AccountService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class RequestController {
    @Autowired
    public AccountService accountService;

    @RequestMapping("/mybatis")
    public Account requestController(Integer id) {
        return accountService.Query(id);
    }


    @ResponseBody
    @PostMapping("/save")
    public Account postController(Account newAccount) {
        accountService.Insert(newAccount);
        return newAccount;
    }
//    @RequestMapping("/error")不能自己定义error页面s
//    public String errorPage() {
//        return "you boom";
//    }
}
