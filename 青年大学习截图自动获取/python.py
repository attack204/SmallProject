import requests
import time 
txt = open(r"data.txt", "r", encoding="UTF-8").read()

tot = 0
for x in range(0, len(txt)):
    if txt[x] == 'h' and txt[x + 1] == 't' and txt[x + 2] == 't' and txt[x + 3] == 'p':
        url = ""
        for i in range(x, x + 65):
            url += txt[i]
        r = requests.get(url)
        # print(str(tot) + ".jpg")
        tot = tot + 1
        if(txt[x - 4] == ' '):
            name = txt[x + 66] + txt[x + 67] + txt[x + 68] + txt[x + 69] + txt[x + 70] + txt[x + 71] + txt[x + 72] + txt[x + 73] + txt[x + 74] + txt[x + 75] + txt[x - 3] + txt[x - 2] + ".jpg";
        else:
            name = txt[x + 66] + txt[x + 67] + txt[x + 68] + txt[x + 69] + txt[x + 70] + txt[x + 71] + txt[x + 72] + txt[x + 73] + txt[x + 74] + txt[x + 75] + txt[x - 4] + txt[x - 3] + txt[x - 2]  + ".jpg"
        with open(name,'wb')as f:
             #wb存为二进制文件
            f.write(r.content)
            #将返回内容写入文件 r.content返回二进制形式
            f.close()
    #    time.sleep(1)
