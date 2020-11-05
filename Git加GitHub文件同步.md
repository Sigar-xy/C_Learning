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
git  add -A 或 .   **上传此目录下所有文件**
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

强制合并 git pull origin master --allow-unrelated-histories

 输入 git push -u origin master 

### 以后的更新提交文件的顺序

​	git status  **查看状态**

​	git  add -A    **上传此目录下所有文件**

​	git commit -m **"更新的信息" 来提交**

​	git push

### git 速度太慢的解决办法

https://www.ipaddress.com/分别搜索

```
github.global.ssl.fastly.net
github.com
```

Windows上的hosts文件路径在`C:\Windows\System32\drivers\etc\hosts`

xx.xx.xx.xx github.global-ssl.fastly.net
xx.xx.xx.xx github.com

Winodws系统的做法：打开CMD，输入`ipconfig /flushdns`

### Clone项目到另外一台电脑

`git clone 你的.git链接` 

### 查看分支

1.查看所有分支

`git branch -a`

2.查看当前使用分支(结果列表中前面标*号的表示当前使用分支)

`git branch`

3.切换分支

`git checkout 分支名`

### Git中从远程的分支获取最新的版本到本地有这样2个命令：

1. git
 fetch：相当于是从远程获取最新版本到本地，不会自动merge
`git fetch origin master`
`git log -p master..origin/master`
`git merge origin/master`
以上命令的含义：
首先从远程的origin的master主分支下载最新的版本到origin/master分支上
然后比较本地的master分支和origin/master分支的差别
最后进行合并
上述过程其实可以用以下更清晰的方式来进行：
`git fetch origin master:tmp`
`git diff tmp`
`git merge tmp`
从远程获取最新的版本到本地的test分支上
之后再进行比较合并
2. git
 pull：相当于是从远程获取最新版本并merge到本地
`git pull origin master`
上述命令其实相当于git fetch 和 git merge
在实际使用中，git fetch更安全一些
因为在merge前，我们可以查看更新情况，然后再决定是否合并