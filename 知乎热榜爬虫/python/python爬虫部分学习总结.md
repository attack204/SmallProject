## python爬虫爬取知乎页面

### 确定任务

1. 链接目标网站`https://www.zhihu.com/hot`，并获取源代码
2. 对网页源代码进行处理，提取出h2的标题部分
3. 对标题部分进一步进行处理，并输出到文件中

### part1

刚开始以为直接get之后输出text就行了，但是遇到了两个问题

1. 直接request的话会被ban掉，于是修改了一下request头，问题解决
2. 知乎热榜需要登陆之后才能访问，于是在header里面加了个cookie

```py
url = "https://www.zhihu.com/hot"
def Pa(url):
  # 爬虫部分
  cookies = 'mycookie'
  headers = {
      'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/80.0.3987.122 Safari/537.36',
      'Cookie': cookies
  }
  r = requests.get(url, headers=headers)
  r.encoding = "utf-8"
  content = r.text
  return content
```

### part2

这里用到BeautifulSoup，其实也简单，就是先审查元素找到标题所独有的class类，然后在BeautifulSoup弄出来的对象中用一下find_all就行了

```py
def GetHtml(html):
  #html为未经处理的字符串文件
  #该函数的功能是对html进行处理，提取出热榜部分的内容
  soup = BeautifulSoup(html, 'html.parser')
  # PrintWebSite(soup) #调试代码，用来输出最开始获得的网页代码
  tmptxt = soup.find_all("h2", "HotItem-title") # 感觉这个find_all有点垃圾，返回结果和下面的select一样，都是ResultSet
  # tmptxt = soup.select('h2[class="HotItem-title"]')
  return tmptxt
```

### part3

这里枚举一下获取到的所有标签，然后string获取一下内容，输出到文件中就行了

```py
def CalculateData(data):
  #data为处理后的热榜内容，为ResultsSet类型
  # 该函数为对data进行数据统计
 
  with open("data.txt", "w", encoding="utf-8") as f:
    for item in data:
      f.write(str(item.string) + '\n')   
```

### 其他学到的知识

- 获取网页cookie的方法
    - 控制台`document.cookie`
    - 控制台network-doc可以查看完整的header头

- 让浏览器停止加载的方法
    - 控制台window.stop()

### 完整代码

```python
import requests
from bs4 import BeautifulSoup
url = "https://www.zhihu.com/hot"
def Pa(url):
  # 爬虫部分
  cookies = 'mycookie'
  headers = {
      'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/80.0.3987.122 Safari/537.36',
      'Cookie': cookies
  }
  r = requests.get(url, headers=headers)
  r.encoding = "utf-8"
  content = r.text
  return content

def PrintWebSite(soup):
#soup为经过bs4解析之后的网页变量
#该函数向文件输出一个经过美化之后的网页源代码
  TmpTxt = soup.prettify()
  with open("data.html", "w", encoding="utf-8") as f:
    f.write(TmpTxt)

def GetHtml(html):
  #html为未经处理的字符串文件
  #该函数的功能是对html进行处理，提取出热榜部分的内容
  soup = BeautifulSoup(html, 'html.parser')
  # PrintWebSite(soup) #调试代码，用来输出最开始获得的网页代码
  tmptxt = soup.find_all("h2", "HotItem-title") # 感觉这个find_all有点垃圾，返回结果和下面的select一样，都是ResultSet
  # tmptxt = soup.select('h2[class="HotItem-title"]')
  return tmptxt

def CalculateData(data):
  #data为处理后的热榜内容，为ResultsSet类型
  # 该函数为对data进行数据统计
 
  with open("data.txt", "w", encoding="utf-8") as f:
    for item in data:
      f.write(str(item.string) + '\n')   

def main():
  html = Pa(url)
  mainhtml = GetHtml(html)
  CalculateData(mainhtml)
main()

```