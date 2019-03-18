cmake_minimum_required(VERSION 3.9)
set(CMAKE_C_STANDARD 99)
project(fdf)
set(					CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")
set(LIB_PATH			libraries)
set(SRC_PATH			sources)
set(INC_PATH			includes)
set(LFT_PATH			libft)
set(LFT_NAME			ft)
set(LFT_INC_PATH		${LIB_PATH}/${LFT_PATH})
set(LFT_LIB				${LIB_PATH}/${LFT_PATH})
find_library(OPENGL		OpenGL)
find_library(APPKIT		AppKit)
find_library(MLX		mlx)
include_directories(	${INC_PATH}
						${LFT_INC_PATH})
aux_source_directory(	${LFT_LIB} LFT_SRC)
aux_source_directory(	${SRC_PATH} SOURCE_FILES)
add_library(			${LFT_NAME} STATIC ${LFT_SRC})
add_executable(			${CMAKE_PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(	${CMAKE_PROJECT_NAME}
						${LFT_NAME}
						${MLX}
						${OPENGL}
						${APPKIT})


