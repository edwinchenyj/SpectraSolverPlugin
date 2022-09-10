cmake_minimum_required (VERSION 3.0)
project (SpectraSolverPluging)
 
find_package (Eigen3 3.3 REQUIRED NO_MODULE)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_definitions("-Wall -mpreferred-stack-boundary=4")
# set(gcc_coverage_compile_flags "-wl,--no-as-needed")
# set(cmake_cxx_flags "${cmake_cxx_flags} ${gcc_coverage_compile_flags}")

# OpenMP.
find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    add_definitions(-DEIGEN_DONT_PARALLELIZE)
endif()
# Pardiso.
option(PARDISO_AVAILABLE "Pardiso" ON)
if(PARDISO_AVAILABLE)
    add_definitions(-DPARDISO_AVAILABLE)
    add_library(pardiso SHARED IMPORTED)
    set_target_properties(pardiso PROPERTIES
        IMPORTED_LOCATION "$ENV{PARDISO_LIC_PATH}/libpardiso600-GNU720-X86-64.so"
    )
else()
    message("Pardiso not detected.")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/spectra/include)

add_library(GenShiftRealSolvePardisoPlugin src/pardiso_spd_solver.cpp)
target_link_libraries(GenShiftRealSolvePardisoPlugin Eigen3::Eigen pardiso lapack blas OpenMP::OpenMP_CXX pthread m)

add_executable (demo spectra_pardiso_demo.cpp)
target_link_libraries (demo GenShiftRealSolvePardisoPlugin)

add_custom_target(CopyMatrix ALL
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/A.mtx ${CMAKE_CURRENT_BINARY_DIR}/A.mtx
    COMMENT "Copying A.mtx to build directory"
)