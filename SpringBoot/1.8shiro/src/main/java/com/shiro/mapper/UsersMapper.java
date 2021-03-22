package com.shiro.mapper;

import com.shiro.entity.Users;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;

/**
 * <p>
 * Mapper 接口
 * </p>
 *
 * @author attack204
 * @since 2021-02-12
 */
@Mapper
public interface UsersMapper extends BaseMapper<Users> {
    @Select("SELECT * FROM users WHERE username=#{username}")
    public Users getByName(String username);
}
