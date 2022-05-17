import requests
from bs4 import BeautifulSoup



urlWeibo = "https://s.weibo.com/top/summary"
def PaWeibo(urlWeibo):
  # 爬虫部分
  headers = {
      'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/80.0.3987.122 Safari/537.36',
  }
  r = requests.get(urlWeibo, headers=headers)
  r.encoding = "utf-8"
  content = r.text
  # print(content)
  return content

def PrintWebSiteWeibo(soup):
#soup为经过bs4解析之后的网页变量
#该函数向文件输出一个经过美化之后的网页源代码
  TmpTxt = soup.prettify()
  with open("data.html", "w", encoding="utf-8") as f:
    f.write(TmpTxt)

def GetHtmlWeibo(html):
  #html为未经处理的字符串文件
  #该函数的功能是对html进行处理，提取出热榜部分的内容
  soup = BeautifulSoup(html, 'html.parser')
  # PrintWebSiteWeibo(soup) #调试代码，用来输出最开始获得的网页代码
  #tmptxt = soup.find_all("td", "td-02") # 感觉这个find_all有点垃圾，返回结果和下面的select一样，都是ResultSet
  tmptxt = soup.select('a[target="_blank"]')
  return tmptxt

def CalculateDataWeibo(data):
  #data为处理后的热榜内容，为ResultsSet类型
  # 该函数为对data进行数据统计
 
  with open("dataWeibo.txt", "w", encoding="utf-8") as f:
    for item in data:
      print(item)
      f.write(str(item.string) + '\n')   

def mainWeiBo():
  html = PaWeibo(urlWeibo)
  mainhtml = GetHtmlWeibo(html)
  CalculateDataWeibo(mainhtml)
mainWeiBo()
