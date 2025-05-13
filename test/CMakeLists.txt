# kvstore_test
# add_executable(kvstore_test kvstore_test.cpp)

# target_link_libraries(kvstore_test PRIVATE
#     WW::kvstore
#     GTest::gtest
#     GTest::gtest_main
# )

# skiplist_test
add_executable(skiplist_test skiplist_test.cpp)

target_link_libraries(skiplist_test PRIVATE
    WW::kvstore
    GTest::gtest
    GTest::gtest_main
)