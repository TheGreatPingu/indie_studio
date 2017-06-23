cmake_minimum_required(VERSION 3.0)

project(indie_studio)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g -g3")

include_directories(./include/irr/
		    ./sources
		    ./include
		    ./media
		    )

if(UNIX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")


set(IRRLICHT_LIBRARY
    -L./lib/
    -lIrrlicht
    -lGL
    -lGLU
    -lXext
    -lX11
    -lXxf86vm
    )

add_executable(indie_studio
	       ./sources/main.cpp
	       ./sources/Bomb.cpp
	       ./sources/Block.cpp
	       ./sources/Player.cpp
	       ./sources/Entity.cpp
	       ./sources/IrrData.cpp
	       ./sources/Bomberman.cpp
	       ./sources/eventReceiver.cpp
	       )

target_link_libraries(indie_studio
		      ${IRRLICHT_LIBRARY}
		      )
elseif(WIN32)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/release")

add_library(Irrlicht STATIC IMPORTED)

set_property(TARGET Irrlicht PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/libIrrlicht.lib)

add_executable(indie_studio
	       ./sources/main.cpp
	       ./sources/Bomberman.cpp
	       ./sources/eventReceiver.cpp
	       ./sources/Bomb.cpp
	       ./sources/Player.cpp
	       ./sources/Entity.cpp
	       ./sources/Block.cpp
	       ./sources/IrrData.cpp
	       )

target_link_libraries(indie_studio
		      Irrlicht
		      )

endif(UNIX)
