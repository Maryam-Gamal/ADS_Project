project(Code_lib)

set(HEADER_FILES
        MyStack.h
        MyVector.h
        ExpressionTree.h

)

set(SOURCE_FILES
        MyStack.cpp
        MyVector.cpp
        ExpressionTree.cpp



)

add_library(Code_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})