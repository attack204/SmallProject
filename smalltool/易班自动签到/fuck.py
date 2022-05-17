import os
import sys
import smtplib
from email.mime.text import MIMEText
from email.utils import formataddr
from time import sleep, time
from selenium import webdriver
from threading import Thread, Lock
from random import randrange, shuffle
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.action_chains import ActionChains


class Info(object):
    def __init__(self, url, sel1, sel2, sel3, email, low, high):
        self.url = url
        self.sel1 = sel1
        self.sel2 = sel2
        self.sel3 = sel3
        self.email = email
        self.low = low
        self.high = high


def mail(my_user):
    try:
        msg = MIMEText(
            '易班报送成功。', 'plain', 'utf-8')
        msg["Accept-Language"] = "zh-CN"
        msg["Accept-Charset"] = "ISO-8859-1,utf-8"
        # 发件人邮箱昵称、发件人邮箱账号
        msg['From'] = formataddr(["Auto5", my_sender])
        # 收件人邮箱昵称、收件人邮箱账号
        msg['To'] = formataddr(["Auto5User", my_user])
        msg['Subject'] = "易班自动报送成功"                # 邮件的标题
        # print(msg.as_string())

        # 括号中对应的是发件人邮箱账号、收件人邮箱账号、发送邮件
        server.sendmail(my_sender, [my_user, ], msg.as_string())

    except Exception as e:
        print(e)


def select_element(driver, element_idx=1, selection_idx=0):
    driver.find_element_by_xpath(
        '//*[@id="WFForm"]/div[2]/div/div[' +
        str(element_idx)+']/div/div[1]').click()
    sleep(1)
    dragger = driver.find_element_by_xpath(
        '/html/body/div[2]/div/div[2]/div/div/div/div/div[2]/div/div[2]')
    ActionChains(driver).drag_and_drop_by_offset(
        dragger, 0, -50*selection_idx).perform()
    sleep(1)
    driver.find_element_by_xpath(
        '/html/body/div[2]/div/div[2]/div/div/div/div/div[1]/div[3]').click()
    sleep(1)


def random_temperature(low=3, high=8):
    return "36." + str(randrange(low, high, 1))


def operate(infos=[]):
    user_count = len(infos)
    if user_count == 0:
        return
    # 随机顺序
    shuffle(infos)
    # 随机延时上下限计算
    # 计算公式 最长时间=(3600-100*用户数)/(用户数)
    # 计算公式 最短时间=最长时间/2
    most = (3600-100*user_count)/user_count
    least = most/2
    for idx in range(len(infos)):
        # mail(infos[idx].email)
        # 随机延时
        sleep_time = randrange(least, most)
        print(sleep_time)
        sleep(sleep_time)
        # 进行操作
        options = webdriver.ChromeOptions()
        options.add_argument(
            'user-agent="Mozilla/5.0 (Linux Android 8.0.0 MIX 2 Build/OPR1.170623.027 wv) AppleWebKit/537.36 (KHTML, like Gecko) Version/4.0 Chrome/71.0.3578.99 Mobile Safari/537.36 yiban_android"')
        driver = webdriver.Chrome(chrome_options=options)
        driver.maximize_window()
        driver.get(infos[idx].url)
        sleep(1)
        # 点击任务
        driver.find_element_by_xpath(
            '//*[@id="root"]/div[3]/div[1]/div[3]').click()
        sleep(1)
        # 点击第一个信息采集栏目
        driver.find_element_by_xpath(
            '//*[@id = "root"]/div/div[1]/div[1]/div/div/div[1]/div').click()
        sleep(1)
        # 点击反馈
        driver.find_element_by_xpath(
            '//*[@id = "root"]/div/footer/a').click()
        sleep(1)
        # 以下填报各项信息
        # 打开第一个信息栏目
        try:
            select_element(driver, 1, infos[idx].sel1)
        except Exception as e:
            print("Fail")
            print(e)
        else:
            select_element(driver, 2, infos[idx].sel2)
            select_element(driver, 3, infos[idx].sel3)
            driver.find_element_by_xpath(
                '//*[@id="WFForm"]/div[2]/div/div[4]/div/div[2]/input').send_keys(random_temperature(infos[idx].low, infos[idx].high))
            sleep(1)
            # 提交
            driver.find_element_by_xpath(
                '//*[@id = "root"]/div/a').click()
            # 发送提示邮件
            mail(infos[idx].email)
        finally:
            # print(infos[idx].email)
            # mail(infos[idx].email)
            # 关闭浏览器
            sleep(1)
            driver.close()
    driver.quit()


my_sender = ''    # 发件人邮箱账号
my_pass = ''       # 发件人邮箱密码
# 登录邮箱
server = smtplib.SMTP_SSL("smtp.qq.com", 465)  # 用发件人邮箱的SMTP服务器地址和端口创建一个新的连接实例
server.login(my_sender, my_pass)  # 登录
# 获取绝对路径并打开数据文件
path = os.path.abspath(os.path.dirname(sys.argv[0]))
fp = open(path + "/test.dat", "r")
# 线程数设定
# 当前用户数较少设定为1
# TODO 自适应线程数功能
thread_num = 1
# thread_num = int(input("thread_num = "))
# 根据线程数设定建立对应数量的list存放task
thread_tasks = []
for _ in range(thread_num):
    thread_tasks.append([])
# 从文件读取数据并加入list
now_thread = -1
while True:
    now_thread += 1
    # 读取用户易班链接
    url = fp.readline()
    # 检测文件是否已经结束
    if url == "":
        break
    # 读取用户三个选项的选择
    sel1 = int(fp.readline())
    sel2 = int(fp.readline())
    sel3 = int(fp.readline())
    # 读取用户邮箱地址并去掉末尾的\n\r
    # 如果不去掉换行符会导致邮件内容乱码
    email = fp.readline()
    email = email.replace('\n', '').replace('\r', '')
    # 读入用户设定的最低和最高体温
    low = int(fp.readline())
    high = int(fp.readline())
    # 将当前用户分配给线程
    thread_tasks[now_thread % thread_num].append(
        Info(url, sel1, sel2, sel3, email, low, high))
# 读取完毕，关闭文件
fp.close()
# 开始多线程操作
threads = []
# start = time()
for now_tasks in thread_tasks:
    t = Thread(target=operate, args=(now_tasks,))
    threads.append(t)
    t.start()
    sleep(0.5)
# 等待所有线程执行完毕
for t in threads:
    t.join()
# end = time()
# print('总共耗费了%.2f秒.' % (end - start))

# 向自己发送提示邮件，表明程序正常运行结束，已经完成所有用户的签到。
mail('')
# 关闭邮箱连接
server.quit()

