# 终于又到了设计算法的步骤
# so how to do it
#
#
#
#
#
#
#
#
#

from PIL import Image
from PIL import ImageFont
from PIL import ImageDraw
import random

def check(x, y, xx, yy):
    flag = 0
    for i in range(x, xx + 1):
        for j in range(y, yy + 1):
            if(mp[i][j] == 1):
                flag = 1
    if(flag == 1):
        return 0
    else:
        return 1


def Paint(x, y, xx, yy):
    for i in range(x, xx + 1):
        for j in range(y, yy + 1):
            mp[i][j] = 1


def GetPosition(size, lens):
    flag = 0
    x = 0
    y = 0
    for i in range(150, 250):
        if(flag == 1):
            break
        for j in range(150, 250):
            if(check(i, j, i + size, j + lens * size) == 1): 
                flag = 1
                x = i
                y = j
                Paint(i, j, i + size, j + lens * size)
                break
    if(flag == 1):
        return [x, y]
    for i in range(0, 400):
        if(flag == 1):
            break
        for j in range(0, 400):
            if(check(i, j, i + size, j + lens * size) == 1): 
                flag = 1
                x = i
                y = j
                Paint(i, j, i + size, j + lens * size)
                break
    if(flag == 1):
        return [x, y]
    else:
        return [0, 0]    

def rand(x):
    v = random.random()
    v = v * 100000
    return v % x + 1


txt = open(r"data.txt", "r").read()
data = {}
str = ""

for i in txt:
    if(i != " "):
        str = str + i
    else:
        if(str in data):
            data[str] += 1
        else:
            data[str] = 1
        str = ""
NewImage = Image.new("RGBA", (500, 500), (255, 255, 255))


Max = 500
mp = [[0 for i in range(0, Max)] for j in range(0, Max)]
# print(mp)


for i in data.keys():
    fontsize = data[i] * 10
    draw = ImageDraw.Draw(NewImage)
    # draw.text((GetPosition(fontsize, len(i))), i, fill=(0, 0, 0), font=ImageFont.truetype("msyh.ttc", fontsize))
    draw.text((GetPosition(fontsize, len(i))), i, fill=(0, 0, 0), font=ImageFont.truetype("msyh.ttc", fontsize))
    del draw


NewImage.save('output.png', 'PNG')
