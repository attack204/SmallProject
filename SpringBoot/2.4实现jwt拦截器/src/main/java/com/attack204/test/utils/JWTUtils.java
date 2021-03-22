package com.attack204.test.utils;

import com.auth0.jwt.JWT;
import com.auth0.jwt.JWTCreator;
import com.auth0.jwt.JWTVerifier;
import com.auth0.jwt.algorithms.Algorithm;
import com.auth0.jwt.exceptions.JWTDecodeException;
import com.auth0.jwt.interfaces.DecodedJWT;

import java.io.UnsupportedEncodingException;
import java.util.Calendar;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

/**
 * Created with IntelliJ IDEA
 * <p>
 * Author attack204 attack204.com
 * Description
 * Date 2021/2/19
 * Time 9:42
 */
public class JWTUtils {
    private static final String SECRET = "@#$%^&*(()3456789WERTYUIO";
    private static final Integer EXPIRE_TIME = 15 * 24; // 15天

    /**
     * 创建token
     * 注意传入的是一个HashMap
     * @param map
     * @return
     */
    public static String createToken(HashMap<String, String> map) {
        Calendar instance = Calendar.getInstance();//默认是当前时间
        instance.add(Calendar.HOUR, EXPIRE_TIME);//一天
        JWTCreator.Builder builder = JWT.create();
        map.forEach((k, v)-> {
            builder.withClaim(k, v);
        });
        builder.withExpiresAt(instance.getTime());
        return builder.sign(Algorithm.HMAC256(SECRET));
    }

    /**
     * 验证token是否有效
     * 这里不加try/catch是因为，在JWTInterceptor中会有一层try/catch，很明显，两层try/catch外层什么都获取不到(如果内层try/catch return了true/false的话)
     * @param token
     * @return
     */
    public static boolean verify(String token) {
        JWTVerifier jwtVerifier = JWT.require(Algorithm.HMAC256(SECRET)).build();
        DecodedJWT verify = jwtVerifier.verify(token);
        return true;
    }

    /**
     * 获得token中的信息，无需secret解密也能获得
     *
     * @return token中包含的用户名
     */
    public static String getUsername(String token) {
        try {
            DecodedJWT jwt = JWT.decode(token);
            return jwt.getClaim("username").asString();
        } catch (JWTDecodeException e) {
            return null;
        }
    }
}
