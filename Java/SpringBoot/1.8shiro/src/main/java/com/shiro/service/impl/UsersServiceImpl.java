package com.shiro.service.impl;

import com.shiro.entity.Users;
import com.shiro.mapper.UsersMapper;
import com.shiro.service.UsersService;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.stereotype.Service;

/**
 * <p>
 * 服务实现类
 * </p>
 *
 * @author attack204
 * @since 2021-02-12
 */
@Service
public class UsersServiceImpl extends ServiceImpl<UsersMapper, Users> implements UsersService {
    @Autowired
    UsersMapper usersMapper;

    @Override
    public Users getUsers(String username) {
        return usersMapper.getByName(username);
    }


}
