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

# Ruta donde se encuentran las bibliotecas necesarias (ajusta según tu instalación de MinGW)
set(MINGW_BIN_DIR "C:/MinGW/bin")

# Copiar las bibliotecas necesarias al directorio de salida
add_custom_command(TARGET AyEdD_Routers POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${MINGW_BIN_DIR}/libgcc_s_dw2-1.dll
        $<TARGET_FILE_DIR:AyEdD_Routers>
        COMMAND_EXPAND_LISTS
        COMMENT "Copying libgcc_s_dw2-1.dll to output directory")
