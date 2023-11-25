import smtplib
from email.mime.text import MIMEText
import requests as rq
import re

# 根据需要修改weather/后面的数字，获取你想要的地点
url = "https://tianqi.so.com/weather/101190101"
Headers = \
    {
        "User-Agent": "UAUAUAUAUAUAUAUAUAUAUAUAUAUAUAUAUAUAUAUA",               #此处修改
        "Cookie": "cookiecookiecookiecookiecookie",                             #此处修改
    }
response = rq.get(url, headers=Headers)
content = response.content.decode('utf-8')
if response.status_code == 200:
    with open("weather.html", "w", encoding="utf-8") as f:  # test
        f.write(content)  # test
else:
    print("网络连接失效")
    exit()

with open("weather.html", "r", encoding="utf-8") as f:
    contents = f.read()

# ------基本信息------------基本信息------------基本信息------------基本信息------------基本信息------------基本信息------
city = re.findall("{city: \"(.*?)\" \|\| \"\",src: \"\"}", contents)[0]

current_time = re.findall(
    "</script><div class=\"local-time\">当前时间：<span>(.*?)</span><span>(.*?)</span><span>(.*?)</span></div>",
    contents)
current_time = ' '.join(current_time[0])
current_info = re.findall(
    "当前天气信息</h3><p><span>天气：</span>(.*?)</p>.*?<p><span>体感：</span>(.*?)</p>.*?<p><span>.*?气压：</span>(.*?)</p>.*?<p><span>.*?<p><span>日出：</span>(.*?)</p>.*?<p><span>日落：</span>(.*?)</p>",
    contents)[0]
# 输出格式
# 天气：
# 体感温度：
# 气压：
# 日出：
# 日落：
# ('晴 27℃', '25℃', '1010', '06：21', '17：15')

today_tem = re.findall(
    "<ul class=\"weather-columns\">.*?今天.*?</div><div class=\".*?\"></div><div>.*?([\u4e00-\u9fa5]+).*?</div>.*?<div>(.*?)</div>.*?</ul>",
    contents, re.DOTALL)[0]
today_tem = ' '.join(today_tem)
# 晴 15/28℃
tom_weather = re.findall(
    "<ul class=\"weather-columns\">.*?明天.*?</div><div class=\".*?\"></div><div>.*?([\u4e00-\u9fa5]+).*?</div>.*?<div>(.*?)</div>.*?</ul>",
    contents, re.DOTALL)[0]
tom_weather = ' '.join(tom_weather)
# 多云转阴 18/28℃


# ------指数------------指数------------指数------------指数------------指数------------指数------------指数------

# 获取今明两天的天气指数
clothes = re.findall(
    "<div class=\"card-l life-tips-wrap\">.*?<div class=\"tip-title tip-icon-chuanyi\" title=\"(.*?)\">.*?</div>.*?<div class=\"tip-title tip-icon-chuanyi\" title=\"(.*?)\">.*?</div>",
    contents, re.DOTALL)[0]
# 穿衣指数：热*2
UV_index = re.findall(
    "<div class=\"card-l life-tips-wrap\">.*?<div class=\"tip-title tip-icon-ziwaixian\" title=\"(.*?)\">.*?</div>.*?<div class=\"tip-title tip-icon-ziwaixian\" title=\"(.*?)\">.*?</div>",
    contents, re.DOTALL)[0]
# 紫外线强度指数：强*2
umbrella = re.findall(
    "<div class=\"card-l life-tips-wrap\">.*?<div class=\"tip-title tip-icon-daisan\" title=\"(.*?)\">.*?</div>.*?<div class=\"tip-title tip-icon-daisan\" title=\"(.*?)\">.*?</div>",
    contents, re.DOTALL)[0]
# 雨伞指数：不带伞*2
ganmao = re.findall(
    "<div class=\"card-l life-tips-wrap\">.*?<div class=\"tip-title tip-icon-ganmao\" title=\"(.*?)\">.*?</div>.*?<div class=\"tip-title tip-icon-ganmao\" title=\"(.*?)\">.*?</div>",
    contents, re.DOTALL)[0]
# 感冒指数：少发*2


# print("city", city)
# print("current_time", current_time)
# print("current_info", current_info)
# print("today_tem", today_tem)
# print("tom_weather", tom_weather)
# print("clothes", clothes)
# print("UV_index", UV_index)
# print("umbrella", umbrella)
# print("ganmao", ganmao)
# print(sentences[cnt])
# city 栖霞
# current_time 2023-11-02 周四 17：44
# current_info ('晴 24℃', '24℃', '1008', '06：21', '17：15')
# today_tem 晴 15/28℃
# tom_weather 多云转阴 18/28℃
# clothes ('穿衣指数：热', '穿衣指数：热')
# UV_index ('紫外线强度指数：强', '紫外线强度指数：弱')
# umbrella ('雨伞指数：不带伞', '雨伞指数：不带伞')
# ganmao ('感冒指数：少发', '感冒指数：少发')


# ------------发送设置---------------发送设置---------------发送设置---------发送设置---------发送设置---------发送设置----


main0 = (
    f"地点：{city}\n"
    f"现在是：{current_time}\n"
    f"天气：{current_info[0]} ,体感温度是{current_info[1]} ,气压：{current_info[2]}hPa\n日出：{current_info[3]} ,日落：{current_info[4]}\n\n"
    f"今日天气：{today_tem}\n"
    f"今天：\n{clothes[0]}\t\t{UV_index[0]}\t\t{umbrella[0]}\t\t{ganmao[0]}\n\n"
    f"明日天气：{tom_weather}\n"
    f"明天：\n{clothes[1]}\t\t{UV_index[1]}\t\t{umbrella[1]}\t\t{ganmao[1]}\n\n\n"
    f"{sentences[cnt]}\n\n\n"
    f"数据来源{url}\n\n\n"
)


def send_email_test(name):
    # qq邮箱
    server = smtplib.SMTP_SSL('smtp.qq.com', 465)
    email = "你的邮箱@邮箱.com"                           #此处修改
    server.login(email, "你的授权码")
    title = "今日天气"
    # ------正文------------正文------------正文------------正文------------正文------------正文------------正文------
    # ------正文------------正文------------正文------------正文------------正文------------正文------------正文------
    # ------正文------------正文------------正文------------正文------------正文------------正文------------正文------
    main = main0
    # ------正文------------正文------------正文------------正文------------正文------------正文------------正文------
    # ------正文------------正文------------正文------------正文------------正文------------正文------------正文------
    # ------正文------------正文------------正文------------正文------------正文------------正文------------正文------

    message = MIMEText(main, 'plain', 'utf8')  # 变化为邮箱格式
    # 邮件发送人
    message["From"] = email
    # 邮件接收者
    message["To"] = ','.join([name])
    message["Subject"] = title
    server.sendmail(email, name, message.as_string())
    server.quit()



# 主体
a = input("To whom?enter the email.\n")
send_email_test('a')
print("成功发送邮件内容是：\n")
print(main0)