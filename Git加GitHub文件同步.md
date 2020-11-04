# **Git加GitHub文件同步**

### 一、安装Git for Windows

​	省略

### 二、github使用

```
git init **初始化仓库**
```

```
git status  **查看状态**
```

```
git add "文件名.后缀"  **上传此文件**
```

```
git  add -A    **上传此目录下所有文件**
```

```
git commit -m "更新的信息" 来提交
```

```
git log 可以查看日志 
```

```
git diff查看改变
```

### 三、Git与GitHub关联使用

	git config --global user.name "你的用户名"

```
git config --global user.email "你的邮箱"
```

```
ssh-keygen -t rsa -C "你的邮箱" ---生成ssh key
```

##### 打开GitHub 进入setting找到ssh key并新建

##### 在c/Users/Administrator/.ssh/id_rsa)文件找到直接复制

```
输入: ssh -T git@github.com --然后测试连接是否成功
```

##### 本地关联GitHub 

 运行 git remote add origin 你复制的地址 

 解决办法: 执行 git pull origin master //没有这个分支 先pull一下

 输入 git push -u origin master 

### 以后的更新提交文件的顺序

​	git status  **查看状态**

​	git  add -A    **上传此目录下所有文件**

​	git commit -m **"更新的信息" 来提交**

​	git push

## git 速度太慢的解决办法

https://www.ipaddress.com/分别搜索

```
github.global.ssl.fastly.net
github.com
```

Windows上的hosts文件路径在`C:\Windows\System32\drivers\etc\hosts`

xx.xx.xx.xx github.global-ssl.fastly.net
xx.xx.xx.xx github.com

Winodws系统的做法：打开CMD，输入`ipconfig /flushdns`