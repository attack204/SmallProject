package com.attack204.test.po;

import lombok.Data;
import lombok.EqualsAndHashCode;
import org.hibernate.annotations.DynamicInsert;
import org.hibernate.annotations.DynamicUpdate;

import javax.persistence.*;

/**
 * @author attack204
 * <p>
 * date:  2021/3/24
 * <p>
 * email: 757394026@qq.com
 */
@EqualsAndHashCode(callSuper = true)
@Entity
@Data
@DynamicUpdate
@DynamicInsert
@Table(name = "tb_sys_user")
public class SysUserPo extends BaseEntity {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private Long corp;

    private String username;

    private String password;

    private String phone;

    private Integer status;
}
