# 观海听涛排班系统API文档

## 上传个人信息

### 简要描述：

用于上传个人时间安排，上传没空的时间段

### 请求URL：

```
https://www.fizzmy.club/paiban/getform
```

### 请求方式

POST

### 请求示例

```
{
    "data": 
    {
            "week":"4",
            "name":"刘新一",
            "id":"2191210207",
            "busy":
            [
                {
                    "busytime":"2",
                    "busyday":"3"
                },
                {
                    "busytime":"3",
                    "busyday":"6"
                }
            ]
    }
}
```

这里表示在第四周里，该学生在星期三第二大节和星期六第三大节是没空的

### 参数说明：

| 参数名   | 必选 | 类型     | 说明                                                |
| -------- | ---- | -------- | --------------------------------------------------- |
| name     | 是   | string   | 名字                                                |
| id       | 是   | string   | 学号                                                |
| week     | 是   | int      | 周次                                                |
| busyday  | 是   | int(1-7) | 忙碌天数(1-7分别对应星期一到星期天)                 |
| busytime | 是   | int(1-4) | 忙碌时间(1-4分别对应第一大节到第四大节课对应的时间) |

### 返回参数说明：

1：成功

## 查询个人信息

### 简要描述

查询已经填写人员的信息

### 请求URL：

```
https://www.fizzmy.club/paiban/search
```

### 请求方式

POST

### 请求示例

```
{
    "data": 
    {
            "week":"4",
            "name":"刘新一",
            "id":"2191210207"
    }
}
```

参数说明同getform

### 返回示例

```
{
    "error_code": 1,
    "data":
    [
        {
            "busyday": 3,
            "busytime": 2
        },
        {
            "busyday": 6,
            "busytime": 3
        }
    ]
}
```

error_code为1表示成功

其他参数同getform

## 进行排班

### 简要描述

对所有已经填写信息的学生进行排班，每大节安排两人

### 请求URL：

```
https://www.fizzmy.club/paiban/search
```

### 请求方式

POST

### 请求示例

```
{
    "data": 
    {
            "week":"4",
            "password":"777"
    }
}
```

| 参数名   | 必选 | 类型   | 说明                      |
| -------- | ---- | ------ | ------------------------- |
| week     | 是   | int    | 周次                      |
| password | 是   | string | 密码，测试时密码默认为777 |

### 返回示例

```
{
    "error_code": 1,
    "data": [
        {
            "week": 4,
            "id": "2191210207",
            "name": "刘新一",
            "time": 4,
            "day": 5
        }
    ]
}
```

error_code为1表示成功

这里表示排班信息，可以有多个

其他参数同getform