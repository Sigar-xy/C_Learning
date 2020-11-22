# Ubuntu+Window双系统安装记录

### 1. 下载镜像

​	官网https://www.ubuntu.com/download/alternative-downloads下载Ubuntu16.04 /18.04 Desktop版本

### 2. 下载制作启动盘的软件16.04可以用UltraISO，18.04只能用rufus

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

- 语言推荐英语（后期报错英语论坛的支持比较多）

- 第三方图像软件和wifi硬件和媒体格式添加不用勾选（网速慢机器满会在安装界面停很久）

- 安装选项选something else

#### 接下来是具体的分区问题

一般网上推荐分区挂载需要弄/boot swap /根目录 /home /usr EFI 其实这是根据个人用户决定的

**反正重要的三个点**

- UEFI + GPT 把boot loader安装到EFI（fat32类型的）文件下
- 可以直接用window的EFI文件（因为我发现我自己创一个空盘给efi，但是安装完成后他还是在window的efi文件下了，至今没解决，所以直接用window的efi文件夹不香吗，不用担心大小问题boot都很小的）
- / 根目录最好给大点，因为很多默认软件全都安装到/usr里了，而你不分配/usr那么他自动挂载/根目录下，所以除了你单独挂载了的目录，其他所有的分区都是挂载/根目录下

#### 具体解释

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

