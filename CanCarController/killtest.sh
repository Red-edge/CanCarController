#!/bin/bash

# 获取当前用户的所有终端进程ID
terminals=$(pgrep -u $USER -f -l "gnome-terminal" | awk '{print $1}')

# 检查是否找到终端进程
if [ -z "$terminals" ]; then
    echo "没有找到打开的终端。"
else
    # 杀死所有终端进程
    echo "关闭以下终端进程: "
    echo "$terminals"
    kill -9 $terminals
    echo "终端已关闭。"
fi
