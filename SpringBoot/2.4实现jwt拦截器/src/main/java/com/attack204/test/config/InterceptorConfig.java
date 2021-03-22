package com.attack204.test.config;

import com.attack204.test.interceptor.JWTInterceptor;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.InterceptorRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

/**
 * Created with IntelliJ IDEA
 * <p>
 * Author attack204 attack204.com
 * Description
 * Date 2021/2/19
 * Time 11:31
 */

@Configuration
public class InterceptorConfig implements WebMvcConfigurer {
    @Override
    public void addInterceptors(InterceptorRegistry registry) {
        registry.addInterceptor(new JWTInterceptor())
                .addPathPatterns("/getUsername")
                .excludePathPatterns("/login");

    }
}
