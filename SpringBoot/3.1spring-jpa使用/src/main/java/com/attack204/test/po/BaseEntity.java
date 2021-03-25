package com.attack204.test.po;

import lombok.Data;

import javax.persistence.MappedSuperclass;

/**
 * @author attack204
 * <p>
 * date:  2021/3/24
 * <p>
 * email: 757394026@qq.com
 */
@Data

public class BaseEntity {

    private String creator;

    private Long createTime;

    private String updater;

    private Long updateTime;
}
