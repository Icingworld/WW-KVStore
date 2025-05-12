#pragma once

#include <vector>

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
    using level_type = unsigned int;
    using node_pointer = SkipListNode *;

private:
    key_type _Key;                          // 键
    value_type _Value;                      // 值
    std::vector<node_pointer> _Forward;     // 向前数组

public:
    SkipListNode()
        : SkipListNode(key_type(), value_type(), 0)
    {
    }

    SkipListNode(const key_type & key, const value_type & value, level_type level)
        : _Key(key), _Value(value), _Forward(level, nullptr)
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
     * @brief 获取等级
     * @return 等级
     * @exception 若`std::vector::size()`允许抛出异常，则允许抛出异常
     */
    const level_type level() const noexcept
    {
        return _Forward.size();
    }

    const node_pointer & forward(level_type level) const noexcept
    {
        return _Forward[level];
    }

    void set_value(const value_type & value) noexcept
    {
        _Value = value;
    }
};

} // namespace WW
