#include <string>

#include <gtest/gtest.h>
#include <KVStore.h>

class KVStoreTest : public testing::Test
{
protected:
    WW::KVStore<std::string, std::string> store;
};

TEST_F(KVStoreTest, PutAndGet)
{
    // 插入新键值对
    EXPECT_TRUE(store.put("name", "Alice"));
    EXPECT_TRUE(store.put("city", "NYC"));

    // 重复插入相同 key 应该失败
    EXPECT_FALSE(store.put("name", "Bob"));

    // 获取值
    EXPECT_EQ(store.get("name"), "Alice");
    EXPECT_EQ(store.get("city"), "NYC");

    // 获取不存在的值返回默认值
    EXPECT_EQ(store.get("unknown"), "");
}

TEST_F(KVStoreTest, Update)
{
    store.put("name", "Alice");
    EXPECT_TRUE(store.update("name", "Bob"));
    EXPECT_EQ(store.get("name"), "Bob");
}

TEST_F(KVStoreTest, Remove)
{
    store.put("name", "Alice");
    store.put("city", "NYC");

    // 删除存在的键
    EXPECT_TRUE(store.remove("name"));
    EXPECT_FALSE(store.contains("name"));
    EXPECT_EQ(store.size(), 1);

    // 删除不存在的键
    EXPECT_FALSE(store.remove("unknown"));
    EXPECT_EQ(store.size(), 1);
}

TEST_F(KVStoreTest, Contains)
{
    store.put("x", "1");
    store.put("y", "2");

    EXPECT_TRUE(store.contains("x"));
    EXPECT_TRUE(store.contains("y"));
    EXPECT_FALSE(store.contains("z"));
}

TEST_F(KVStoreTest, SizeAndEmpty)
{
    EXPECT_TRUE(store.empty());
    EXPECT_EQ(store.size(), 0);

    store.put("a", "b");
    EXPECT_FALSE(store.empty());
    EXPECT_EQ(store.size(), 1);

    store.remove("a");
    EXPECT_TRUE(store.empty());
    EXPECT_EQ(store.size(), 0);
}
