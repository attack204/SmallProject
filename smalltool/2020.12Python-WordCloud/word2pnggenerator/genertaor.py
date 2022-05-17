tar = open("data.txt", "w")
word = ["分秒", "淡忆", "小公主", "AK", "步篱", "#", "小那", "鱼跃"]
for i in range(0, 8):
    for j in range(0, 8 - i):
        print(word[i], end = " ", file = tar)
tar.close()