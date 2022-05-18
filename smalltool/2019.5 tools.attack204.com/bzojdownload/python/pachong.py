import urllib
import requests
def getHtml(url):   
    r = requests.get(url)
    return r.text
    # page = urllib.request.urlopen(url)
    # html = page.read()
    # return html

def output(FailName, Str):
    fh = open(FailName, 'w', encoding = 'utf-8')
    fh.write(Str)
    fh.close

content = getHtml("https://ruanx.pw/bzojch/list.html")
output('test.txt', content)
