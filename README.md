# README

*此项目写成于2020年6月，由于有一段时间了，具体细节就没有当时记得那么清楚*

此项目为使用C++实现的一个在线订餐系统，数据库使用的是Mysql，如果不懂mysql可以先学习这方面的内容，东西不多，基础内容很快就能学完！

### 运行环境：

1. Visual Studio 2019
2. Mysql server 8.0.20
3. Navicat for Mysql

### 使用：

此页面中只是简单粗略地说一说，具体过程参考tutorial。

在项目路径下有个"store.txt"供学习参考使用，该文本里存储的是可供订餐的商家信息（没有具体到商家的商品），请首先使用Navicat工具或者通过命令行输入mysql语句的方法将此文本导入数据库中。数据库的搭建与配置参考tutorial

##### 配置项：

1. 使用VS打开项目文件后，找到**菜单栏**的 **调试** –> **Order属性**，在弹出的窗口中找到 **C/C++** –> **常规**，在**附加包含目录**一栏添加Mysql的安装路径+'\include'，例如我的Mysql安装路径为C:\Program Files\MySQL\MySQL Server 8.0，那么添加的内容为 C:\Program Files\MySQL\MySQL Server 8.0\include

2. 在同一个属性窗口中，找到**链接器** -> **常规**，在**附加库目录**一栏添加C:\Program Files\MySQL\MySQL Server 8.0\lib（安装目录改成自己的）

3. 找到**链接器** ->  **输入**，在**附加依赖项**添加字符串"libmysql.lib;"（没有引号，添加后记得再加一个分号）

4. 找到 **C** ->  **预处理器**，设置**预处理器定义**一栏的内容为"DEBUG;_CONSOLE;%(PreprocessorDefinitions);_CRT_SECURE_NO_WARNINGS;"

配置完成后（包括数据库），执行VS的×64Debug即可生成exe文件，你可以在工程目录下的/×64/Debug下找到编译产生的文件。

此项目只是一个简单的小demo，当时刚学完C++做的，可能有很多地方不是做得很好，水平有限，敬请谅解！



