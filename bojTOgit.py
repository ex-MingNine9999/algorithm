import os
import requests
from bs4 import BeautifulSoup
from selenium import webdriver
import time

path = "/Users/ming._.nine9/Programming/git/algorithm/Problems/"
driverPath = "/Users/ming._.nine9/PycharmProjects/chromedriver"

URL = 'https://www.acmicpc.net/'
mysource1 = "status?from_mine=1&problem_id="
mysource2 = "&user_id="

add = "git add "
commit = "git commit -m "
push = "git push"

print("Input Your BOJ handle")
ID = input()

os.chdir(path)
wd = webdriver.Chrome(driverPath)
wd.implicitly_wait(3)

wd.get(URL + "login?next=%2F")
wd.find_element_by_name("login_user_id").send_keys(ID)
time.sleep(0.5)
wd.find_element_by_name("login_password").send_keys("")
time.sleep(5)

while str(wd.current_url) != URL :
    time.sleep(3)
    continue;

bshtml = BeautifulSoup(requests.get(URL + 'user/' + ID).text, "html.parser")

probNum = bshtml.select("span.problem_number")
probTitle = bshtml.select("span.problem_title")


for i in range(len(probNum)) :
    MySourceURL = URL + mysource1 + probNum[i].text + mysource2 + ID

    bshtml = BeautifulSoup(requests.get(MySourceURL).text, "html.parser")

    solList = bshtml.tbody.findAll("tr")

    for solNum in solList :
        if solNum.select(".result-ac") :
            sn = solNum.td.text
            sourceURL = URL + "source/" + sn
            wd.get(sourceURL)
            time.sleep(0.5)

            bshtml2 = BeautifulSoup(wd.page_source, "html.parser")
            MySource = bshtml2.select("textarea")

            fname = "boj" + probNum[i].text + ".cpp"
            tmpFile = open(path + fname, "w")

            tmpFile.write("//Problem Number : " + probNum[i].text + "\n")
            tmpFile.write("//Problem Title : " + probTitle[i].text + "\n")
            tmpFile.write("//Problem Link : " + URL + "problem/" + probNum[i].text + "\n\n")
            tmpFile.write(MySource[0].contents[0])

            tmpFile.close()

            os.system(add + fname)
            os.system("rm " + fname)
            break

os.system(commit + "Solutions")
os.system(push)

print("Finish!!!")