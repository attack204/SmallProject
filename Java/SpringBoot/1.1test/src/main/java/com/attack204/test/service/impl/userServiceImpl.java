package com.attack204.test.service.impl;

import com.attack204.test.service.userService;
import org.springframework.stereotype.Service;

@Service
public class userServiceImpl implements userService {

    public String getName() {
        return "attack204";
    }
}
