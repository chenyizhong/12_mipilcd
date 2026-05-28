# 定义变量：源码目录 = LED 文件夹，现在用file递归出所有.c，不用这个了
#set(src_dirs LED)

# 定义变量：头文件目录 = LED 文件夹，现在不用这个了
#set(include_dirs LED)

# 定义变量：依赖组件 = driver
#意思：本文件夹依赖 ESP-IDF 的 driver 组件
set(requires
    driver
    esp_lvgl_adapter
    lvgl
    BSP
    service
)

# 递归搜索路径下的所有符合的.c文件
file(
    GLOB_RECURSE SOURCES
      "${CMAKE_CURRENT_LIST_DIR}/*.c"
      #"${CMAKE_CURRENT_SOURCE_DIR}/ConsoleAPP/*.c"
      
)

#目录下所有含有.h的目录
# 1. 递归找到所有 .h 文件
file(GLOB_RECURSE ALL_HEADER_FILES "${CMAKE_CURRENT_LIST_DIR}/*.h")

# 2. 自动提取这些 .h 所在的目录（自动去重、不含空目录）
foreach(HEADER ${ALL_HEADER_FILES})
    get_filename_component(DIR ${HEADER} DIRECTORY)
    list(APPEND ALL_HEADER_DIRS ${DIR})
endforeach()
list(REMOVE_DUPLICATES ALL_HEADER_DIRS)

# ====================== 这里是新加的：打印 ALL_HEADER_DIRS ======================
message(STATUS "========================================================")
message(STATUS "  自动收集的头文件目录：")
message(STATUS "  ALL_HEADER_DIRS = ${ALL_HEADER_DIRS}")
message(STATUS "========================================================")
# ==============================================================================

idf_component_register(
     #强制链接所有符号，不做优化
    WHOLE_ARCHIVE    
    SRCS ${SOURCES}
    INCLUDE_DIRS "." ${ALL_HEADER_DIRS} 
    REQUIRES ${requires}
)

#给本目录单独设置编译规则  
### `-O3`
#最大优化等级，让代码跑得最快，建议一开始-O0
#-ffast-math，数学计算加速，提高数学计算速度
#`-Wno-format` 和 `-Wno-error=format`，这个不建议使用，关闭了格式化字符串警告
component_compile_options(-ffast-math -O0)