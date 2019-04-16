#创建 和 转换
#students = ['小明','小红','小刚']
#打印列表
#print(students)
t = ('小明','小红','小刚')
#元组初始化列表
li = list(t)
print(li)

#索引
# print(students[0])
# #分片
# print(students[0:2])
# 追加
# students.append('小美')
# print(students)
# 删除
# del students[3]
# print(students)

A = [1,2,3,4]
B = [5,6,7,8]
A.extend(B)
print(A)

C = [1,2,3,4]
D = [5,6,7,8]
C += D
print(C)