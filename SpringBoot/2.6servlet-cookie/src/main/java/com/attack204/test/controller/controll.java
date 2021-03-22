package com.attack204.test.controller;

import com.attack204.test.service.impl.userServiceImpl;
import com.attack204.test.service.userService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.xml.crypto.Data;
import java.io.IOException;
import java.util.Date;

@RestController
public class controll {
    @Autowired
    userServiceImpl userServiceImpl;

    @GetMapping("/test")
    public String test(HttpServletRequest request, HttpServletResponse response) {
        Date date = new Date();
        response.addCookie(new Cookie("username", "attack204"));
        //cookie中不能有字符串
        response.addCookie(new Cookie("loginTime", date.toString().replace(" ", "")));

        Cookie cookie = new Cookie("ExpireTime", "7");
        cookie.setMaxAge(60 * 60 * 24 * 7);//设置过期时间，单位为秒，0表示删除，-1表示浏览器关闭时失效

        return "success";
    }

    @GetMapping("getCookie")
    public String[] getCookie(HttpServletRequest request, HttpServletResponse response) {
        String[] arr = new String[20];
        Integer cnt = 0;
        for(Cookie cookie: request.getCookies()) {
            arr[++cnt] = cookie.getName() + " " + cookie.getValue();
        }
        return arr;
    }
}
