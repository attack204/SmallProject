package com.howie.shirojwt;

import com.auth0.jwt.JWT;
import com.auth0.jwt.JWTVerifier;
import com.auth0.jwt.algorithms.Algorithm;
import com.auth0.jwt.interfaces.DecodedJWT;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

import java.io.UnsupportedEncodingException;
import java.util.Calendar;
import java.util.Date;
import java.util.HashMap;

//@RunWith(SpringRunner.class)
@SpringBootTest
public class ShiroJwtApplicationTests {
	/**
	 eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJsb2dpblRpbWUiOiJUaHUgRmViIDE4IDIyOjI4OjM2IENTVCAyMDIxIiwiZXhwIjoxNjEzNzQ0OTE2LCJ1c2VybmFtZSI6ImF0dGFjazIwNCJ9.8n7Fr5OxHkGg5m7qL4UKEMs1HvjJxph-z9uR2C1HWIs
	 */
	@Test
	public void contextLoads() {
		HashMap<String, Object> map = new HashMap<>();
//		map.put("alg", "HS256");
//		map.put("typ", "JWT");
		Date date = new Date();
		Calendar instance = Calendar.getInstance();//默认是当前时间
		instance.add(Calendar.SECOND, 60 * 60 * 24);//一天
		String token = new String();
		try {

			token = JWT.create().withHeader(map)
					.withClaim("username", "attack204")
					.withClaim("loginTime", date.toString())
					.withExpiresAt(instance.getTime())
					.sign(Algorithm.HMAC256("!WERTYUIO"));
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
		}
		System.out.println(token);
	}
	@Test
	public void Verify() {
		try {
			JWTVerifier jwtVerifier = JWT.require(Algorithm.HMAC256("!WERTYUIO")).build();
			DecodedJWT verify = jwtVerifier.verify("eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJsb2dpblRpbWUiOiJUaHUgRmViIDE4IDIyOjI4OjM2IENTVCAyMDIxIiwiZXhwIjoxNjEzNzQ0OTE2LCJ1c2VybmFtZSI6ImF0dGFjazIwNCJ9.8n7Fr5OxHkGg5m7qL4UKEMs1HvjJxph-z9uR2C1HWIs");
			System.out.println(verify.getClaims().get("username").asString());
			System.out.println(verify.getClaims().get("loginTime").asString());
			System.out.println(verify.getClaim("username").asString());//必须是asString
			System.out.println(verify.getClaim("loginTime").toString());
			System.out.println("过期时间" + verify.getExpiresAt());
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
		}
	}
}
