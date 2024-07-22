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
add_executable(AyEdD_Routers main.cpp)

# Link the OBJECT library to the executable
target_link_libraries(AyEdD_Routers PRIVATE $<TARGET_OBJECTS:AyEdD_Routers_ObjLib>)

# Include headers
target_include_directories(AyEdD_Routers PRIVATE ../include)
