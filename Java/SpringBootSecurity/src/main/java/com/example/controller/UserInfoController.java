package com.example.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.Collection;

/**
 * @author attack204
 * date:  2021/7/22
 * email: 757394026@qq.com
 */
@RestController
public class UserInfoController {

    @Autowired
    UserDetailsService userDetailsService;

    @GetMapping("/userinfo")
    public Object UserInfo() {

        Authentication authentication = SecurityContextHolder.getContext().getAuthentication();
        return authentication.getPrincipal();
    }

    @GetMapping("/userinfo2")
    public Object UserInfo(Authentication authentication) {
        return authentication.getPrincipal();
    }


    @GetMapping("/userinfo3")
    public UserDetails UserInfo3() {
        //会返回加密后的密码
        return userDetailsService.loadUserByUsername("attack204");
    }
}
