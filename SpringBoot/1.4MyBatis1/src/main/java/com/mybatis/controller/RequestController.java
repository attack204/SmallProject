package com.mybatis.controller;

import com.mybatis.bean.Account;
import com.mybatis.service.AccountService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class RequestController {
    @Autowired
    public AccountService accountService;

    @RequestMapping("/mybatis")
    public Account requestController(Integer id) {
        return accountService.Query(id);
    }

//    @RequestMapping("/error")不能自己定义error页面s
//    public String errorPage() {
//        return "you boom";
//    }
}
