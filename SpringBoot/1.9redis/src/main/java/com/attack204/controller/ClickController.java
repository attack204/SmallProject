package com.attack204.controller;

import com.attack204.entity.Click;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import java.util.Date;

@ResponseBody
@Controller
public class ClickController {
    @Autowired
    private RedisTemplate redisTemplate;

    @PostMapping("/click")
    public Integer Click(Click click) {
        Date time = click.getTime();
        String username = click.getUsername();
        System.out.println(time);
        System.out.println(username);
        Integer clickTimes = (Integer)redisTemplate.opsForValue().get("clickTimes");
        if(clickTimes == null) {
            clickTimes = 0;
        }
        redisTemplate.opsForValue().set(++clickTimes, click);
        redisTemplate.opsForValue().set("clickTimes",  clickTimes);
        return (Integer)redisTemplate.opsForValue().get("clickTimes");
    }
    @GetMapping("query/{id}")
    public Click Query(@PathVariable int id) {
        return (Click) redisTemplate.opsForValue().get(id);
    }
}
