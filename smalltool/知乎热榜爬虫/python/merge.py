import requests
from bs4 import BeautifulSoup
import time 
import random
import re

url = "https://www.zhihu.com/hot"
def Pa(url):
  # 爬虫部分
  cookies = '_zap=4a6bd80f-0fd8-4ebb-b99a-c14ecc4df941; d_c0="AODepSyCaBKPTpN6weCDI9cn2vuWde27FEQ=|1609031091"; z_c0="2|1:0|10:1609031100|4:z_c0|92:Mi4xMFVucEJnQUFBQUFBNE42bExJSm9FaVlBQUFCZ0FsVk51eXZWWUFBTG5wTk9WdmY0X0tTRzE2QllqQ05aTHpsSVJn|717a1fae2322ea2b13a47e4a13db7cd8376c7fb37e765b00e8aca7b9e7c10877"; capsion_ticket="2|1:0|10:1609031100|14:capsion_ticket|44:NTcyMWY0MzZjYWQ3NDM0YzhlZWY1OTM1Njg1OTg0YTM=|01ebdfe3041a62631e4b0befa2f6000660817b53277a0d935c62aa1989fe1e7c"; q_c1=c14e00733b9d4f839b439d5ab5babf6e|1609037793000|1609037793000; _xsrf=d4d0ff2c-cf1f-4f87-a94f-333586341ebb; Hm_lvt_98beee57fd2ef70ccdd5ca52b9740c49=1609036060,1609037769,1609052238,1609052241; tshl=; tst=h; Hm_lpvt_98beee57fd2ef70ccdd5ca52b9740c49=1609053074; SESSIONID=AbUqdDD2YrLFqXJM9H3NSz2boUnqE2iPpCLJmqItPjN; JOID=VF0TAEODiiQDYz4AIoYn_stduWUwwet0eQl5RxXU-2tAGWhJbBK_wlluPgYssl-dDlRZgdg5HfU4wnSPF5NJ9ss=; osd=UFARBEKHhyYHYjoNIIIm-sZfvWQ0zOlweA10RRHV_2ZCHWlNYRC7w11jPAIttlKfClVdjNo9HPE1wHCOE55L8so=; KLBRSID=4843ceb2c0de43091e0ff7c22eadca8c|1609053432|1609052235'
  headers = {
      'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/80.0.3987.122 Safari/537.36',
      'Cookie': cookies
  }
  r = requests.get(url, headers=headers)
  r.encoding = "utf-8"
  content = r.text
  # print(content)
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
    # print(len(data))
    for item in data:
      f.write(str(item.string) + '\n')   

def main():
  html = Pa(url)
  mainhtml = GetHtml(html)
  CalculateData(mainhtml)
main()


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
  # print(len(Tmptxt))
  with open("data.html", "w", encoding="utf-8") as f:
    # print(Tmptxt)
    f.write(TmpTxt)

def GetHtmlWeibo(html):
  #html为未经处理的字符串文件
  #该函数的功能是对html进行处理，提取出热榜部分的内容
  soup = BeautifulSoup(html, 'html.parser')
  #print(soup)
  # PrintWebSiteWeibo(soup) #调试代码，用来输出最开始获得的网页代码
  #tmptxt = soup.find_all("td", "td-02") # 感觉这个find_all有点垃圾，返回结果和下面的select一样，都是ResultSet
  tmptxt = soup.select('a[target="_blank"]')
  # print(tmptxt)
  return tmptxt

def CalculateDataWeibo(data):
  #data为处理后的热榜内容，为ResultsSet类型
  # 该函数为对data进行数据统计
 
  with open("dataWeibo.txt", "w", encoding="utf-8") as f:
    for item in data:
     # print(item)
      f.write(str(item.string) + '\n')   

def mainWeiBo():
  html = PaWeibo(urlWeibo)
  mainhtml = GetHtmlWeibo(html)
  CalculateDataWeibo(mainhtml)
mainWeiBo()
