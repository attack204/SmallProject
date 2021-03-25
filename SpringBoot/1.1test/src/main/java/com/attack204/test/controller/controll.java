package com.attack204.test.controller;

import com.attack204.test.service.impl.userServiceImpl;
import com.attack204.test.service.userService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import javax.servlet.ServletRequest;
import javax.servlet.http.HttpServletRequest;

@RestController
public class controll {
    @Autowired
    userService userService;

    @GetMapping("/query")
    public String ret(ServletRequest request) {
        return "attack204";
    }

}
