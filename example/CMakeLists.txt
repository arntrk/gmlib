

find_package(glfw3 REQUIRED)
find_package(glew REQUIRED)


add_executable(BSplineBasis
    BSplineBasis.cpp
    src/myWindowClass.cpp
    src/WindowBaseClass.cpp
)

target_include_directories(BSplineBasis
    PRIVATE 
        include
)

target_link_libraries(BSplineBasis
    PUBLIC
        glfw
        GLEW::GLEW
        SplineBasis
)