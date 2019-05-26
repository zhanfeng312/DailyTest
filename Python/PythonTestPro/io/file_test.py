# 文件操作
#打开一个文件
filePath = "scriptTemplates/default.sh"
fp = open(filePath, 'r')

print('文件名: ' + fp.name)
print('是否已关闭: ' + str(fp.closed))
print('访问模式: ' + fp.mode)

#读取文件内容
# 方法1：fileObject.read([count]);
content = fp.read()
print("content:" + str(content))
#方法2：readline()方法 读取单独的一行
# str1 = fp.readline();
# print("str1 :" + str1)
#方法3：readlines()方法 以列表方式返回
# li = fp.readlines()
# print("li :" + str(li))

#关闭文件
fp.close()