# DDL 列表

| DDL截点 | 游戏逻辑需求/安排 | 完成情况 |
| ------- | ----------------- | -------- |
| 第六周末     | 框架文档，解释器文档         |        |
| 第七周周三|分工| |
|第七周周六|对播放器/AI通信协议| |
|第七周末|软工给出对接方式| |
|第九周末|生成完整replay文件| |
|第十一周末|无网站各部件对接| |
|第十三周末|全部对接| |

# 前言

这个ReadMe写得比较匆忙，主要用于辅助阅读代码。

# 解释器 （Loong.h）

## IContent

IContent是用来管理解释器变量的，初始没有类型，类型会在赋值等操作时改变

其中每个IContent对象都包含一个LContent指针，LContent有若干子类，支持各种二元运算符以及小括号(),中括号[]

```c++
#include"Loong.h"
int main()
{
	IContent a,b,c,d;
	a=2;b=3;
	c=a+b;
	d[0].assign(c+a+b);
	a.Print();cout<<endl;
	b.Print();cout<<endl;
	c.Print();cout<<endl;
	d.Print();cout<<endl;
}
```

**特殊说明**：因为IContent对象有可能是LContentPointer，也就是指针。所以在赋值的时候使用**assign**子函数更稳妥，不然有可能会出现将指针赋值给对象的情况。

### LContent

所有IContent默认创建LContent对象，即什么都不是，没有任何信息

### LContentPointer: public LContent

指针实类型，包含一个IContent*，会将所有运算都转接到对应的IContent对象上去。

在对指针对象赋值时，需要使用assign函数，不能直接使用=运算符。

### LContentInt: public LContent

整形类型，支持各种整形运算。

### LContentDouble: public LContent

浮点类型，支持各种浮点运算。

### LContentPos: public LContent

坐标点类型，支持六边形坐标系上的运算。

其中
["Length"]运算符会返回LContentInt类型，表示坐标点到原点六边形坐标系上最短距离

同样还有["EliminateX"], ["EliminateY"], ["EliminateZ"], ["Balance"]等对象，分别对应SavageCoordinate.h中Pos类对应的函数返回值。

### LContentString: public LContent

字符串类型，可以记录字符串

### LContentDictionary: public LContent

字典类型，可以用[由小写字母组成的字符串]访问字典中的元素，返回的是LContentPointer

### LContentVector: public LContent

向量类型，可以用[非负整数]访问向量中的元素，返回的是LContentPointer

## LoongCode类型

直接定义，通过LoadFromFile(const char* filename)函数从filename对应的文件读取Loong代码

## ILoongFunction类型

实际上是IContent(IContent)类函数指针，可以将对应格式的函数赋值到该种类型

## LoongExecuter函数
```c++
IContent LoongExecuter(const LoongCode& code,const map<string, ILoongFunction>& funcspace, map<string, IContent>& contentspace);
```

### 参数

#### code

传LoongCode类型对象，表示需要运行的代码

#### funcspace


传map<string, ILoongFunction>类型对象

用于给代码提供接口函数的变量

若有

```c++
funcspace["abc"]=Func;
```

则在运行Loong代码的时候，调用abc函数会传到Func接口

#### contentspace

传map<string, IContent>类型对象

用于记录所有脚本中用到的变量的对象。脚本中的变量名即对应位置取值

## Loong代码


变量直接赋值即可使用，不用声明。赋值可能改变变量类型
```
a=1;b=1;
```

### 分隔符

分号(;)和逗号(,)

分号隔开两条语句。
逗号则会在隔开两条语句的同时，创造向量类型

```
c=(a=1,b=2); c会被赋值成一个[1,2]的向量
```

### 二元运算符

不支持!,~,-等一元运算符，取负数请使用0.0 - 1.0; 0-1; 等方法

等于号 = 对应C++代码中的assign

```
c=a+b;
```

### 函数

Pos(1,2,3)实际上会传一个向量[1,2,3]到Pos对应的函数接口

Inv(1)则只会传一个整形1，不形成向量[1]

函数的接口功能需要在C++代码端定义对应的函数指针

### 样例

```
a=1;
b[0]=a;
b=b+2;
b=b+0.0;
b=b+b;
```

会得到 a = 1; b = [1, 2, 0.0, [1, 2, 0.0] ];


# 游戏逻辑 （Savage.h）

## GameMap类型

游戏地图

### Init函数

可以从文件中加载地图信息

### BlockType函数

可以返回对应查询位置的类别信息（深渊: 0，平地: 1）

## GameUnitTemp类型

单位模板，所有的游戏内单位实体都由模板创建

### 变量列表

#### temp_type

表示是普通单位（2）还是神器（1）

#### health

表示该种单位初始血量

#### attack

表示攻击力

#### attack_range_near

表示攻击范围的最小值，即比该值更近的单位无法被攻击到

#### attack_range_far

表示攻击范围的最大值，即比该值更远的单位无法被攻击到

#### move_range

表示移动速度，每回合对应单位只能移动该数值以内的距离

#### status

以二进制或的形式叠加记录多种属性

#### height

0表示地面单位，1表示飞行单位

#### 各种LoongCode*类型trigger

对应不同时间对应的触发器

## GameUnit类型

战场中操作的对象。

各项参数直接继承自单位模板，意义相同。

### pid

单位所属阵营

### unit_type

对应的单位模板，拥有对应模板的触发器，和不变属性

### Pos

记录单位在地图上的位置

### 各种_buff

表示对应变量受到的光环影响

## GameWorld

游戏总对象。

包含一个对应的Loong代码接口函数列表，一个游戏地图，一个单位模板池，以及一个单位池。

### LoadTemp

从文件中加载一个单位模板到单位模板池

### CreateUnitFromTemp

由单位模板创建一个包含必要信息的GameUnit类型，需要补全初始位置以及所属阵营信息。

### Summon, Move, Attack, Damage, Kill, Bless

依次表示召唤单位，对对应单位执行移动、攻击、造成伤害、消灭、祝福（加攻击加血量）命令。

会触发对应的触发器

### Refresh

对所有血量小于等于0的仍然活着的单位执行消灭命令。

然后重新结算光环类触发器影响。

