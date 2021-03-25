package com.attack204.test;

import com.attack204.test.dao.SysUserDao;
import com.attack204.test.po.SysUserPo;
import org.junit.jupiter.api.Test;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
class TestApplicationTests {

    @Autowired
    SysUserDao sysUserDao;

    @Test
    void contextLoads() {
        SysUserPo target = sysUserDao.findById(17L).get();
        target.setUsername("fuck5");
        sysUserDao.save(target);
    }

}
