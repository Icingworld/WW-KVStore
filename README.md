# WW-KVStore

这是`WW`系列中，关于`KV存储`的简易实现，使用跳表`Skiplist`作为底层数据结构。

## 一、特点

+ 将跳表设计为`STL`风格的容器，支持`STL`关联型容器相同的操作
+ 注释详细，可读性强

## 二、使用

### 1. 引入库

下载项目文件并储存至合适位置，然后在可执行文件中链接库`WW::kvstore`

+ 示例

```cmake
target_link_libraries(YOUR_EXCUTABLE_NAME PRIVATE WW::kvstore)
```

### 2. 使用跳表

示例代码位于[skiplist_test.cpp](test/skiplist_test.cpp)

```cpp
#include <string>
#include <iostream>

#include <SkipList.h>

int main()
{
    WW::_Skiplist<std::string, std::string> _Skiplist;

    // 插入
    auto pair = _Skiplist.insert({"a", "b"});

    // 访问
    std::string value = _Skiplist.at("a");

    // 访问 & 修改
    _Skiplist["a"] = "c";

    // 删除
    _Skiplist.erase("a");

    // 迭代器
    for (auto it = _Skiplist.begin(); it != _Skiplist.end(); ++it) {
        std::cout << it->first << " " << it->second << std::endl;
    }

    return 0;
}
```

### 3. 使用KVStore

`KVStore`是一个简单的对跳表的封装，示例代码位于[kvstore_test.cpp](test/kvstore_test.cpp)

```cpp
#include <string>

#include <KVStore.h>

int main()
{
    WW::KVStore<std::string, std::string> store;

    // put
    store.put("name", "Alice");

    // get
    std::string name = store.get("name");

    // update
    store.update("name", "Bob");

    // remove
    store.remove("name");

    // contains
    std::cout << store.contains("name") << std::endl;

    // size
    std::cout << store.size() << std::endl;

    // empty
    std::cout << store.empty() << std::endl;

    return 0;
}
```

## 三、计划

后续将对`SkipList`和`KVStore`进行优化和扩展，使得该`KV存储`成为相对完备的内存型数据库。
