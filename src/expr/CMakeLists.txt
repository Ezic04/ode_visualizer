add_library(
    EXPR_LIB
    STATIC
    parser.cpp
    tree.cpp
)

target_include_directories(
    EXPR_LIB
    PRIVATE
    ${INCLUDE_DIR}
)
