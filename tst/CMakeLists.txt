# Asegúrate de que Google Test esté disponible
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Add the executable for tests
add_executable(RunTests test_main.cpp
        NodeTest.cpp
        ListTest.cpp
        QueueTest.cpp
        PageTest.cpp
        IPAddressTest.cpp
        TerminalTest.cpp
        PacketTest.cpp
        RouterTest.cpp
        NetworkTest.cpp
        AdjNodeTest.cpp
        AdjacencyListTest.cpp)

# Link the Google Test libraries
target_link_libraries(RunTests gtest gtest_main AyEdD_Routers_ObjLib)

# Specify include directories for the tests
target_include_directories(RunTests PRIVATE ../include)