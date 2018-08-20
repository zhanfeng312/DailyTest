import random
secret = random.randint(1, 18)

print ('*******欢迎进入猜字游戏**********')

temp = input('请输入一个数字：')
guess = int(temp)
count = 1
b_success = False

while True:
    if guess == secret:
        b_success = True
        break
    elif guess > secret:
        print ('您的输入大了')
    else:
        print ('您的输入小了')

    if count == 4:
        print ('机会已经用完，游戏即将结束')
        b_success = False
        break
    
    temp = input('请再输入一个数字：')
    guess = int(temp)
    
    count += 1

print ('您总共猜了'+ str(count) + '次')

if b_success:
    print ('恭喜恭喜，游戏结束!')
else:
    print ('很遗憾，未能猜到结果，欢迎下次继续玩')
