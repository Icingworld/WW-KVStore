#include <string>

#include <gtest/gtest.h>
#include <SkipList.h>

class SkipListTest : public testing::Test {
public:
    WW::_Skiplist<std::string, std::string> _Skiplist;
};

TEST_F(SkipListTest, Insert)
{
    auto pair = _Skiplist.insert({"a", "b"});
    EXPECT_EQ(pair.first->first, "a");
    EXPECT_EQ(pair.first->second, "b");
    EXPECT_TRUE(pair.second);
    EXPECT_EQ(_Skiplist.size(), 1);
    pair = _Skiplist.insert({"c", "d"});
    EXPECT_EQ(pair.first->first, "c");
    EXPECT_EQ(pair.first->second, "d");
    EXPECT_TRUE(pair.second);
    EXPECT_EQ(_Skiplist.size(), 2);
    pair = _Skiplist.insert({"e", "f"});
    EXPECT_EQ(pair.first->first, "e");
    EXPECT_EQ(pair.first->second, "f");
    EXPECT_TRUE(pair.second);
    EXPECT_EQ(_Skiplist.size(), 3);

    pair = _Skiplist.insert({"a", "g"});
    EXPECT_EQ(pair.first->first, "a");
    EXPECT_EQ(pair.first->second, "b");
    EXPECT_FALSE(pair.second);
    EXPECT_EQ(_Skiplist.size(), 3);
}

TEST_F(SkipListTest, Access)
{
    _Skiplist.insert({"a", "b"});
    _Skiplist.insert({"c", "d"});
    _Skiplist.insert({"e", "f"});

    // at
    EXPECT_EQ(_Skiplist.at("a"), "b");
    EXPECT_EQ(_Skiplist.at("c"), "d");
    EXPECT_EQ(_Skiplist.at("e"), "f");
    EXPECT_THROW(_Skiplist.at("g"), std::out_of_range);

    // operator[]
    EXPECT_EQ(_Skiplist["a"], "b");
    EXPECT_EQ(_Skiplist["c"], "d");
    EXPECT_EQ(_Skiplist["e"], "f");
    _Skiplist["a"] = "g";
    EXPECT_EQ(_Skiplist["a"], "g");
    _Skiplist["h"] = "i";
    EXPECT_EQ(_Skiplist["h"], "i");
}

TEST_F(SkipListTest, Iterator)
{
    _Skiplist.insert({"a", "b"});
    _Skiplist.insert({"c", "d"});
    _Skiplist.insert({"e", "f"});
    auto it = _Skiplist.begin();
    EXPECT_EQ(it->first, "a");
    EXPECT_EQ(it->second, "b");
    ++it;
    EXPECT_EQ(it->first, "c");
    EXPECT_EQ(it->second, "d");
    ++it;
    EXPECT_EQ(it->first, "e");
    EXPECT_EQ(it->second, "f");
    ++it;
    EXPECT_EQ(it, _Skiplist.end());
}

TEST_F(SkipListTest, Erase)
{
    _Skiplist.insert({"a", "b"});
    _Skiplist.insert({"c", "d"});
    _Skiplist.insert({"e", "f"});

    // erase(1)
    auto it = _Skiplist.begin();
    ++it;
    it = _Skiplist.erase(it);
    EXPECT_EQ(it->first, "e");
    EXPECT_EQ(it->second, "f");
    EXPECT_EQ(_Skiplist.size(), 2);

    // erase(2)
    auto count = _Skiplist.erase("e");
    EXPECT_EQ(count, 1);
    EXPECT_EQ(_Skiplist.size(), 1);

    count = _Skiplist.erase("g");
    EXPECT_EQ(count, 0);
    EXPECT_EQ(_Skiplist.size(), 1);
}

TEST_F(SkipListTest, Clear)
{
    _Skiplist.insert({"a", "b"});
    _Skiplist.insert({"c", "d"});
    _Skiplist.insert({"e", "f"});
    _Skiplist.clear();
    EXPECT_EQ(_Skiplist.size(), 0);
    EXPECT_TRUE(_Skiplist.empty());

    _Skiplist.insert({"a", "b"});
    _Skiplist.insert({"c", "d"});
    _Skiplist.insert({"e", "f"});
    EXPECT_EQ(_Skiplist.size(), 3);
    EXPECT_FALSE(_Skiplist.empty());
}

TEST_F(SkipListTest, FindAndContains)
{
    _Skiplist.insert({"a", "b"});
    _Skiplist.insert({"c", "d"});
    _Skiplist.insert({"e", "f"});
    auto it = _Skiplist.find("a");
    EXPECT_EQ(it->first, "a");
    EXPECT_EQ(it->second, "b");
    it = _Skiplist.find("g");
    EXPECT_EQ(it, _Skiplist.end());
    EXPECT_TRUE(_Skiplist.contains("a"));
    EXPECT_TRUE(_Skiplist.contains("c"));
    EXPECT_TRUE(_Skiplist.contains("e"));
    EXPECT_FALSE(_Skiplist.contains("g"));
}