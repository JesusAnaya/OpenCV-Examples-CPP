cmake_minimum_required(VERSION 3.5)

PROJECT(OpenCV_Examples)
SET(CMAKE_CXX_STANDARD 20)

#############  Common Instructions for all Users  ############
if(MSVC)
  SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
endif()

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS})

MACRO(add_example name)
  ADD_EXECUTABLE(${name} src/${name}.cpp)
  TARGET_LINK_LIBRARIES(${name} ${OpenCV_LIBS} )
ENDMACRO()

# Add warnings all
if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Werror -pedantic)
endif()

add_example(morph_examples)
add_example(contours_examples)
add_example(basic_image_operations)
add_example(datatype_conversion)
