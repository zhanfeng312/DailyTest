score = int(input("请输入一个分数:"))

if score < 0 or score > 100:
    print ('您的输入有误!')
elif score >= 90 and score <= 100:
    print ('A')
elif score >= 75 and score < 90:
    print ('B')
elif score >= 60 and score < 75:
    print ('C')
else:
    print ('D')
