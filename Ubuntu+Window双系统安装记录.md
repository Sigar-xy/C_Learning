# Ubuntu+Window双系统安装记录--2020.11.22

### 1. 下载镜像

​	官网https://www.ubuntu.com/download/alternative-downloads下载Ubuntu16.04 /18.04 Desktop版本

### 2. 下载制作启动盘的软件16.04可以用UltraISO，18.04只能用rufus

​	<u>rufus会再百分之90多的时候卡着，只要等就行了。18.04比16装的舒适多了</u> -----2020.11.23

https://cn.ultraiso.net/xiazai.html

https://rufus.ie/downloads/

### 3. 关于启动项编辑的软件和适配问题

EasyBCD是用来弄legacy引导 + MBR格式的（这个太老了，而且磁盘大小有限制，别用了，除非电脑太老）同时window黑背景选择界面是GRUB方式

Easy'UEFI是用来弄UEFI引导 + GPT格式的（都什么年代了，肯定用这个啊）

### 4. 做完启动盘后需要给电脑进行的设置

1. BIOS里设置关闭security boot项，

2. 设置boot mode为UEFI（不能legacy+UEFI）我用legacy+UEFI时候分区时候没有efi类型给我选，我去BIOS改了只用UEFI启动就有了

3. windows下关闭fast boot（系统--电源--其他电源设置--选择电源按钮的功能--更改）

4. 切换到configuration，设置SATA Controller Mode为AHCI（这个很重要，不设置成AHCI会导致读不出硬盘）**我去看的时候是默认的这个**

### 5. 开始安装

主板引导启动盘自己查主板型号对应哪一个键前面的选项不赘述了，下面进入安装。

- 语言推荐英语（后期报错英语论坛的支持比较多），
- <u>其实选择最小安装就好了，很干净，不需要再进去处理一些用不到的官方的软件</u>---2020.11.23
- 第三方图像软件和wifi硬件和媒体格式添加不用勾选（网速慢机器满会在安装界面停很久）
- 安装选项选something else

#### 接下来是具体的分区问题

一般网上推荐分区挂载需要弄/boot swap /根目录 /home /usr EFI 其实这是根据个人用户决定的

**反正重要的三个点**

- UEFI + GPT 把boot loader安装到EFI（fat32类型的）文件下
- 可以直接用window的EFI文件（因为我发现我自己创一个空盘给efi，但是安装完成后他还是在window的efi文件下了，至今没解决，所以直接用window的efi文件夹不香吗，不用担心大小问题boot都很小的）
- / 根目录最好给大点，因为很多默认软件全都安装到/usr里了，而你不分配/usr那么他自动挂载/根目录下，所以除了你单独挂载了的目录，其他所有的分区都是挂载/根目录下

#### 分区具体解释

- **"/"** 是根目录("/"类似于Windows的 c 盘，所以这个目录下装的是系统的东西，如果你安装软件习惯默认安装，没有修改路径的习惯，建议 "/" 多分配点空间，因为默认安装的软件都被安装在 "/usr"目录里面) **选择主分区 EXT4格式**对照window C盘是主分区，其他全是逻辑分区（所以其他都选择logical）

- **"/home"** 是用户文件夹**EXT4格式**（多用户需求很高，再就是这个是唯一图像界面用户可以直接操作的空间，平时存东西都可以放这里其他空间都需要**sudo**）**不推荐弄root用户，容易崩，**

- swap交换空间，这个也就是虚拟内存的地方，也可以不设置，空间大可以分一个一比一够了，应该对系统稳定有一点点心里作用**就ubuntu18.04而言，这个swap 完全可以不要**

**我觉得只需挂载这三个分区就够了**

-  /boot 老机器或者就是用legacy + MBR格式的电脑，需要弄个/boot **并且boot loader选择这里**

- 挂载“/usr，软件安装位置，Linux下一般来说安装第三方软件你是没办法更改安装目录的，系统都会统一地安装到/usr目录下面，可以不用管，直接加大/根目录大小。        

### 最后等着安装就好了

Win10 和Ubuntu 启动引导向管理软件解决办法：https://blog.csdn.net/xrinosvip/article/details/80994450

Ubuntu 下使用Linux命令简单总结：https://blog.csdn.net/xrinosvip/article/details/80894728

[解决Windows10与Ubuntu16.04双系统时间不一样问题！（亲测，真正的正确方案）](https://blog.csdn.net/zyqblog/article/details/79318955)

安装完后的琐事：https://www.jb51.net/article/100611.htm

# ubuntu18.04下搭建深度学习环境

**PC：ubuntu18.04、r5 2600、微星GTX1060显卡、固态硬盘、机械硬盘**

一开始装了16.04然后装的很没有头绪，一开始显卡驱动下载的super慢，弄得心态有问题了，换了很多源都不能解决，最后直接放弃治疗，回windows端重新研究，再整装出发。

### 装完系统后需要操作的

#### 更新软件源

源的好坏涉及的能不能愉快的下软件

```
备份原有源,恢复时有用  

sudo cp /etc/apt/sources.list /etc/apt/sources.list.backup 

修改更新源，添加相应的镜像源 

sudo gedit /etc/apt/sources.list 

更新源并升级系统 

sudo apt-get update 

sudo apt-get upgrade
```

**阿里云开源镜像站（推荐） http://mirrors.aliyun.com/** 

#### 中文输入法（适用于18.04）

language-->manage installed languages-->install/remove languages...-->choose Chinese(simplified)

在中文语言包安装完成后，就需要安装ibus输入法了，安装ibus框架需要在Terminal中输入：

`sudo apt-get install ibus ibus-clutter ibus-gtk ibus-gtk3 ibus-qt4`

ibus框架安装完成后，再切换到ibus框架，即在Terminal中输入：

`im-config -s ibus`

然后调出 IBus Preference 窗口来添加该中文拼音输入法，即在Terminal中输入：

`sudo ibus-setup`

**（若项找不到，log out，再进去设置就有了）**

在弹出的窗口上选择 input Method --> Add --> choose Chinese->Pinyin --> Add

`language-->manage installed languages--> 点击+号添加Chinese（Pinyin）`

### 装环境之前的准备工作

#### 经过测试的构建配置（linux-GPU）

| 版本                  | Python 版本  | 编译器    | 构建工具     | cuDNN | CUDA |
| :-------------------- | :----------- | :-------- | :----------- | :---- | :--- |
| tensorflow-2.1.0      | 2.7、3.5-3.7 | GCC 7.3.1 | Bazel 0.27.1 | 7.6   | 10.1 |
| tensorflow-2.0.0      | 2.7、3.3-3.7 | GCC 7.3.1 | Bazel 0.26.1 | 7.4   | 10.0 |
| tensorflow_gpu-1.14.0 | 2.7、3.3-3.7 | GCC 4.8   | Bazel 0.24.1 | 7.4   | 10.0 |
| tensorflow_gpu-1.13.1 | 2.7、3.3-3.7 | GCC 4.8   | Bazel 0.19.2 | 7.4   | 10.0 |
| tensorflow_gpu-1.12.0 | 2.7、3.3-3.6 | GCC 4.8   | Bazel 0.15.0 | 7     | 9    |
| tensorflow_gpu-1.11.0 | 2.7、3.3-3.6 | GCC 4.8   | Bazel 0.15.0 | 7     | 9    |
| tensorflow_gpu-1.10.0 | 2.7、3.3-3.6 | GCC 4.8   | Bazel 0.15.0 | 7     | 9    |
| tensorflow_gpu-1.9.0  | 2.7、3.3-3.6 | GCC 4.8   | Bazel 0.11.0 | 7     | 9    |
| tensorflow_gpu-1.8.0  | 2.7、3.3-3.6 | GCC 4.8   | Bazel 0.10.0 | 7     | 9    |
| tensorflow_gpu-1.7.0  | 2.7、3.3-3.6 | GCC 4.8   | Bazel 0.9.0  | 7     | 9    |
| tensorflow_gpu-1.6.0  | 2.7、3.3-3.6 | GCC 4.8   | Bazel 0.9.0  | 7     | 9    |
| tensorflow_gpu-1.5.0  | 2.7、3.3-3.6 | GCC 4.8   | Bazel 0.8.0  | 7     | 9    |
| tensorflow_gpu-1.4.0  | 2.7、3.3-3.6 | GCC 4.8   | Bazel 0.5.4  | 6     | 8    |
| tensorflow_gpu-1.3.0  | 2.7、3.3-3.6 | GCC 4.8   | Bazel 0.4.5  | 6     | 8    |
| tensorflow_gpu-1.2.0  | 2.7、3.3-3.6 | GCC 4.8   | Bazel 0.4.5  | 5.1   | 8    |
| tensorflow_gpu-1.1.0  | 2.7、3.3-3.6 | GCC 4.8   | Bazel 0.4.2  | 5.1   | 8    |
| tensorflow_gpu-1.0.0  | 2.7、3.3-3.6 | GCC 4.8   | Bazel 0.4.2  | 5.1   | 8    |

​	**这个图在官方文档里找的 https://tensorflow.google.cn/install/source 里面介绍的还蛮详细的可以看一看**

**然后就是对应着下载对应的cuda cudnn Anaconda 这三个最好是提前下载好，因为进系统下载有可能太慢了**

CUDA 下载地址 [点击打开链接](https://developer.nvidia.com/cuda-toolkit-archive)

cudnn 下载地址(需要注册账号) [点击打开链接](https://developer.nvidia.com/cudnn)

tensorflow-cpu 下载地址 [点击打开链接](http://mirrors.aliyun.com/pypi/simple/tensorflow/)

tensorflow-gpu 下载地址 [点击打开链接](http://mirrors.aliyun.com/pypi/simple/tensorflow-gpu/)

anaconda/python下载见另一篇博客 [点击打开链接](https://blog.csdn.net/yuejisuo1948/article/details/81043823)

例如你要建一个python3.5的虚拟环境（其中myenv是这个环境的名称，可以自定）：

```
conda create -n myenv python=3.5
```

然后用以下命令进入该虚拟环境即可：

```
activate myenv
```

#### Anaconda版本对应的python版本

| Release date | conda        | python2.7                         | python3.4 | python3.5                      | python3.6                      | python3.7                        | python3.8 |
| ------------ | ------------ | --------------------------------- | --------- | ------------------------------ | ------------------------------ | -------------------------------- | --------- |
| 2015-02-25   |              |                                   | 3.4.3     |                                |                                |                                  |           |
| 2015-05-23   |              | 2.7.10                            |           |                                |                                |                                  |           |
| 2015-09-13   |              |                                   |           | 3.5.0                          |                                |                                  |           |
| 2015-12-05   |              | 2.7.11                            |           |                                |                                |                                  |           |
| 2015-12-07   |              |                                   |           | 3.5.1                          |                                |                                  |           |
| 2015-12-21   |              |                                   | 3.4.4     |                                |                                |                                  |           |
| 2016-03-29   | conda 4.0.5  | Anaconda2-4.0.0 (python 2.7.11)   |           | Anaconda3-4.0.0 (python 3.5.1) |                                |                                  |           |
| 2016-06-28   | conda 4.1.4  | Anaconda2-4.1.0 (python 2.7.11)   |           | Anaconda3-4.1.0 (python 3.5.1) |                                |                                  |           |
| 2016-06-25   |              | 2.7.12                            |           |                                |                                |                                  |           |
| 2016-06-27   |              |                                   | 3.4.5     | 3.5.2                          |                                |                                  |           |
| 2016-07-08   | conda 4.1.6  | Anaconda2-4.1.1 (python 2.7.12)   |           | Anaconda3-4.1.1 (python 3.5.2) |                                |                                  |           |
| 2016-09-28   | conda 4.2.9  | Anaconda2-4.2.0 (python 2.7.12)   |           | Anaconda3-4.2.0 (python 3.5.2) |                                |                                  |           |
| 2016-12-17   |              | 2.7.13                            |           |                                |                                |                                  |           |
| 2016-12-23   |              |                                   |           |                                | 3.6.0                          |                                  |           |
| 2017-01-17   |              |                                   | 3.4.6     | 3.5.3                          |                                |                                  |           |
| 2017-01-31   | conda 4.3.8  | Anaconda2-4.3.0 (python 2.7.13)   |           |                                | Anaconda3-4.3.0 (python 3.6.0) |                                  |           |
| 2017-03-10   | conda 4.3.14 | Anaconda2-4.3.1 (python 2.7.13)   |           |                                | Anaconda3-4.3.1 (python 3.6.0) |                                  |           |
| 2017-03-21   |              |                                   |           |                                | 3.6.1                          |                                  |           |
| 2017-05-31   | conda 4.3.21 | Anaconda2-4.4.0 (python 2.7.13)   |           |                                | Anaconda3-4.4.0 (python 3.6.1) |                                  |           |
| 2017-07-17   |              |                                   |           |                                | 3.6.2                          |                                  |           |
| 2017-08-08   |              |                                   |           | 3.5.4                          |                                |                                  |           |
| 2017-08-09   |              |                                   | 3.4.7     |                                |                                |                                  |           |
| 2017-09-26   | conda 4.3.27 | Anaconda2-5.0.0 (python 2.7.13)   |           |                                | Anaconda3-5.0.0 (python 3.6.2) |                                  |           |
| 2017-09-16   |              | 2.7.14                            |           |                                |                                |                                  |           |
| 2017-10-03   |              |                                   |           |                                | 3.6.3                          |                                  |           |
| 2017-10-25   | conda 4.3.30 | Anaconda2-5.0.1 (python 2.7.14)   |           |                                | Anaconda3-5.0.1 (python 3.6.3) |                                  |           |
| 2017-12-19   |              |                                   |           |                                | 3.6.4                          |                                  |           |
| 2018-02-05   |              |                                   | 3.4.8     | 3.5.5                          |                                |                                  |           |
| 2018-02-15   | conda 4.4.10 | Anaconda2-5.1.0 (python 2.7.14)   |           |                                | Anaconda3-5.1.0 (python 3.6.4) |                                  |           |
| 2018-03-28   |              |                                   |           |                                | 3.6.5                          |                                  |           |
| 2018-05-01   |              | 2.7.15                            |           |                                |                                |                                  |           |
| 2018-05-30   | conda 4.5.4  | Anaconda2-5.2.0 (python 2.7.15)   |           |                                | Anaconda3-5.2.0 (python 3.6.5) |                                  |           |
| 2018-06-27   |              |                                   |           |                                | 3.6.6                          | 3.7.0                            |           |
| 2018-08-02   |              |                                   | 3.4.9     | 3.5.6                          |                                |                                  |           |
| 2018-09-28   | conda 4.5.11 | Anaconda2-5.3.0 (python 2.7.15)   |           |                                |                                | Anaconda3-5.3.0 (python 3.7.0)   |           |
| 2018-10-20   |              |                                   |           |                                | 3.6.7                          | 3.7.1                            |           |
| 2018-12-21   | conda 4.5.12 | Anaconda2-2018.12 (python 2.7.15) |           |                                |                                | Anaconda3-2018.12 (python 3.7.1) |           |
| 2018-12-24   |              |                                   |           |                                | 3.6.8                          | 3.7.2                            |           |
| 2019-03-04   |              | 2.7.16                            |           |                                |                                |                                  |           |
| 2019-03-18   |              |                                   | 3.4.10    | 3.5.7                          |                                |                                  |           |
| 2019-03-25   |              |                                   |           |                                |                                | 3.7.3                            |           |
| 2019-04-04   | conda 4.6.11 | Anaconda2-2019.03 (python 2.7.16) |           |                                |                                | Anaconda3-2019.03 (python 3.7.3) |           |
| 2019-07-02   |              |                                   |           |                                | 3.6.9                          |                                  |           |
| 2019-07-08   |              |                                   |           |                                |                                | 3.7.4                            |           |
| 2019-07-24   | conda 4.7.10 | Anaconda2-2019.07 (python 2.7.16) |           |                                |                                | Anaconda3-2019.07 (python 3.7.3) |           |
| 2019-10-14   |              |                                   |           |                                |                                |                                  | 3.8.0     |
| 2019-10-15   |              |                                   |           |                                |                                | 3.7.5                            |           |
| 2019-10-19   |              | 2.7.17                            |           |                                |                                |                                  |           |
| 2019-10-29   |              |                                   |           | 3.5.8                          |                                |                                  |           |
| 2019-11-02   |              |                                   |           | 3.5.9                          |                                |                                  |           |

|                   | anaconda                                                     | miniconda                                                    |
| ----------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 镜像下载地址      | https://mirrors.tuna.tsinghua.edu.cn/anaconda/archive/?C=N&O=D | https://mirrors.tuna.tsinghua.edu.cn/anaconda/miniconda/?C=N&O=D |
| 官方首页          | https://www.anaconda.com/distribution/                       | https://docs.conda.io/en/latest/miniconda.html               |
| 官方下载地址      | https://repo.anaconda.com/archive/                           | https://repo.anaconda.com/miniconda/                         |
| 官方文档          | https://docs.anaconda.com/anaconda/                          |                                                              |
| old package lists | https://docs.anaconda.com/anaconda/packages/oldpkglists/     |                                                              |
| release notes     | https://docs.anaconda.com/anaconda/reference/release-notes/  |                                                              |

### 开始安装环境

#### **1. 安装ssh**

`sudo apt-get install openssh-server`

#### **2. 安装显卡驱动**

默认安装的显卡驱动不是英伟达的驱动，所以先把旧得驱动删除掉。

`sudo apt-get purge nvidia*`

添加Graphic Drivers PPA

```
sudo add-apt-repository ppa:graphics-drivers/ppa 

sudo apt-get update
```

查看合适的驱动版本：

`ubuntu-drivers devices`

直接使用recommended

`sudo apt-get install nvidia-driver-XXX`

`sudo reboot**重启生效**`

`nvidia-smi`**查看是否生效了**

#### **3. 安装依赖库**

`sudo apt-get install freeglut3-dev build-essential libx11-dev libxmu-dev libxi-dev libgl1-mesa-glx libglu1-mesa libglu1-mesa-dev`

#### **4. GCC降低版本**

- 版本安装

```text
# 版本安装：
sudo apt-get install gcc-5
sudo apt-get install g++-5

```

- gcc -v 查看当前gcc版本
- 通过命令替换掉之前的版本

```text
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 50
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-5 50
```

上面的50是指这个版本的优先级，值越大，优先级越高

**使用如下命令选择gcc的版本**

sudo update-alternatives --config gcc

想选择哪个版本为默认值，直接输入编号就行。

**最后，可通过gcc -v语句验证是否更改成功**

#### **5. 安装CUDA9.0**

下载进入目录后，依次执行命令：

注意：在安装过程中会提示是否需要安装显卡驱动，在这里要选择**n**，其他的选择**y**或者回车键进行安装:

```text
sudo sh cuda_9.0.176_384.81_linux.run

sudo sh cuda_9.0.176.1_linux.run

sudo sh cuda_9.0.176.2_linux.run

sudo sh cuda_9.0.176.3_linux.run

sudo sh cuda_9.0.176.4_linux.run

```

- 在~/.bashrc 中设置环境变量：

```text
sudo vim ~/.bashrc
```

在最后添加：

```text
exportPATH=/usr/local/cuda-9.0/bin${PATH:+:${PATH}} 
exportLD_LIBRARY_PATH=/usr/local/cuda-9.0/lib64${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}
```

重启后，测试**CUDA**是否成功（此步骤可以省略）

```text
cd ~/NVIDIA_CUDA-9.0_Samples/1_Utilities/deviceQuery 
make -j4  
sudo ./deviceQuery
123
```

若会输出相应的显卡性能信息，**Result = PASS**，表明**CUDA**安装成功。

#### **6. 安装CUDNN**

下载后安装非常简单，就是解压然后拷贝到相应的系统CUDA路径下，注意最后一行拷贝时 "-d"不能少，

```text
tar -zxvf cudnn-9.0-linux-x64-v7.4.1.5.tgz

sudo cp cuda/include/cudnn.h /usr/local/cuda/include

sudo cp cuda/lib64/libcudnn* /usr/local/cuda/lib64

sudo chmod a+r/usr/local/cuda/include/cudnn.h /usr/local/cuda/lib64/libcudnn*
```

#### **7.安装Tensorflow GPU 1.8**

1）安装Anaconda

下载地址：[https://www.anaconda.com/download/](https://link.zhihu.com/?target=https%3A//www.anaconda.com/download/)

```text
bash Anaconda3-5.3.0-Linux-x86_64.sh

```

2）更改pip和conda为国内的源

由于国内访问pip和conda比较慢，建议更改为国内的源：

a.更改pip的源为阿里云：

```text
mkdir ~/.pip
1）方法一
cat > ~/.pip/pip.conf << EOF
[global]
trusted-host=mirrors.aliyun.com
index-url=https://mirrors.aliyun.com/pypi/simple/
EOF
2）方法二
vim ~/.pip/pip.conf
2 //写入一下内容
3 [global]
4 trusted-host=mirrors.aliyun.com
5 index-url=http://mirrors.aliyun.com/pypi/simple/

```

b.更改conda的源为清华大学：

```text
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main/
conda config --set show_channel_urls yes

```

3）在Anaconda中安装Python3.6的虚拟环境

由于Anaconda的python版本是3.7的，TensorFlow尚不支持此版本，于是我们创建一个Python的虚拟环境

```text
conda create --name tf python=3.6 #创建tf环境

```

虚拟环境主要命令：

```text
source activate tf             #激活tf环境
1
source deactivate tf          #退出tf环境
1
conda remove --name tf --all  #删除tf环境（全部删除）
```

在Anaconda中安装TensorFlow GPU 这个命令好像直接下载最新了（不过需要降级直接装低版本会卸载高版本）

```text
pip install --ignore-installed --upgrade tensorflow-gpu
//////或者
pip install tensorflow-gpu==1.7
```

conda安装方式：

```
conda install tensorflow-gpu==1.8
```

使用下列代码测试安装正确性

命令行输入：

```text
source activate tf
python

```

Python命令下输入以下代码：

```text
import tensorflow as tf
hello= tf.constant('Hello, TensorFlow!')
sess= tf.Session()
print(sess.run(hello))
```

没有报错就是配置好了。

#### **8. 安装Keras**

直接在这个虚拟环境中安装：

```text
pip install keras
```

-------------------2020.11.23修订环境安装

