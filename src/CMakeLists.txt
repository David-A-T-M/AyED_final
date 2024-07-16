# Create an OBJECT library
add_library(AyEdD_Routers_ObjLib OBJECT
        Admin.cpp
        IPAddress.cpp
        Network.cpp
        Packet.cpp
        Page.cpp
        Terminal.cpp
        Router.cpp
)

# Specify include directories for the OBJECT library
target_include_directories(AyEdD_Routers_ObjLib PUBLIC ../include)

# Create the executable using the OBJECT library
add_executable(AyEdD_Routers $<TARGET_OBJECTS:AyEdD_Routers_ObjLib>
        ../include/AdjNode.hpp
        ../include/List.hpp
        ../include/Node.hpp
        ../include/IPAddress.hpp
        ../include/Network.hpp
        ../include/Page.hpp
)