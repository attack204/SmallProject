package com.shiro.controller;


import org.apache.shiro.SecurityUtils;
import org.apache.shiro.authc.IncorrectCredentialsException;
import org.apache.shiro.authc.UnknownAccountException;
import org.apache.shiro.authc.UsernamePasswordToken;
import org.apache.shiro.subject.Subject;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;

import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RestController;


/**
 * <p>
 * 前端控制器
 * </p>
 *
 * @author attack204
 * @since 2021-02-12
 */
@RestController
public class UsersController {
    @GetMapping("/login")
    public String Login(String username, String password) {
        UsernamePasswordToken token = new UsernamePasswordToken(username, password);
        Subject subject = SecurityUtils.getSubject();
        try {
            subject.login(token);
        } catch (UnknownAccountException e) {
            return "Username error" + e.getMessage();
        } catch (IncorrectCredentialsException e) {
            return "password error" + e.getMessage();
        }
        return "success";
    }

    @GetMapping("/user/add")
    public String useradd() {
        Subject subject = SecurityUtils.getSubject();
        return "你的信息" + subject.getPrincipals() + "<br>" + subject.getSession();
    }

    @GetMapping("/tologin")
    public String tologin() {
        return "非常抱歉，您还没有登陆";
    }

    @GetMapping("/logout")
    public String logout() {
        Subject subject = SecurityUtils.getSubject();
        subject.logout();
        return "登出成功";
    }
}
