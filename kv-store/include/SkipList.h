#pragma once

#include <cstdlib>
#include <cstddef>
#include <utility>
#include <vector>

#include <Common.h>

namespace WW
{

/**
 * @brief 跳表节点
 * @tparam _Key 键类型
 * @tparam _Value 值类型
 */
template <
    typename _Ty_key,
    typename _Ty_value
> class SkipListNode
{
public:
    using key_type = _Ty_key;
    using value_type = _Ty_value;
    using pair_type = std::pair<const _Ty_key, _Ty_value>;
    using level_type = int;
    using node_pointer = SkipListNode<_Ty_key, _Ty_value> *;

private:
    key_type _Key;                          // 键
    value_type _Value;                      // 值
    std::vector<node_pointer> _Forward;     // 向前数组

public:
    SkipListNode()
        : SkipListNode(pair_type(), 0)
    {
    }

    explicit SkipListNode(level_type _Level)
        : SkipListNode(pair_type(), _Level)
    {
    }

    SkipListNode(const pair_type & _Pair, level_type _Level)
        : _Key(_Pair.first)
        , _Value(_Pair.second)
        , _Forward(_Level + 1, nullptr)
    {
    }

    ~SkipListNode() = default;

public:
    /**
     * @brief 获取键
     * @return 键
     */
    const key_type & key() const noexcept
    {
        return _Key;
    }

    /**
     * @brief 获取值
     * @return 值
     */
    const value_type & value() const noexcept
    {
        return _Value;
    }

    /**
     * @brief 获取层级
     * @return 层级
     * @exception 若`std::vector::size()`允许抛出异常，则允许抛出异常
     */
    const level_type level() const noexcept
    {
        return _Forward.size() - 1;
    }

    /**
     * @brief 获取该节点在指定层级的向前节点
     * @param _Level 层级
     * @return 节点指针
     */
    const node_pointer & forward(level_type _Level) const noexcept
    {
        return _Forward[_Level];
    }

    /**
     * @brief 设置值
     * @param value 值
     */
    void set_value(const value_type & value) noexcept
    {
        _Value = value;
    }
};

/**
 * @brief 跳表
 * @tparam _Key 键类型
 * @tparam _Value 值类型
 */
template <
    typename _Ty_key,
    typename _Ty_value
> class SkipList
{
public:
    using key_type = _Ty_key;
    using value_type = _Ty_value;
    using pair_type = std::pair<const _Ty_key, _Ty_value>;
    using size_type = std::size_t;
    using level_type = int;
    using node_type = SkipListNode<key_type, value_type>;
    using node_pointer = SkipListNode<key_type, value_type> *;

private:
    node_pointer _Head;                 // 头节点
    level_type _Max_level_index;        // 最大层级索引
    level_type _Current_level_index;    // 当前最高层级索引
    size_type _Size;                    // 节点个数

public:
    SkipList()
        : SkipList(MAX_LEVEL)
    {
    }

    explicit SkipList(level_type _Max_level)
        : _Head(_Create_node(_Max_level - 1))
        , _Max_level_index(_Max_level - 1)
        , _Current_level_index(0)
        , _Size(0)
    {
    }

    ~SkipList()
    {
        // 删除所有节点
        clear();

        // 删除头节点
        _Destroy_node(_Head);
    }

public:
    /**
     * @brief 清空跳表
     */
    void clear() noexcept
    {
        // TODO
    }

    /**
     * @brief 获取跳表大小
     * @return 跳表大小
     */
    size_type size() const noexcept
    {
        return _Size;
    }

    /**
     * @brief 判断跳表是否为空
     * @return 是否为空
     */
    bool empty() const noexcept
    {
        return _Size == 0;
    }

    /**
     * @brief 查询一个键是否存在
     * @param _Key 键
     * @return 是否存在
     */
    bool contains(const key_type & _Key) const noexcept
    {
        node_pointer _Node_ptr = _Find(_Key);
        return _Node_ptr != nullptr;
    }

    /**
     * @brief 当不存在键时，插入一个键值对
     * @param _Pair 键值对
     * @return 是否插入成功
     */
    bool insert(const pair_type & _Pair) noexcept
    {
        // TODO
        return true;
    }

    /**
     * @brief 删除一个键值对
     * @param _Key 键
     * @return 是否删除成功
     */
    bool erase(const key_type & _Key) noexcept
    {
        // TODO
        return true;
    }

private:
    /**
     * @brief 随机生成一个层级
     * @return 层级
     */
    level_type _Random_level() const noexcept
    {
        level_type _Level = 1;

        while (rand() % 2 && _Level < _Max_level_index) {
            ++_Level;
        }

        return _Level;
    }

    /**
     * @brief 创建一个空节点
     * @return 节点指针
     */
    node_pointer _Create_node() const noexcept
    {
        return new node_type();
    }

    /**
     * @brief 创建一个指定层级的空节点
     * @param _Level 层级
     * @return 节点指针
     */
    node_pointer _Create_node(level_type _Level) const noexcept
    {
        return new node_type(_Level);
    }

    /**
     * @brief 创建一个节点
     * @param _Pair 键值对
     * @param _Level 层级
     * @return 节点指针
     */
    node_pointer _Create_node(const pair_type & _Pair, level_type _Level) const noexcept
    {
        return new node_type(_Pair, _Level);
    }

    /**
     * @brief 销毁一个节点
     * @param _Node 节点指针
     */
    void _Destroy_node(node_pointer _Node) const noexcept
    {
        delete _Node;
    }

    /**
     * @brief 查找一个节点
     * @param _Key 键
     * @return 节点指针
     */
    node_pointer _Find(const key_type & _Key) const noexcept
    {
        // 从头节点开始查找
        node_pointer _Cur = _Head;

        // 从当前最高层级开始查找
        for (level_type _Level = _Current_level_index; _Level >= 0; --_Level) {
            // 在当前层级中前进，直到找到大于等于_key的节点
            while (_Cur->forward(_Level) != nullptr && _Cur->forward(_Level)->key() < _Key) {
                _Cur = _Cur->forward(_Level);
            }
        }
        
        // 到达0层，向后移动一个就是最终找到的节点
        _Cur = _Cur->forward(0);

        // 判断该节点是不是目标节点
        if (_Cur != nullptr && _Cur->key() == _Key) {
            return _Cur;
        }

        return nullptr;
    }
};

} // namespace WW
