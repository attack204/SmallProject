package com.attack204.test;

import com.attack204.test.dao.SysUserDao;
import com.attack204.test.po.SysUserPo;
import org.junit.jupiter.api.Test;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Sort;

import java.awt.print.Pageable;
import java.sql.SQLOutput;
import java.util.List;

@SpringBootTest
class TestApplicationTests {

    @Autowired
    SysUserDao sysUserDao;

    @Test
    void PageTest() {
        //下面的代码可以执行对SysUserPo对象对应表的分页查询，并将结果按Sort指定的顺序返回
        //不过比较遗憾的是,jpa内部指支持对所有数据的分页
        int PageNumber = 0;
        int PageSize = 3;
        Sort sort = Sort.by(Sort.Order.asc("id"));
        PageRequest pageRequest = PageRequest.of(PageNumber, PageSize, sort);
        Page<SysUserPo> result = sysUserDao.findAll(pageRequest);
        System.out.println("数据总条数" + result.getTotalElements());
        System.out.println("总页数" + result.getTotalPages());
        List<SysUserPo> list = result.getContent();
        for(SysUserPo sysUserPo: list) {
            System.out.println(sysUserPo);
        }
    }
    @Test
    void SortTest() {
        Sort sort = Sort.by(Sort.Order.asc("corp"));
        List<SysUserPo> list = (List<SysUserPo>) sysUserDao.findAll(sort);
        for(SysUserPo sysUserPo: list) {
            System.out.println(sysUserPo);
        }
    }
    @Test
    void PageDIYTest() {
        int PageNumber = 0;
        int PageSize = 3;
//        Sort sort = Sort.by(Sort.Order.asc("id"));
        PageRequest pageRequest = PageRequest.of(PageNumber, PageSize);
        Page<SysUserPo> result = sysUserDao.findSysUsersByPasswordContainingOrUsernameContaining("at", "at",   pageRequest);
//        System.out.println("数据总条数" + result.getTotalElements());
//        System.out.println("总页数" + result.getTotalPages());
//        List<SysUserPo> list = result.getContent();
//        for(SysUserPo sysUserPo: list) {
//            System.out.println(sysUserPo);
//        }
    }
}
