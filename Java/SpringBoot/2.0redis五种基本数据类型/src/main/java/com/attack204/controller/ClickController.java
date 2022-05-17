package com.attack204.controller;

import com.attack204.entity.Click;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.redis.core.*;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Set;

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

    @RequestMapping("/String")
    public String RedisStringTest() {
        redisTemplate.opsForValue().set("attack204", "garbage");
        return (String) redisTemplate.opsForValue().get("attack204");
        //garbage
    }

    @RequestMapping("/List")
    public List<String> RedisListTest() {
        ListOperations<String, String> list = redisTemplate.opsForList();
        list.leftPush("adminList", "attack204");
        list.leftPush("adminList", "attack205");
        list.rightPush("adminList", "attack206");
        list.leftPush("userList", "attack1");
        list.rightPush("userList", "attack2");
        return list.range("adminList", 0, list.size("adminList"));
        //attack205 attack204 attack206
    }

    @RequestMapping("/Set")
    public Set<String> RedisSetTest() {
        SetOperations<String, String> set = redisTemplate.opsForSet();
        set.add("applyMember", "attack205");
        set.add("applyMember", "attack204");
        set.add("applyMember", "attack204");

        return set.members("applyMember");
        //attack204 attack205
    }

    @RequestMapping("/ZSet")
    public Set<String> RedisZSetTest() {
        ZSetOperations<String, String> zset = redisTemplate.opsForZSet();
        zset.add("applyMember2", "attack205", 2);//第三个参数是权重，注意不要重名
        zset.add("applyMember2", "attack204", 1);
        zset.add("applyMember2", "attack204", 3);//3会覆盖掉1，虽然是add操作，但是是覆盖

        return zset.range("applyMember2", 0, 1);
//        attack204 attack205
    }

    @RequestMapping("/Hash")
    public String RedisHashTest() {
        HashOperations<String, String, String> hash = redisTemplate.opsForHash();
        hash.put("good", "time1", "900");
        hash.put("good", "time2", "800");
        return hash.get("good", "time1");
    }

}
