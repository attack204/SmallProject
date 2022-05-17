package com.shiro.service;

import com.shiro.entity.Users;
import com.baomidou.mybatisplus.extension.service.IService;

/**
 * <p>
 * 服务类
 * </p>
 *
 * @author attack204
 * @since 2021-02-12
 */
public interface UsersService extends IService<Users> {
    Users getUsers(String username);

}
