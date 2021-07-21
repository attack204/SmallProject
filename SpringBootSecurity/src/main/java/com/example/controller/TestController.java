package com.example.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

/**
 * @author attack204
 * date:  2021/7/21
 * email: 757394026@qq.com
 */

@RestController
@RequestMapping("/v1")
public class TestController {

    @GetMapping("/test")
    public String test() {
        return "HelloWrold";
    }
}
