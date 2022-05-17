package com.attack204.test.controller;

import com.attack204.test.service.impl.userServiceImpl;
import com.attack204.test.service.userService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;
import javax.xml.crypto.Data;
import java.io.IOException;
import java.util.Date;

@RestController
@MultipartConfig//文件上传需要加此注解
public class controll {
    @Autowired
    userServiceImpl userServiceImpl;

    @PostMapping("/test")
    public String test(HttpServletRequest request) {

        try {
//            request.setCharacterEncoding("UTF-8");
            String username = request.getParameter("username");
            System.out.println("姓名" + username);

            Part part = request.getPart("userfile");
            String fileName = part.getSubmittedFileName();
            if(fileName != null) {
                String realPath = request.getServletContext().getRealPath("/");
                part.write(realPath + fileName);
                return realPath + fileName;
            }
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ServletException e) {
            e.printStackTrace();
        }
        return "failed";
    }

}
