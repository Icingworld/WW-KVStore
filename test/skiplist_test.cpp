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
    EXPECT_EQ(pair.first, _Skiplist.end());
    EXPECT_FALSE(pair.second);
    EXPECT_EQ(_Skiplist.size(), 3);
}