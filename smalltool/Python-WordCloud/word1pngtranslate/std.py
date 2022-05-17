# coding=utf-8
from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont
import random
txt = '国庆快乐'  # 设置图片中文字的构成
fontsize = 7
# 这个参数如果太小，会使字太小，不够清晰，但整体视觉效果好
# 如果这个参数太大，会使字太大，影响视觉效果
font = ImageFont.truetype('msyh.ttc', fontsize)  # 9为字体大小
im = Image.open('img.jpeg')  # im为待操作的对象
width, height = im.size
newImg = Image.new("RGBA", (width, height), (20, 20, 20))
# 生成待输出的文件
# RGBA用来生成背景色
x = 0
for i in range(0, height, fontsize):  # 需要与字体大小一致
    for j in range(0, width, fontsize):  # 需要与字体大小一致
        a, b, c = im.getpixel((j, i)) #获取指定位置的像素
        draw = ImageDraw.Draw(newImg)
        draw.text((j, i), txt[x], fill=(a, b, c), font=font)
        del draw
        x += 1
        x %= 4
        
newImg.save('result.png', 'PNG')
