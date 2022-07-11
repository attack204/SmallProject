# Bug

1. mybatis-plus与mybatis-plus-generator版本号必须相同，因为其具有包含关系

## 简单说说我对shiro框架的理解

核心思想，shiro有三部分组成：

subject：用来直接与数据进行交互。

securityManager: 用来处理数据，网上大部分说这玩意儿是中心，但是我觉得这玩意儿其实挺鸡肋的。

realm:这是业务的核心部分， 其中含有两个方法，分别是认证方法与授权方法，这部分需要开发者自行编写。

ShiroFilterFactoryBean：框架的主要配置，设置路径权限。

所以需要由开发者编写的只有两块，一个是ShiroFilterFactoryBean，还有一个是realm

接下来说说shiro的执行逻辑

1. 在subject.login时进行doGetAuthenticationInfo，也就是判断用户名密码是否正确。

需要注意的是判断用户名密码这一步不需要我们做，是shiro框架完成的(在最后)，判断完成之后会自动更新subject

2. 在访问被拦截的页面的时候会进行认证

我们需要提供的是当前登陆用户的所有权限。

但是有一个细节需要注意：就是即使该用户已经登陆了，在访问同一个页面多次时，会进行多次认证，这是非常耗时的！






