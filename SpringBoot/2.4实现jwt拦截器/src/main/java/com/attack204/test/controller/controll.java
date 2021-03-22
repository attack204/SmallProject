package com.attack204.test.controller;

import com.attack204.test.service.impl.userServiceImpl;
import com.attack204.test.service.userService;
import com.attack204.test.utils.JWTUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import javax.servlet.ServletRequest;
import javax.servlet.http.HttpServletRequest;
import java.util.HashMap;

@RestController
public class controll {
    @Autowired
    userServiceImpl userServiceImpl;

    @GetMapping("/login")
    public String login(@RequestParam("username") String username,
                        @RequestParam("password") String password) {
        HashMap<String, String> map = new HashMap<>();
        map.put("username", username);
        String token = JWTUtils.createToken(map);
        return token;
    }

    @GetMapping("/getUsername")
    public String getUsername(HttpServletRequest request) {
        return JWTUtils.getUsername(request.getHeader("token"));
    }
}
