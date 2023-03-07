# 设计模式

## Q: 为什么全局和静态变量是邪恶的？你能给出一个代码例子吗？


1. 对于 C 语言来说，占据了静态存储区，使程序变大
2. 破坏封装，函数不是幂等的
3. 代码可读性下降
4. 多线程程序会造成竞态条件

## Q: 给我讲讲 Inversion of Control，以及他是如何提升代码的设计水平的

其实很简单，就是把一段代码中需要依赖的另一个类从这段代码中移出来，然后把生成的结果传递到这段代码中，这就是 Inversion of Control 了

https://stackoverflow.com/questions/3058/what-is-inversion-of-control

## Q: Demeter 定律（最小知识原则）说一个单元应该对其他单元了解的知识越少越好，而且应该只能和他的直接相关单元通信（或者说“不要和陌生人说话”）。你会写违反这个原则的代码吗？展示下为什么这个是不好的设计然后修复他。

比如说一个类不应该访问另一个类的数据成员，而应该通过getter方法来访问。当然这样做可能会使运行效率低下。但是比如说另一个类的实现改变的时候，我们不需要改动代码，因为没有依赖。

## Q: Active Record 模式提倡对象中包含增删改查等方法，并且每个属性都对应到数据库的表中字段，介绍一下这种模式的限制和坑

但是缺少灵活性，实际中当你每次处理一张表时使用这个模式是可以的， 但是当你要处理很多关联表，类继承关系较为复杂的时候就会有很多问题，这种情况你可以使用Data Mapper模式

像是 Django，RoR 都是采用的 Active Record 模式

ref: http://www.jacopobeschi.com/post/active-record-design-pattern

## Q: Data Mapper 模式提倡使用一层mapper来在对象和数据库之间传递数据，但是保持了它们两者之间的独立。相反 Active Record 模式直接持久化到数据库中。关于两者你有什么看法？为什么使用其中一个而不是用其中另一个呢？

我们看到它在存数据的时候，没有用$user->save()去存，而是用了另一个类EntityManager去存。也就是说，它的模型$user没有继承一个数据库操作类，$user和数据库完全是分离开的。
它这样做有什么好处呢？$user没有继承一个庞大的基类，变得轻便多了。就好像蜗牛甩掉了重重的壳，变成了蛞蝓。
这是反Active Record人士最重要的攻击点，他们会嫌Active Record性能差。
另外一个就是在Data Mapper模式下，模型，数据操作层，数据库这三者是完全分开的，所以不必一一对应，这样在某些情况下是很灵活的。

ref: http://larabase.com/post/156

## Q: 为什么经常说 null 的引入是一个“价值百万美元的错误”？能不能谈一下避免Null值的一些设计模式，比如 Null Object 模式 和 Option Types？

A: null 是一个没有值的值，这就是错误。实际上，比如在Python中，我就经常遇到 None object has no method xxx 的问题。

Null Ojbect pattern 就是定义一个空对象，让它来当做当值为空时候的对象，而不要使用Null值来表示空。比如返回空字符串而不是None，避免了检查返回是不是为null的问题。

在一些编程语言，尤其是函数式编程语言中，Option Type 是一个多态的类型，表示的是函数可能返回一个有效的值或者无效的值

ref:

1. https://www.lucidchart.com/techblog/2015/08/31/the-worst-mistake-of-computer-science/
2. http://www.cnblogs.com/gaochundong/p/design_pattern_null_object.html
3. https://en.wikipedia.org/wiki/Option_type

## Q: 好多人说在 OOP 中，组合比继承更好，你的观点呢？

A: 首先，类型系统看起来很好，太复杂了，问题就很多。其次，继承表达了 is-a 的关系，如果遇到要实现两个接口就很复杂。组合的话更加模块化一点。

ref: https://www.zhihu.com/question/49008835

## Q: 什么是 Anti-Corruption Layer？

通过在旧系统和新式系统之间放置防损层，将它们隔离。 此层转换两个系统之间的通信，在旧系统保持不变的情况下，新式应用程序可以避免破坏其设计和技术方法。

新式应用程序和防损层之间的通信始终使用应用程序的数据模型和体系结构。 从防损层到旧系统的调用符合该系统的数据模型或方法。 防损层包含在两个系统之间转换所必需的所有逻辑。 该层可作为应用程序内的组件或作为独立服务实现。

ref: https://docs.microsoft.com/zh-cn/azure/architecture/patterns/anti-corruption-layer

## Q: 写一个线程安全的单例模式

A: 这个也是经典问题了，但是实际上感觉并没有卵用，但是大家就是喜欢问

    import threading

    class SingletonMixin:

        _singleton_lock = threading.Lock()
        _singleton_instance = None

        @classmethod
        def get_instance(cls):
            if not cls._singleton_instance:
                # 其他语言中使用 lock 和 unlock，而 Python 的with语句就很方便了
                with cls._singleton_lock:
                    if not cls._singleton_instance:
                        cls._singleton_instance = cls()
            return cls._singleton_instance

也可以使用装饰器实现

## Q: 能够改变具体实现而不用更改使用方代码叫做数据抽象。给出一个违反这个原则的例子，然后修复他

A: 尽量使用 getter 和 setter，而不要直接访问数据成员。当然在 Python 中有更好的方法(properties)

## Q: 写一段违反 DRY 原则的代码，然后修复他

A: 这也太简单了。。正常人哪儿有写重复代码的，基本都是过度封装居多。

## 如何处理 Dependency Hell（依赖地狱）

1. 首先用包管理器，不要手工拷贝代码管理依赖
2. 多使用 virtual env 等虚拟环境工具
3. 使用 docker 打包镜像

## Q: goto 语句是有害的吗？关于使用 goto 语句你有什么看法呢？

肯定最好别用。。

## Q: 保持软件健壮的一个核心原则是，对你的输出要严格，但是对你的输入要保持宽容，能不能讨论一下这个原则?

比如说对于一个函数来说，可以接受不同类型的值，但是，输出得时候要注意保证自己的输出是有效的。


    def add(a, b):
        a = int(a)
        b = int(b)
        return a + b

## Command-Query Separation (CQS)  – 命令-查询分离原则

查询：当一个方法返回一个值来回应一个问题的时候，它就具有查询的性质；
命令：当一个方法要改变对象的状态的时候，它就具有命令的性质；

通常，一个方法可能是纯的Command模式或者是纯的Query模式，或者是两者的混合体。在设计接口时，如果可能，应该尽量使接口单一化，保证方法的行为严格的是命令或者是查询，这样查询方法不会改变对象的状态，没有副作用，而会改变对象的状态的方法不可能有返回值。也就是说：如果我们要问一个问题，那么就不应该影响到它的答案。实际应用，要视具体情况而定，语义的清晰性和使用的简单性之间需要权衡。将Command和Query功能合并入一个方法，方便了客户的使用，但是，降低了清晰性，而且，可能不便于基于断言的程序设计并且需要一个变量来保存查询结果。

在系统设计中，很多系统也是以这样原则设计的，查询的功能和命令功能的系统分离，这样有则于系统性能，也有利于系统的安全性。

## Q: 责任分离原则用来把计算机程序分解到不同的领域，有不同的方法来实现这个原则（比如 对象、函数、模块、设计模式）等等，能不能讨论下这个话题?

一旦一个函数被抽像出来并实现了，那么使用函数的人就不用关心这个函数是如何实现的，同样的，一旦一个类被抽像并实现了，类的使用者也不用再关注于这个类的内部是如何实现的。

ref: https://coolshell.cn/articles/4535.html

# 代码设计问题

## 经常听人说，在OO设计中要满足高内聚和低耦合，这个是什么意思，怎么实现？

耦合性与内聚性是模块独立性的两个定性标准，将软件系统划分模块时，尽量做到高内聚低耦合，提高模块的独立性，为设计高质量的软件结构奠定基础。

有个例子很容易明白：一个程序有50个函数，这个程序执行得非常好；然而一旦你修改其中一个函数，其他49个函数都需要做修改，这就是高耦合的后果。

ref: https://www.cnblogs.com/robnetcn/archive/2012/04/15/2449008.html

## 为什么大多数语言的数组索引都是从0开始的

因为 C 是从0开始的，大多数语言都受C的影响，另外就是C接近硬件，0表示的是偏移量

## 测试与 TDD 如何影响代码设计

1. 有了测试用例以后重构更容易，而重构可以带来更好的代码
2. 测试更深入细节，可以更好的帮助思考

ref: http://www.jamesshore.com/Blog/How-Does-TDD-Affect-Design.html

## 内聚和耦合的区别在于？

内聚是应该在一起的，而耦合是不应该在一起的因为设计失误而在一起。

## 代码中的注释有用吗？有些人说应该尽量避免注释，你同意吗？

我同意，代码应该尽量是自解释的，而不是借助于注释才能明白

我觉得以下情况下才需要添加注释：

* 解释了业务逻辑和总体设计，这往往也是文档的一部分
* 采用了特殊的用法
* 算法比较复杂，代码无法解释清楚

## 设计和架构之间的区别是？

这个问题也太抽象了吧，架构是设计的实现。。

## 为什么 TDD 中要在代码之前写测试

* 测试定义了代码完成的标志
* 测试是你代码如何使用的文档
* 面向测试编程可以让你保持专注

## C++ 支持多重继承，而在 Java 中允许一个类去实现多个 interface。使用这些方法对于代码的正交性有什么影响吗？使用多重继承和实现多个 interface 有什么区别吗？使用委托和使用继承有什么区别吗？


多重继承的不好就不用多说了吧，尽量避免继承。。

## 把业务逻辑都放在 Stored Procedures 中的好处和坏处

貌似意思是把业务逻辑都写在数据库里，这得多奇葩呀。。不过银行系统里似乎的确是这么用的，厉害啊

ref: https://softwareengineering.stackexchange.com/questions/158534/pros-and-cons-of-holding-all-the-business-logic-in-stored-procedures-in-web-appl

## 为什么 OO 设计垄断了业界这么多年？

OO 的好处：

1. 限制对数据成员的访问，减少代码耦合
2. 提供了一个抽象层，类是对现实世界的事物的一个很好抽象

## 你用什么方法来评价你的代码是否设计有问题？

这个问题太抽象了

# 语言相关问题

## 说出你喜欢的语言的三个缺点

Python：GIL、性能慢、2 和 3不兼容

## 为什么现在函数式编程的影响越来越大？

两个方面回答，一方面，为什么之前函数式编程不流行，函数式编程性能往往不高，例如垃圾处理等，这时候大家更愿意使用贴近硬件的 C 语言等
另一方面，函数式编程没有副作用，更好地适应并发高的情形。可以证明正确性。多核处理器的出现等等。方便实现高阶函数

## 什么是闭包，它和类之间有什么联系？

闭包和类都创建了一个独立的作用域，其中定义的函数都可以访问这个空间内的变量，闭包创建的作用域在函数执行结束之后依然是有效的

    function() {
        var a = 1;
        console.log(a);  // works, -> 1
    }
    console.log(a);  // fails, -> undefined

    function outer() {
        let a = 1
        function inner() {
            console.log(a)
        }
        return inner
    }

    let fn = outer()
    fn()  // -> 1

ref: https://stackoverflow.com/questions/36636/what-is-a-closure

## 泛型有什么用

## 高阶函数是什么？写一个

    def get_counter():
        count = 0
        def counter():
            count += 1
            return count
        return counter


## 写一个循环，然后把它变成一个递归，不要使用变量

    def sum(l):
        ret = 0
        for i in l:
            ret += i
        return ret

    def sum2(l):
        if len(l) == 0:
            return 0
        if len(l) == 1:
            return l[0]
        return l + sum2(l[1:])

## 当我们说一个语言中，函数是一等公民的时候，我们想表达什么

函数可以向其他变量一样被传递

ref: https://stackoverflow.com/questions/5178068/what-is-a-first-class-citizen-function

## 给我写一个匿名函数的例子

    filter([1, 2, 3, 4], lambda x: x % 2 == 0)

## 有很多不同的类型系统，我们来讨论一下静态和动态类型系统，以及强类型和弱类型。关于这个话题你肯定有你自己的观点，然后分享一下当开发一个企业级的系统的时候，你会如何选择

静态类型系统是指的变量绑定的类型在生命周期内不可变，而动态类型系统则相反。

强类型指的是两个互相操作的变量必须类型匹配，而弱类型则会自动转换。

比如在弱类型的 JS 中：

    let a = "1" + 1  // a = 2

而在强类型的 Python 中：

    In [1]: a = "1" + 1
    ---------------------------------------------------------------------------
    TypeError                                 Traceback (most recent call last)
    <ipython-input-1-c5310317b555> in <module>()
    ----> 1 a = "1" + 1

    TypeError: must be str, not int

实际上好多人分不清楚，什么是动态类型，什么是弱类型。

在开发大规模的软件的时候，使用静态强类型语言会好一些，这样编译器就可以做好多的检
查工作。

## 聊聊 Java 和 C# 之间的互操作性，或者其他任意两种语言之间

可以通过队列或者RPC来实现通信

## 命名空间有什么用？

可以让两个两个模块使用同一个名字

## 为什么很多工程师不喜欢 Java

啰嗦。在语言上比较繁琐以及架构上各种过度设计。

## 好语言好在哪里？坏语言坏在哪里？

太抽象了吧

## 写两个函数，一个是 Referential Transparency 的，一个不是

Referential trasparency 指的是通过函数的参数就可以推断出函数的结果。比如下面两个函数

```
def add(a, b):
    return a + b
```

```
MSG = 'hello '
def greeting(name):
    return MSG + name
```

## 什么是堆，什么是栈，什么是堆栈溢出 Stack Overflow

## 一些语言，尤其是支持函数式编程的语言，推崇一种称作 Pattern Matching 的技术，他和 switch 语句有什么区别吗？

Pattern Matching 相对于 switch 更加灵活，switch 只能使用常量匹配，pm 可以根据类型、值等多种方法匹配

## 为什么一些语言（比如 Go）没有异常呢？这样做的好处和坏处都是什么？

把异常和控制结构混在一起，可能会引起混淆。而且可能会鼓励用户把一些常见的错误也归
类为异常，比如打开文件。

异常本质上是一个不知道会跳到哪里去的 goto。

好处是强迫程序员在编写代码的时候就处理每一个错误，坏处是这样会混淆代码的核心逻辑

ref: https://golang.org/doc/faq#exceptions

## 如果 `Cat` 是一个 `Animal`，那么 TakeCare<Cat> 是一个 `TakeCare<Animal>` 吗？

不是, 模板特例化之后是不同的类

## 为什么在 Java 和 C# 中，构造函数不是接口的一部分呢?

接口定义的是类的行为，而构造函数属于实现细节。如果允许的话，会有如下问题：如果一个类实现了两个接口，该如何调用构造函数呢？

# 数据库

## 你如何迁移应用的数据库，比如从 MySQL 迁移到 postgresql？如果你需要管理这样的项目，你预期会遇到什么问题？

首先，如果这个项目是可以停掉的，那直接停掉，迁移完毕之后验证数据就好了
如果这个项目不能停掉，可以按下面的步骤

1. 更改代码，数据开始双写新旧数据库
2. 更改读取代码，开始灰度读取新数据库数据
3. 把历史数据导入新数据库
4. 灰度下掉老数据库

预期会有数据不一致，性能问题等

## 为什么数据库把 null 当做一个特殊值来处理？比如说 `Select * From table Where Field = null` 不会匹配到含有 null 的行？

因为 null 表示的是没有值，它不和任何值相等

## ACID 是原子性（Atomicity）、一致性（Consistency）、隔离性（Isolation）、持久性（Durability）的缩写，几乎所有的数据库引擎都支持他们，关于这个话题，你了解多少？

一个支持事务（Transaction）的，必需要具有这四种特性，否则在事务过程（Transaction processing）当中无法保证数据的正确性，交易过程极可能达不到交易方的要求。

1. 原子性 整个事务中的所有操作，要么全部完成，要么全部不完成，不可能停滞在中间某个环节。事务在执行过程中发生错误，会被回滚（Rollback）到事务开始前的状态，就像这个事务从来没有执行过一样。

2. 一致性 在事务开始之前和事务结束以后，数据库的完整性约束没有被破坏。具体来说就是，比如表与表之间存在外键约束关系，那么你对数据库进行的修改操作就必需要满足约束条件，即如果你修改了一张表中的数据，那你还需要修改与之存在外键约束关系的其他表中对应的数据，以达到一致性。

3. 隔离性 隔离状态执行事务，使它们好像是系统在给定时间内执行的唯一操作。如果有两个事务，运行在相同的时间内，执行相同的功能，事务的隔离性将确保每一事务在系统中认为只有该事务在使用系统。这种属性有时称为串行化，为了防止事务操作间的混淆，必须串行化或序列化请求，使得在同一时间仅有一个请求用于同一数据。

4. 持久性 在事务完成以后，该事务所对数据库所作的更改便持久的保存在数据库之中，并不会被回滚。 由于一项操作通常会包含许多子操作，而这些子操作可能会因为硬件的损坏或其他因素产生问题，要正确实现ACID并不容易。ACID建议数据库将所有需要更新以及修改的资料一次操作完毕，但实际上并不可行。

目前主要有两种方式实现ACID：第一种是Write ahead logging，也就是日志式的方式。第二种是Shadow paging。

在使用WAL的系统中，所有的修改都先被写入到日志中，然后再被应用到系统状态中。通常包含redo和undo两部分信息。

ref: http://blog.csdn.net/shenwansangz/article/details/47614759
https://www.cnblogs.com/hzmark/p/wal.html

## 如何管理数据库 schema 的变更，当程序一个一个版本迭代的时候，如何自动化地处理数据库 schema 的变更。

导出数据库，确保升级失败后能够重建数据库。把变更动作写成一个脚本，然后提交到仓库中。然后执行升级。

## 懒加载是如何实现的，什么时候有用？有什么坑呢？

```
if (_AllCustomers == null) {
    _AllCustomers = ExpensiveDataCall();
}

return _AllCustomers; // Was: _Customers, not sure if by design.
```

缺点是得到的数据可能是滞后的，以及更新策略的设计

https://softwareengineering.stackexchange.com/questions/278210/is-lazy-loading-always-required

## "N+1 问题" 如何解决？

举个例子，我们数据库中有两张表，一个是Customers，一个是Orders。Orders中含有一个外键customer_id，指向了Customers的主键id。

想要得到所有Customer以及其分别对应的Order，一种写法是 `SELECT * FROM Customers;`
对于每一个Customer: `SELECT * FROM Orders WHERE Orders.customer_id = #{customer.id}`

这样我们实际对数据库做了N+1次查询：选择所有Customer一次得到N个Customer，对于N个Customer分别选择其对应的Order一共N次。
所以，一共执行了N+1次查询，这就是N+1问题

N+1问题的一般解决方法

使用Left Join一次性取出所有数据：`SELECT * FROM Customers LEFT JOIN Orders on Customers.id = Orders.customer_id`。 这样虽然取出的数据相对多一些，但是只需要一次执行

PS：感觉数据库所谓的几个范式优点纸上谈兵，如果完全按照这些范式设计的话，性能就成渣了，互联网公司实际上极少用join。不过产品使用 hive 查询数据倒是经常用 join。

ref: http://kevinsun.logdown.com/posts/1069599

## 如何找出耗费资源最多的查询？

```
SELECT * FROM INFORMATION_SCHEMA.PROCESSLIST where time>10 and command<>"Sleep"
```

或者设置日志

```
[mysqld]

slow-query-log = 1
slow-query-log-file = /var/log/mysql/mysql-slow.log
long_query_time = 5
log-queries-not-using-indexes = 1
```

## 从你来看，是否总要是的数据规范化，什么时候不规范更好？

数据规范化的主要目的是消除冗余信息，但是往往会对性能造成影响。如果性能更重要的话，应该放开规范化。

ref:

1. https://stackoverflow.com/questions/934577/should-i-normalize-my-db-or-not
2. https://stackoverflow.com/questions/1102590/what-exactly-does-database-normalization-do
3. http://www.25hoursaday.com/weblog/2007/08/03/WhenNotToNormalizeYourSQLDatabase.aspx

## 蓝绿部署涉及到数据库的时候会更加复杂，如果处理这种情况呢？

蓝绿部署：https://www.v2ex.com/t/344341


# 关于 NoSQL 的问题

## 什么是 Eventual Consistency？

因为大多数的 NoSQL 数据库都是分布式的，所以很难保证在任何时间都是完全一致的，但是可以保证在一定时间最终一致。

不一致是否可接受取决于客户应用程序。Vogels给出了一个网站的例子，例中真正重要的是“用户感知到的一致性”，也就是让不一致窗口——即“更新发生时刻到任何观察者都一定能观察到更新后数据的时刻之间的时间段”——“小于顾客对下一页面加载时间的期待”，这样更新就可在预期发生下一次读取的时刻之前传播到整个系统。

一致性有不同程度：

强一致性。在更新完成后，（A、B或C进行的）任何后续访问都将返回更新过的值。
弱一致性。系统不保证后续访问将返回更新过的值，在那之前要先满足若干条件。通常条件就是经过一段时间，也就是不一致窗口。
最终一致性。存储系统保证如果对象没有新的更新，最终（在不一致窗口关闭之后）所有访问都将返回最后更新的值。

ref: 
1. https://stackoverflow.com/questions/10078540/eventual-consistency-in-plain-english
2. https://www.zhihu.com/question/20113030

## 解释一下 CAP 理论

一致性 (Consistency)：一个写操作返回成功，那么之后的读请求都必须读到这个新数据；如果返回失败，那么所有读操作都不能读到这个数据。所有节点访问同一份最新的数据。
可用性 (Availability)：对数据更新具备高可用性，请求能够及时处理，不会一直等待，即使出现节点失效。
分区容错性 (Partition tolerance)：能容忍网络分区，在网络断开的情况下，被分隔的节点仍能正常对外提供服务。

理解CAP理论最简单的方式是想象两个副本处于分区两侧，即两个副本之间的网络断开，不能通信。

如果允许其中一个副本更新，则会导致数据不一致，即丧失了C性质。
如果为了保证一致性，将分区某一侧的副本设置为不可用，那么又丧失了A性质。
除非两个副本可以互相通信，才能既保证C又保证A，这又会导致丧失P性质。

CAP 理论并不是简单的三选二，而是至少保证P，然后在CA中二选一。P指的是分区容忍性，也就是网络分区，比如两个数据中心之间的网络断掉的情况如何提供服务的。所以CAP应该理解为当P发生的时候，A和C只能而选一。也就是当发生网络分区的时候，如果我们要继续服务，那么强一致性和可用性只能2选1。

当发生网络分区的时候，在如果要提供服务就可能无法保证强一致性，如果保证一致性，就不一定能提供服务。实际上强一致性不一定是必须的，往往满足了最终一致性就可以了。

ref:

1. https://www.zhihu.com/question/64778723
2. http://www.infoq.com/cn/articles/cap-twelve-years-later-how-the-rules-have-changed
3. http://www.hollischuang.com/archives/666

## 为什么 NoSQL 越来越流行了？

1. 传统的 SQL 数据库需要使用 ORM
2. NoSQL 一般开始设计的时候就考虑了分布式的问题
3. 非结构化的数据越来越多

ref:

1. https://www.quora.com/Why-is-NoSQL-becoming-popular

## NoSQL 如何解决 scalability 的问题？

NoSQL 放弃了 SQL 中提供的原子性等诸多特性，所以非常适合多机实现。

比如说：

* Dropping Atomicity lets you shorten the duration for which tables (sets of data) are locked. Example: MongoDB, CouchDB.
* Dropping Consistency lets you scale up writes across cluster nodes. Examples: riak, cassandra.
* Dropping Durability lets you respond to write commands without flushing to disk. Examples: memcache, redis.

ref:

1. https://softwareengineering.stackexchange.com/questions/194340/why-are-nosql-databases-more-scalable-than-sql

## 在哪种情况下你会使用 MongoDB 这样的文档数据库来代替 MySQL 这种关系型数据库呢？

基本不会采用 MongoDB。文档数据库中的好多特性现在 MySQL 都已经实现了，比如说 JSON Field

# 关于版本管理的问题

## 为什么 git 的分支比 SVN 更简单？

没用过 SVN，但是 SVN 好像是服务端分支，而 Git 在本地分支就可以了

## 像是 Git 这样的分布式版本管理系统相对于中心式的版本管理系统，比如 SVN，有什么优势和劣势？

没用过 SVN

## 能不能描述一下 GitHub Flow 或者 gitflow 的工作模式

有两个分支是长期存在的，master 和 dev，日常开发在dev 分支上，当 dev 分支上的可以
发布新版本之后，可以合并到 master 分支。master 分支上的总是稳定版本

除此之外还有一些临时的分支：

* 功能分支
* 发布分支
* Hotfix 分支

功能分支从 dev 分支上分叉出来，并且最终要合并会 dev 分支，名字可以随便起
发布分支可以从 dev 分支，开发完成后合并到 dev 或者 master 分支（不太理解为什么要有这种分支），名字 `release-*`
Hotfix 分支用于修复 bug，可以从 master 中分叉出去，但是注意要同时合并回 dev 和 master，名字 `hotfix-*`

https://nvie.com/posts/a-successful-git-branching-model/

## 什么是 rebase

顾名思义，就是改变当前 commit 的上一个节点(base node)

## 为什么 git 中的 merge 比 SVN 方便很多？

没用过 SVN

# 关于并发的问题

## 为什么我们需要并发呢？

* 更好地利用多核
* CPU、内存、IO 之间速度有差异，并发可以更好地让速度块的部分不会被速度慢地拖累

## 为什么测试多线程的代码如此之难？

* 多线程代码可能会使用全局变量
* 多线程代码之间的通信

## 什么是竞态条件？举个例子

当两个线程/进程竞争同一资源时，如果对资源的访问顺序敏感，就称存在竞态条件。

```
COUNTER = 1
def add():
    COUNTER = COUNTER + 1
```

ref:

1. http://ifeve.com/race-conditions-and-critical-sections/

## 什么是死锁？举个例子

当两个以上的运算单元，双方都在等待对方停止运行，以获取系统资源，但是没有一方提前退出时，就称为死锁。

## 什么情况下会导致进程饥饿？

进程长时间没有分配到自己所需要的资源

1. 发生死锁
2. 调度算法有问题

## 什么是 wait free 的算法

它保证了每一次调用都可以在有限的步骤内结束。避免出现进程饥饿的情况。

# 分布式系统的问题

## 如何测试一个分布式系统？

ref:

1. http://www.cnblogs.com/yunnotes/archive/2013/04/19/3032290.html
2. https://www.jianshu.com/p/bddfce1494d6

## 什么情况下在两个系统之间使用异步通信？

当被调用的系统花费时间过长的时候，可以让被调用的系统回调来通知处理结果。或者被调
用的系统不关心处理结果。

## RPC 常见的坑有哪些？

比较慢？

## 假设你要构建一个可扩展和健壮的分布式系统。如果你需要在一个封闭安全的系统的系统中构建和在一个地理上隔离的公开环境，有什么区别呢？
## How to manage Fault Tolerance in a Web application? And in a Desktop one?
## 如何处理分布式系统中的错误
## Let's talk about the several approaches to Reconciliation after network partitions
## What are the Fallacies of Distributed Computing?
## 什么时候使用 request/reply，什么时候使用 pubsub？

pubsub 支持多个消费者

## 如果你使用的系统不支持原子性，你怎么实现它？



# 关于软件生命周期和团队管理的问题

## 什么是敏捷?
## How would you deal with Legacy Code?
## Say I'm your Project Manager, and I'm no expert in programming. Would you try explaining me what Legacy Code is and why should I care about code quality?
## I'm the CEO of your company. Explain to me Kanban and convince me to invest in it.
## 敏捷和瀑布式开发有什么区别？
## Being a team manager, how would you deal with the problem of having too many meetings?
## How would you manage a very late project?
## "Individuals and interactions over processes and tools" and "Customer collaboration over contract negotiation" comprise half of the values of the Agile Manifesto. Discuss
## Tell me what decisions would you take if you could be the CTO of your Company.
## 产品经理有用吗？
## Organize a development team using flexible schedules (that is, no imposed working hours) and "Take as you need" vacation policy
## How would you manage a very high turn over and convince developers not to leave the team, without increasing compensation? What could a Company improve to make them stay?
## What are the top 3 qualities you look for in colleagues, beyond their code?
## What are the top 3 things you wish non-technical people knew about code?
## Imagine your company gives you 1 month and some budget to improve your and your colleagues' daily life. What would you do?

# 关于逻辑和算法的问题

## 使用栈来模拟一个队列，然后使用队列来模拟一个栈。
## 写一个会导致堆栈溢出的代码
## 写一个尾递归版本的阶乘计算
## 写一个逆波兰表达式的计算器
## 你会怎样设计“磁盘碎片清理”程序
## 写一个程序构造随机迷宫
## 写一个会产生内存泄漏的程序
## 生成一个随机数序列
## 写一个简单的垃圾回收器
## 写一个简单的消息代理(message broker)
## 写一个简单的 web 服务器，并且把将来要实现的功能画一个路线图
## 如何排序一个 10GB 的文件？如果是 10TB 呢？
## 如何检测文件重复？

# 关于软件架构的问题

## 什么时候缓存没有用而且可能很危险？
## 为什么事件驱动的架构能够提高可扩展性
## 如何让代码更可读?
## What is the difference between emergent design and evolutionary architecture?
## Scale out vs scale up: how are they different? When to apply one, when the other?
## How to deal with failover and user sessions?
## What is CQRS (Command Query Responsibility Segregation)? How is it different from the oldest Command-Query Separation Principle?
## The so called "multitier architecture" is an approach to design a client–server system aimed to keep physically and logically separated presentation, application processing, data management and other functions. The most widespread of the multitier architectures is the three-tier architecture. Would you discuss the pros and cons of such approach?
## How would you design a software system for scalability?
## Someone gave the name "The "C10k problem" to the problem of optimising network sockets to handle over 10.000 open connections at once. While handling 10.000 concurrent clients is not the same as handling 10.000 open connection, the context is similar. It's a tough challenge anyway, and no one is expected to know every single detail to solve it. It may be interesting to discuss the strategies you know to deal with that problem. Would you like to try?
## How would you design a decentralized (that is, with no central server) P2P system?
## 为什么 CGI 不流行了？

CGI 每个请求就要新建一个进程，而进程的创建开销是很大的。

## 如何防止你的系统陷入供应商锁定（vendor lockin）？

在第三方 API 上再抽象一层，避免直接依赖对方代码或者 API。尽量使用开源软件，实在
不行还可以自己改。

## PubSub 模型在规模变大的时候会有那些问题？

PubSub 本质上是一个多生产者多消费者的队列。当消息量大的时候，如果没有很好地缓冲
机制，很可能造成缓冲溢出导致丢消息。另外这种模式也没有定义很好地持久化机制。

## What's new in CPUs since the 80s, and how does it affect programming?
## 在软件声明周期的哪个部分应该考虑性能？怎么做？
## How could a Denial of Service arise not maliciously but for a design or architectural problem?
## 性能和可靠性之间的关系是怎样的？
## When is it OK (if ever) to use tight coupling?
## What characteristic should a system have to be Cloud Ready?
## Does unity of design imply an aristocracy of architects? Putting it simple: can good design emerge from a collective effort of all developers?
## What's the difference between design, architecture, functionality and aesthetic? Discuss.

# 关于面向服务的架构和微服务

## 在面向服务的架构中，为什么长时间的事务是不被鼓励的，而建议使用 saga 模式呢？
## SOA 和 微服务之间的区别是？
## 来谈谈 web services 的版本管理、版本兼容性和破坏性变更
## Let's talk about web services versioning, version compatibility and breaking changes.
## What's the difference between a transaction and a compensation operation in a saga, in SOA?
## 什么时候你会觉得微服务太“微”了
## 微服务架构的优缺点


# 关于安全的问题

## 如何写出安全的代码？

## 为什么说不要自己去发明一套加密系统？

https://security.stackexchange.com/questions/18197/why-shouldnt-we-roll-our-own

## 什么是两步验证，如何实现？

除了密码之外，再使用额外的设备提供一个密码，比如 OTG 或者硬件密码等。

## 如果不小心处理的话，很可能日志中会包含很多的敏感数据，如何处理呢？(twitter 和 GitHub 都犯了这个错误)

只在开发环境记录敏感日志，在线上要关闭这些日志

ref:

1. https://systemoverlord.com/2018/05/03/how-the-twitter-and-github-password-logging-issues-could-happen.html

## 写一个会受到 SQL 注入影响的代码，然后修复它

```
# 如果 user_id = '1; drop table users;'
cursor.execute('select * from users where id = %s', % (user_id))
```

## 如何通过静态代码检查消除 SQL 注入的隐患？

## 什么是 XSS，如何阻止？

如果完全信任用户的输入，用户可能输入 `<script>` 的标签的形式注入自己的脚本。更严
重的是，如果 cookies 没有设置成 http only 的，那么用户的 cookies 很可能也被偷取。

ref:

1. https://www.cnblogs.com/dolphinX/p/3391351.html

## 什么是 CSRF，如何阻止？

CSRF攻击是源于WEB的隐式身份验证机制！WEB的身份验证机制虽然可以保证一个请求是来自于某个用户的浏览器，但却无法保证该请求是用户批准发送的！

浏览器在请求每个域名的时候会带上对应的 cookies，可以通过 img 标签的 src 等伪造
GET 请求，或者通过 js 来伪造表单提交的 POST 请求，这样就相当于代替用户请求了服务
器。

可以通过在页面上增加一个隐藏的 crsf_token 来，然后每次请求都校验这个 token 是不是合法。

ref:

1. http://www.cnblogs.com/hyddd/archive/2009/04/09/1432744.html

## https 是如何工作的?


## 什么是中间人攻击？为什么 https 可以避免中间人攻击？

在 http 等明文协议中，中间人（代理服务器、路由器）等等可以偷听、篡改数据包，而通
信双方都无法察觉。

https 通过密钥通信，而密钥只有通信双方知道，也就无法查看或者篡改数据包。

## 如何避免用户的 session 被窃取？

可以使用 https

ref:

1. https://stackoverflow.com/questions/22880/what-is-the-best-way-to-prevent-session-hijacking

# 通用问题

## 为什么函数式编程很重要呢？什么时候应该使用函数式语言?

函数是编程的每一个函数都是可验证的，可以证明程序是正确的。因为函数都没有副作用，
所以也天然适合并发。

## 微软、谷歌、Mozilla、搜狗、360这样的公司都怎么靠他们的浏览器挣钱呢？

谷歌通过广告挣钱，通过 Chrome，谷歌可以成为默认的搜索引擎，其他家也都类似

## 为什么打开一个 TCP socket 有很大的开销呢？

打开一个新的 tcp 链接需要三次握手，也就是 3xRTT 的时间，相比于复用一个已经打开的
链接的成本几乎为零。

ref:

1. https://serverfault.com/questions/418393/why-is-creating-a-new-tcp-connection-regarded-as-expensive

## 封装对什么很重要呢？
## 什么是实时系统，它和普通系统有什么区别呢？
## 实时系统和堆内存分配的关系？

没查到相关资料

## 不可变的值为什么有助于代码的安全性？

不可变对象在并发应用种特别有用。因为他们不能改变状态，它们不能被线程干扰所中断或者被其他线程观察到内部不一致的状态。

不可变对象没有副作用、更容易缓存、也不会产生 null 引用。

ref:

1. http://www.importnew.com/14027.html

## 使用可变和不可变值都有什么利弊?

使用不可变值每次都需要创建一个新的对象，可能开销很大。

## 对象(OOP)和关系(SQL)之间的不匹配指的是？

比如说有两种对象：

1. book
2. author

每个人可能有很多本书，每本书也可能有好几个作者，所以数据库中就需要建三个表，
`book`, `author`, `book_author_ref`, 而一些 ORM 则帮助做了这些映射。

## 如何确定缓存的大小？

创建一个连续内存块，进行连贯、大量、随机的有意义内存访问。这几点缺一不可，否则不能保证整块内存被
尽可能的放入Cache。在这种情况下，当内存块能够被整块放入Cache时，平均访问速度会显著的快。观察随
着内存大小提高，平均访问时间的跃升点，即可估计Cache大小。

ref:

1. https://www.zhihu.com/question/30563694

## TCP 和 HTTP 之间有什么区别？

tcp 是第四层的协议，是面向字节流的。而 http 是 第七层的协议，基于 tcp，但是是面
向报文的。

## 客户端渲染和服务端渲染各有什么优缺点？

客户端渲染减轻服务器负担，可以把页面逻辑写在js中，不需要总是重载页面。但是不利于
SEO，同时可能造成白屏现象。

## 如何基于不可靠的链接建立一个可靠地链接？

可以参考 TCP，IP 协议就是一个不可靠的协议，但是基于 IP 的 TCP 协议是可靠的。

TCP 有编号确认机制，还可以重发。

## Imagine you want to remove the possibility to have null references in your preferred language: how would you achieve this goal? What consequences could this have?


# 开放问题

## 为什么人们抵制变化？
## 向你的爷爷奶奶解释下什么是线程？
## As a software engineer you want both to innovate and to be predictable. How those 2 goals can coexist in the same strategy?
## 好代码好在哪里？
## Explain streaming and how you would implement it.
## Say your Company gives you one week you can use to improve your and your colleagues' lifes: how would you use that week?
## What did you learn this week?
## There is an aesthetic element to all design. The question is, is this aesthetic element your friend or your enemy?
## 你最近读了哪五本书？
## How would you introduce Continuous Delivery in a successful, huge company for which the change from Waterfall to Continuous Delivery would be not trivial, because of the size and complexity of the business?
## When does it make sense to reinvent the wheel?
## Let's have a conversation about "Reinventing the wheel", the "Not Invented Here Syndrome" and the "Eating Your Own Food" practice
## What's the next thing you would automate in your current workflow?
## Why is writing software difficult? What makes maintaining software hard?
## Would you prefer working on Green Field or Brown Field projects? Why?
## What happens when you type google.com into your browser and press enter?
## What does an Operating System do when it has got no custom code to run, and therefore it looks idle? I would like to start a discussions about interrupts, daemons, background services, polling, event handling and so on.
## 向一个五岁的孩子解释 Unicode 和数据库事物。
## Defend the monolithic architecture.
## What does it mean to be a "Professional Developer"?
## Is developing software an art, a craftsmanship or an engineering endeavour? Your opinion.
## "喜欢这个的顾客也喜欢XXX". 你怎样实现这个功能？

协同过滤

## Why are corporations slower than startups in innovating?
## What have you achieved recently that you are proud of?


# 关于代码片段的问答

## 下面这段 JS 的输出结果是什么？

```
function hookupevents() {
  for (var i = 0; i < 3; i++) {
    document.getElementById("button" + i)
      .addEventListener("click", function() {
        alert(i);
      });
  }
}
```

回答：

每一个元素点击都会提示 3，因为闭包捕获了 i，最终结果是 3

## 关于类型擦除，下面这段 Java 代码的输出是什么？

```
ArrayList<Integer> li = new ArrayList<Integer>();
ArrayList<Float> lf = new ArrayList<Float>();
if (li.getClass() == lf.getClass()) // evaluates to true
    System.out.println("Equal");
```

Java 中的泛型并没有把每个不同的模板参数特例化成不同的类，而是简单地把类型抹掉了。

## 你能找到内存泄露吗？

```
public class Stack {
    private Object[] elements;
    private int size = 0;
    private static final int DEFAULT_INITIAL_CAPACITY = 16;

    public Stack() {
        elements = new Object[DEFAULT_INITIAL_CAPACITY];
    }

    public void push(Object e) {
        ensureCapacity();
        elements[size++] = e;
    }

    public Object pop() {
        if (size == 0)
            throw new EmptyStackException();
        return elements[--size];
    }

    /**
     * Ensure space for at least one more element, roughly
     * doubling the capacity each time the array needs to grow.
     */
    private void ensureCapacity() {
        if (elements.length == size)
            elements = Arrays.copyOf(elements, 2 * size + 1);
    }
}
```

pop 的时候没有缩小占用空间，而且也没有析构函数

## if 和其他的条件语句会导致过程化的代码，请重构下面的代码，去掉 switch 语句，并且变得更加面向对象

```
public class Formatter {

    private Service service;

    public Formatter(Service service) {
        this.service = service;
    }

    public String doTheJob(String theInput) {
        String response = service.askForPermission();
        switch (response) {
        case "FAIL":
            return "error";
        case "OK":
            return String.format("%s%s", theInput, theInput);
        default:
            return null;
        }
    }
    }
```

重构:

```
public class Formatter {

}
```

## 去掉 if 并让下面的代码更加面向对象

```
public class TheService {
    private final FileHandler fileHandler;
    private final FooRepository fooRepository;

    public TheService(FileHandler fileHandler, FooRepository fooRepository) {
        this.fileHandler = fileHandler;
        this.fooRepository = fooRepository;
    }

    public String Execute(final String file) {

        final String rewrittenUrl = fileHandler.getXmlFileFromFileName(file);
        final String executionId = fileHandler.getExecutionIdFromFileName(file);

        if (executionId.equals("") || rewrittenUrl.equals("")) {
            return "";
        }

        Foo knownFoo = fooRepository.getFooByXmlFileName(rewrittenUrl);

        if (knownFoo == null) {
            return "";
        }

        return knownFoo.DoThat(file);
    }
    }
```

## 如何重构下面的代码

```
function()
{
    HRESULT error = S_OK;

    if(SUCCEEDED(Operation1()))
    {
        if(SUCCEEDED(Operation2()))
        {
            if(SUCCEEDED(Operation3()))
            {
                if(SUCCEEDED(Operation4()))
                {
                }
                else
                {
                    error = OPERATION4FAILED;
                }
            }
            else
            {
                error = OPERATION3FAILED;
            }
        }
        else
        {
            error = OPERATION2FAILED;
        }
    }
    else
    {
        error = OPERATION1FAILED;
    }

    return error;
}
```

这是典型的箭头形函数，可以参见酷壳的这篇文章：https://coolshell.cn/articles/17757.html


# Bill Gates 式的问题

This section collects some weird questions along the lines of the Manhole Cover Question.

## 如果你把一个镜子放到扫描仪中会发生什么？
## 如果有一个你的克隆人来做你的老板，你愿意为他工作吗？
## 面试我
## 为什么知乎上的答案比百度知道上要好？
## 为 Cobol 是一个现代的语言辩护
## 十年后你想变成怎样？
## 你是我的老板，然后把我炒了鱿鱼，通知我
## 我想重构一个系统，你想从头重写，和我讨论一下，然后我们互换角色。
## 你的上司让你对公司说谎，你会怎么办？
## 如果你可以穿越回过去，你会给自己什么建议？
