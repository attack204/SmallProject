## exp

1. redis中，用不同数据结构维护的key不能相同

```java
@RequestMapping("/ZSet")
public Set<String> RedisZSetTest() {
    ZSetOperations<String, String> zset = redisTemplate.opsForZSet();
    zset.add("applyMember2", "attack205", 2);//第三个参数是权重，注意不要重名
    zset.add("applyMember2", "attack204", 1);
    zset.add("applyMember2", "attack204", 3);//3会覆盖掉1，虽然是add操作，但是是覆盖

    return zset.range("applyMember2", 0, 1);
//        attack204 attack205
}
```