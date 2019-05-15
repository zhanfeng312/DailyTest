#创建 和 转换

#用字符串初始化列表
s1 = "房战锋"
li = list(s1)
print(li)

# 元组初始化列表
# t = ('小明','小红','小刚')
# li = list(t)
# print(li)

students = ['小明', '小红', '小刚']
#打印列表
print(students)

# 索引
print(students[0])
#分片
print(students[0:2])
#追加
students.append('小美')
print(students)
#删除
del students[3]
print(students)

#扩展列表
A = [1, 2, 3, 4]
B = [5, 6, 7, 8]
A.extend(B)
print(A)
