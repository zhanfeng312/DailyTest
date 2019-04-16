#s1 = "fang"

#构造方法
# 无参      创建空字符串
# 一个参数  创建普通字符串
# 两个参数  str(字节，编码)

#两端去除空格
# s1.strip()

#以 ... 开头
# s1.startswith()

#找子序列 "12", "h"
# s1.find()

#将字符串中的某子序列 替换为指定的值
# s1.replace()

#变大写
# s1.upper()

#是 ... 吗?
# s1.isalpha()

#UTF-8 编码，一个汉字，3个字节
name = "战锋"
# for i in name:
#     print(i)
#     byte_list = bytes(i, encoding="utf-8")
#     print(byte_list)
#     for b in byte_list:
#         print(b)

bytes_a1 = bytes(name, encoding="utf-8")
print(bytes_a1)
