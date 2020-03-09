set( _projname "utility" )

#添加头文件路径
include_directories( include
    "${CMAKE_CURRENT_SOURCE_DIR}"
    )
#添加连接库路径
list( APPEND ${_projname}_LINKS_LIBS
    )
#为工程添加源文件,,第一个为工程名
add_executable( ${_projname}
    "configer.cc"
    "tool.cc"
    )
#最后一步,为可执行文件链接所有库
target_link_libraries( ${_projname} ${${_projname}_LINKS_LIBS} )


