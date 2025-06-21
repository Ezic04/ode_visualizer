add_subdirectory(expr)

add_executable(${PROJECT_NAME} main.cpp)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(
        ${PROJECT_NAME} 
        PRIVATE 
        stdc++exp
    )
endif()

target_link_libraries(
    ${PROJECT_NAME} 
    PRIVATE 
    EXPR_LIB
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${INCLUDE_DIR}
)
