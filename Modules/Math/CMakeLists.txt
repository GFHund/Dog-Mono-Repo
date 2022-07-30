cmake_minimum_required(VERSION 3.18.0)
project(Math VERSION 1.0.0)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(MATH_SOURCE
    src/BoundingBox2dAABB.cpp
    src/BoundingBox3dAABB.cpp
    src/Matrix.cpp
    src/SquareMatrix.cpp
    src/Matrix2.cpp
    src/Matrix3.cpp
    src/Matrix4.cpp
    src/Quaternion.cpp
    src/Ray.cpp
    src/Vector.cpp
    src/Vector2.cpp
    src/Vector3.cpp
    src/Vector4.cpp
    src/Exceptions/OutOfBoundsException.cpp
    src/Exceptions/MathOperationForbiddenException.cpp
)

add_library(Math STATIC ${MATH_SOURCE})
include_directories("./include")

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    math_test
    test/VectorTest.cpp
    test/Vector2Test.cpp
    test/Vector3Test.cpp
    test/Vector4Test.cpp
    test/MatrixTest.cpp
    test/SquareMatrixTest.cpp
    test/Matrix2Test.cpp
    test/Matrix3Test.cpp
    test/Matrix4Test.cpp
    test/BoundingBox2dAABBTest.cpp
    test/BoundingBox3dAABBTest.cpp
    
)
target_link_libraries(
    math_test
    gtest_main
    Math
)
include(GoogleTest)
gtest_discover_tests(math_test)