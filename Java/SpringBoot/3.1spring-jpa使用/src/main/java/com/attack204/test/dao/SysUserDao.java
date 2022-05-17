package com.attack204.test.dao;

import com.attack204.test.po.SysUserPo;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.data.repository.PagingAndSortingRepository;
import org.springframework.stereotype.Repository;

import java.util.List;

/**
 * @author attack204
 * <p>
 * date:  2021/3/24
 * <p>
 * email: 757394026@qq.com
 */
@Repository
public interface SysUserDao extends PagingAndSortingRepository<SysUserPo, Long> {
    List<SysUserPo> findAllByCorp(Long corp);
    SysUserPo findByCorp(Long corp);
    SysUserPo findByCorpAndUsername(Long corp, String username);
//    Page<SysUserPo> findByPasswordContainingOrUsernameContaining(String password, String username, PageRequest pageRequest);
    Page<SysUserPo> findSysUsersByPasswordContainingOrUsernameContaining(String password, String username, Pageable pageable);
    //注意这里一定要写Pageable！！不要写PageRequest
//    Page<SysUserPo> findSysUserPosByStatus(Integer status, Pageable pageable);
//    Page<SysUserPo> findSysUserPoByStatus(Integer status, Pageable pageable);
    Page<SysUserPo> findByStatus(Integer status, Pageable pageable);
    //这种三种写法没啥区别
}
