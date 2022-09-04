package main

import (
    "fmt"
    "github.com/go-redis/redis"
)

func main() {
    fmt.Println("golang连接redis")

    client := redis.NewClient(&redis.Options{
        Addr: "127.0.0.1:6379",
    })

    pong, err := client.Ping().Result()
    fmt.Println(pong, err)

        //添加键值对
        err = client.Set("golang", "yes", 0).Err()
        if err != nil {
            fmt.Println(err)
        }
        fmt.Println("键golang设置成功")
}
