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
    value_type & value() noexcept
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
    node_pointer & forward(level_type _Level) noexcept
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
        node_pointer _Cur = _Head->forward(0);

        while (_Cur != nullptr) {
            node_pointer _Next = _Cur->forward(0);
            _Destroy_node(_Cur);
            _Cur = _Next;
        }

        for (level_type _Level = 0; _Level <= _Current_level_index; ++_Level) {
            _Head->forward(_Level) = nullptr;
        }

        _Current_level_index = 0;
        _Size = 0;
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
        // 使用一个数组来储存前一个结点的向前指针，为了避免越界，直接初始化大小为最大大小
        std::vector<node_pointer> _Update_list(_Max_level_index + 1, nullptr);

        // 从头节点开始向下寻找
        node_pointer _Cur = _Head;

        // 从最高层开始查找
        for (level_type _Level = _Current_level_index; _Level >= 0; --_Level) {
            while (_Cur->forward(_Level) != nullptr && _Cur->forward(_Level)->key() < _Pair.first) {
                _Cur = _Cur->forward(_Level);
            }

            // 记录该节点，后续可能需要修改
            _Update_list[_Level] = _Cur;
        }

        // 移动到0层，向后移动一个
        _Cur = _Cur->forward(0);

        // 判断是否已经存在
        if (_Cur != nullptr && _Cur->key() == _Pair.first) {
            return false;
        }

        // 不存在，创建新节点
        level_type _New_level_index = _Random_level() - 1;
        node_pointer _New_node = _Create_node(_Pair, _New_level_index);

        // 如果新节点层级大于当前最高层级，将多出来的这些层级加入更新列表中
        if (_New_level_index > _Current_level_index) {
            for (level_type _Level = _Current_level_index + 1; _Level <= _New_level_index; ++_Level) {
                // 由于跳表的开头必须是头节点，所以多出来的高度的前置都指向头节点即可
                _Update_list[_Level] = _Head;
            }

            // 更新最高层级
            _Current_level_index = _New_level_index;
        }

        // 开始遍历各层的前置节点并修改
        for (level_type _Level = 0; _Level <= _New_level_index; ++_Level) {
            // 将原来的指针添加到新节点中
            _New_node->forward(_Level) = _Update_list[_Level]->forward(_Level);
            // 将新节点添加到前置节点的向前列表中
            _Update_list[_Level]->forward(_Level) = _New_node;
        }

        ++_Size;

        return true;
    }

    /**
     * @brief 删除一个键值对
     * @param _Key 键
     * @return 是否删除成功
     */
    bool erase(const key_type & _Key) noexcept
    {
        // 存储每层中指向待删除节点的前驱
        std::vector<node_pointer> _Update_list(_Max_level_index + 1, nullptr);

        node_pointer _Cur = _Head;

        // 从顶层向下查找，记录每一层的前驱
        for (level_type _Level = _Current_level_index; _Level >= 0; --_Level) {
            while (_Cur->forward(_Level) != nullptr && _Cur->forward(_Level)->key() < _Key) {
                _Cur = _Cur->forward(_Level);
            }

            _Update_list[_Level] = _Cur;
        }

        // 到达第0层，检查是否匹配
        _Cur = _Cur->forward(0);

        if (_Cur == nullptr || _Cur->key() != _Key) {
            // 不存在这个节点，删除失败
            return false;
        }

        // 开始删除节点
        for (level_type _Level = 0; _Level <= _Current_level_index; ++_Level) {
            if (_Update_list[_Level]->forward(_Level) != _Cur) {
                // 从这里开始上层都没有该键值对了
                break;
            }

            // 是该键值对，删除
            _Update_list[_Level]->forward(_Level) = _Cur->forward(_Level);
        }

        // 删除节点
        _Destroy_node(_Cur);

        // 检查是否需要降低跳表的高度
        while (_Current_level_index > 0 && _Head->forward(_Current_level_index) == nullptr) {
            --_Current_level_index;
        }

        --_Size;

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
