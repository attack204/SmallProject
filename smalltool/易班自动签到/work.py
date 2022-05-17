import os
import sys
import smtplib
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.action_chains import ActionChains
from time import sleep

options = webdriver.ChromeOptions()
options.add_argument(
    'user-agent="Mozilla/5.0 (Linux Android 8.0.0 MIX 2 Build/OPR1.170623.027 wv) AppleWebKit/537.36 (KHTML, like Gecko) Version/4.0 Chrome/71.0.3578.99 Mobile Safari/537.36 yiban_android"'
)
options.add_argument(
  'PHPSESSID="81cba557b2396279194522ba3b924051"'
)
options.add_argument(
  'csrf_token="f35477d956652df21ef4a0a04da145d8"'
)

driver = webdriver.Chrome(executable_path="D:/pythonchromemirror/chromedriver.exe", chrome_options=options)


# driver.get("https://app.uyiban.com/nightattendance/student/#/home?AppName=%E6%99%9A%E7%82%B9%E7%AD%BE%E5%88%B0")
driver.get("https://www.yiban.cn/login?go=http://f.yiban.cn/iapp7463")

# sleep(10000)
# driver.get("")

js='document.getElementById("account-txt").value = "15006856731"'
driver.execute_script(js)
js='document.getElementById("password-txt").value = "lgj325188."'
driver.execute_script(js)
js='document.getElementById("login-btn").click()'
driver.execute_script(js)
# driver.quit()

# driver.get("https://c.uyiban.com/#/")

sleep(10)


js='document.getElementsByClassName("interior___3mayh")[2].click()'
driver.execute_script(js)

sleep(10)
js='document.getElementsByClassName("btn___1FJPN")[0].click()'
driver.execute_script(js)


function getPosition () {
  return new Promise((resolve, reject) => {
    if (navigator.geolocation) {
      navigator.geolocation.getCurrentPosition(function (position) {
        let latitude = position.coords.latitude
        let longitude = position.coords.longitude
        let data = {
          latitude: latitude,
          longitude: longitude
        }
        resolve(data)
      }, function () {
        reject(arguments)
      })
    } else {
      reject('你的浏览器不支持当前地理位置信息获取')
    }
  })
}
      // 获取当前经纬度坐标
      getPosition().then(result => {
        // 返回结果示例：
        // {latitude: 30.318030999999998, longitude: 120.05561639999999}
        // 一般小数点后只取六位，所以用以下代码搞定
        let queryData = {
          longtitude: String(result.longitude).match(/\d+\.\d{0,6}/)[0],
          latitude: String(result.latitude).match(/\d+\.\d{0,6}/)[0],
          channelType: '00'
        }
        console.log(queryData)
        // 以下放置获取坐标后你要执行的代码:
        // ...
      }).catch(err => {
        console.log(err)
      })