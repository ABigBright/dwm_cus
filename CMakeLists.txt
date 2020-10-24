cmake_minimum_required(VERSION 3.10)

# misc config
message(STATUS "CMAKE_GENERATOR = " ${CMAKE_GENERATOR})
set(DWM_VERSION 6.2)
project(DWM VERSION ${DWM_VERSION} LANGUAGES C)

# source file config
set(srcs drw.c dwm.c util.c)
message(STATUS "srcs = " ${srcs})

# target file  confiSS
add_executable(dwm ${srcs})

# compile config
set(DWM_COMPILE_INCLUDE
    /usr/X11R6/include
    /usr/include/freetype2
)

set(DWM_COMPILE_FLAG
    -std=c99
    -pedantic
    -Wall
    -Wno-deprecated-declarations
    -Os
    -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_C_SOURCE=2 -DVERSION=\"${DWM_VERSION}\"
    -DXINERAMA
)

target_include_directories(dwm PRIVATE 
    ${DWM_COMPILE_INCLUDE}
)
target_compile_options(dwm PRIVATE
    ${DWM_COMPILE_FLAG}
)

# link config
set(DWM_LOAD_LIBS Xinerama 
    fontconfig Xft X11 Xrender)
set(DWM_LOAD_LIBS_FLAG "-L/usr/X11R6/lib")

target_link_libraries(dwm ${DWM_LOAD_LIBS})
target_link_options(dwm BEFORE PRIVATE ${DWM_LOAD_LIBS_FLAG})

