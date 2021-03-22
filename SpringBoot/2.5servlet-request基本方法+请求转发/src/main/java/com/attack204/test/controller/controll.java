package com.attack204.test.controller;

import com.attack204.test.service.impl.userServiceImpl;
import com.attack204.test.service.userService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@RestController
public class controll {
    @Autowired
    userServiceImpl userServiceImpl;

    @GetMapping("/query")
    public void query(HttpServletRequest request) {
        //获取完整的请求路径(到?前结束)
        System.out.println(request.getRequestURL());
        //获取部分请求路径(从/开始，到?前结束)
        System.out.println(request.getRequestURI());
        //获取请求的参数字符串
        System.out.println(request.getQueryString());
        //获取请求的参数GET/POST
        System.out.println(request.getMethod());
        //获取请求的协议版本
        System.out.println(request.getProtocol());
        //获取站点名(项目对外访问路径)
        System.out.println(request.getContextPath());
    }

    @GetMapping("/dispatcher")
    public void dispatcher(String username, String password, HttpServletRequest req, HttpServletResponse resp) {
        System.out.println(username);
        System.out.println(password);
        try {
            if(username.equals("attack204") && password.equals("123456")) {
                req.getRequestDispatcher("/success").forward(req, resp);
            } else {
                req.setAttribute("msg", "用户名或密码不正确");
                //req.getRequestDispatcher("/failed").forward(req, resp);//请求转发不会改变url，两次跳转的request相同，可以自己指定，但默认是相同的
                resp.sendRedirect("/failed");//重定向会改变url，两次跳转的request不同
            }
        } catch (ServletException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @GetMapping("success")
    public String success() {
        return "登陆成功";
    }
    @GetMapping("/failed")
    public String failed(HttpServletRequest req) {
        return "登陆失败" + req.getAttribute("msg");
    }
}
