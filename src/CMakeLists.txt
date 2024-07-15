# Create an OBJECT library
add_library(AyEdD_Routers_ObjLib OBJECT
        Terminal.cpp
    Router.cpp
    Admin.cpp
        Page.cpp
    Packet.cpp
        IPAddress.cpp
        Network.cpp
        AdjacencyList.cpp
        AdjNode.cpp
)

# Specify include directories for the OBJECT library
target_include_directories(AyEdD_Routers_ObjLib PUBLIC ../include)

# Create the executable using the OBJECT library
add_executable(AyEdD_Routers $<TARGET_OBJECTS:AyEdD_Routers_ObjLib>
        ../include/IPAddress.hpp
        ../include/Network.hpp
        ../include/AdjacencyList.hpp
        ../include/AdjNode.hpp
)