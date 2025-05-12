#include <string>

#include <gtest/gtest.h>
#include <SkipList.h>

TEST(SkipListTest, BasicInsert)
{
    WW::SkipList<int, std::string> sl;
    EXPECT_TRUE(sl.insert({1, "one"}));
    EXPECT_TRUE(sl.insert({2, "two"}));
    EXPECT_FALSE(sl.insert({1, "duplicate"}));  // 重复插入
    EXPECT_EQ(sl.size(), 2);
}

TEST(SkipListTest, EraseTest)
{
    WW::SkipList<int, std::string> sl;
    sl.insert({10, "ten"});
    sl.insert({20, "twenty"});
    EXPECT_TRUE(sl.erase(10));
    EXPECT_FALSE(sl.erase(10));  // 再次删除应失败
    EXPECT_EQ(sl.size(), 1);
}

TEST(SkipListTest, ClearTest)
{
    WW::SkipList<int, std::string> sl;
    sl.insert({1, "a"});
    sl.insert({2, "b"});
    sl.insert({3, "c"});
    sl.clear();
    EXPECT_EQ(sl.size(), 0);
    EXPECT_TRUE(sl.insert({4, "d"}));  // 插入新节点仍然可用
}

TEST(SkipListTest, FindBehavior)
{
    WW::SkipList<int, std::string> sl;
    sl.insert({5, "five"});
    sl.insert({6, "six"});
    EXPECT_TRUE(sl.contains(5));
    EXPECT_FALSE(sl.contains(100));
}