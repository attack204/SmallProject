package com.attack204.test.dao;

import com.attack204.test.po.SysUserPo;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.domain.Sort;
import org.springframework.data.repository.PagingAndSortingRepository;
import org.springframework.stereotype.Repository;

import java.util.Optional;

/**
 * @author attack204
 * <p>
 * date:  2021/3/24
 * <p>
 * email: 757394026@qq.com
 */
@Repository
public interface SysUserDao extends PagingAndSortingRepository<SysUserPo, Long> {
}
