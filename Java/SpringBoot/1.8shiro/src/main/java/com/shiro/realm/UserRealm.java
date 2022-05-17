package com.shiro.realm;


import com.shiro.entity.Users;
import com.shiro.service.UsersService;
import org.apache.shiro.SecurityUtils;
import org.apache.shiro.authc.*;
import org.apache.shiro.authz.AuthorizationInfo;
import org.apache.shiro.authz.SimpleAuthorizationInfo;
import org.apache.shiro.realm.AuthorizingRealm;
import org.apache.shiro.session.Session;
import org.apache.shiro.subject.PrincipalCollection;
import org.apache.shiro.subject.Subject;
import org.springframework.beans.factory.annotation.Autowired;


public class UserRealm extends AuthorizingRealm {

    @Autowired
    private UsersService usersService;

    /**
     * 进行授权，授权的意思就是给当前正在访问的用户一些权限
     *
     * @param principalCollection
     * @return
     */
    @Override
    protected AuthorizationInfo doGetAuthorizationInfo(PrincipalCollection principalCollection) {
        System.out.println("执行了授权 => doGetAuthorizationInfo");

        SimpleAuthorizationInfo info = new SimpleAuthorizationInfo();

        // 拿到当前登录的对象；
        Subject subject = SecurityUtils.getSubject();
        Users currentUser = (Users) subject.getPrincipal();// 拿到user对象

        // 从数据库中取出权限信息。
        info.addStringPermission(currentUser.getPerms());
        System.out.println(currentUser.getPerms());
        return info;
    }

    /**
     * 进行身份认证
     * 这一步只需要获取到数据库中的用户名密码即可，具体比较细节不需要我们操作
     *
     * @param authenticationToken
     * @return
     * @throws AuthenticationException
     */
    @Override
    protected AuthenticationInfo doGetAuthenticationInfo(AuthenticationToken authenticationToken) throws AuthenticationException {
        UsernamePasswordToken userToken = (UsernamePasswordToken) (authenticationToken);
        String username = userToken.getUsername();
        Users user = usersService.getUsers(username);
        if (user == null) {
            return null;
        }
        // 表示登录成功过之后将用户的信息放入到session里面
//        Subject subject = SecurityUtils.getSubject();
//        Session session = subject.getSession();
//        session.setAttribute("loginUser",user);

        System.out.println("执行了认证=> doGetAuthenticationInfo");
        System.out.println(getName());
        return new SimpleAuthenticationInfo(user, user.getPassword(), getName());
    }
}
