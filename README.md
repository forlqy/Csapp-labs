# Csapp-labs
CSAPP官方labs的解答与配置实验环境的问题
## 配置环境
如果在ubuntu 64环境下编译32位程序会出现错误`fatal error: bits/libc-header-start.h: 没有那个文件或目录`，这是因为gcc未安装`multilib`库，这个库可以在64位机器上产生32位程序：
`sudo apt install gcc-multilib`
