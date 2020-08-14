#!/bin/sh

if [ -e "product_config" ]; then
    . ./product_config
fi

echo "start call test1"
test1

echo "start call test2"
$(test2)  # 执行test2中的命令, 此处test2函数打印了This is test2, 会把This is test2作为命令执行
