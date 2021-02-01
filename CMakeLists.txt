CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

PROJECT(Mong LANGUAGES CXX)

Include(CMakeModules/CPM.cmake)

CPMAddPackage(
        NAME Cup
        VERSION 2020.523
        GITHUB_REPOSITORY Andres6936/Cup
)

CPMAddPackage(
        NAME Cup.Object
        VERSION 2020.0505
        GITHUB_REPOSITORY Andres6936/Cup.Object
)

ADD_LIBRARY(Stephan STATIC
        Source/Stephan/BinaryInputBuffer.cpp
        Source/Stephan/Hash.cpp
        Source/Stephan/HuffmanTree.cpp
        Source/Stephan/Inflate.cpp
        )
TARGET_INCLUDE_DIRECTORIES(Stephan PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>)
SET_TARGET_PROPERTIES(Stephan PROPERTIES CXX_STANDARD 17)

ADD_EXECUTABLE(Stephan.Main Source/Stephan/uncompress.cpp)
SET_TARGET_PROPERTIES(Stephan.Main PROPERTIES CXX_STANDARD 17)
TARGET_LINK_LIBRARIES(Stephan.Main PRIVATE Stephan)

ADD_EXECUTABLE(Mong
        Source/Main.cpp
        Source/App.cpp
        Source/Chunk.cpp
        Source/Information.cpp
        Source/CRC.cpp
        Source/Palette.cpp
        Source/Data.cpp
        )
TARGET_INCLUDE_DIRECTORIES(Mong PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>)
SET_TARGET_PROPERTIES(Mong PROPERTIES CXX_STANDARD 20)
TARGET_LINK_LIBRARIES(Mong PRIVATE Cup)
TARGET_LINK_LIBRARIES(Mong PRIVATE Cup.Object)
