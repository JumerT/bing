# bing
这是一个基于Gnome3的命令行程序，在输入命令`bing`后，会将[每日必应壁纸](https://cn.bing.com/)下载到`~/Bing`中，并且设置为桌面壁纸。

### 下载和安装
在安装之前，你需要在先编译安装[libcurl](https://curl.haxx.se/download.html)。
之后将压缩包下载到本地，解压。在文件`Makefile`所在目录中打开终端。
输入命令
> make \
make install \
make clean

在安装过程中需要您输入您的超级用户密码，目的是为了将编译后的程序放入`/usr/bin`目录中。
### 使用
只需要在终端中使用命令
> bing

即可

### 联系和支持
- email: 805077931@qq.com
