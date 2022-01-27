
find_package(catch2 REQUIRED)


add_executable(${PROJECT_NAME}tests
    test.cpp
    catch.cpp
)

target_link_libraries(${PROJECT_NAME}tests
    gmlib
    catch2::catch2
)