# l61Config.cmake

# Set variables for include dirs and libs
set(L61_STANDARD_PATH "/opt/l61")
set(L61_STANDARD_INCLUDE_DIRS "${L61_STANDARD_PATH}/l61_include")
set(L61_STANDARD_LIB_DIR "${L61_STANDARD_PATH}/lib/native")

# Create imported targets for the core shared lib and static runtime lib
add_library(l61::core SHARED IMPORTED)
set_target_properties(l61::core PROPERTIES
        IMPORTED_LOCATION "${L61_LIB_DIR}/libl61Core.so"
        INTERFACE_INCLUDE_DIRECTORIES "${L61_STANDARD_INCLUDE_DIRS}"
)

add_library(l61::lex61::runtime STATIC IMPORTED)
set_target_properties(l61::lex61::runtime PROPERTIES
        IMPORTED_LOCATION "${L61_LIB_DIR}/libl61_lex61_rt.a"
        INTERFACE_INCLUDE_DIRECTORIES "${L61_STANDARD_INCLUDE_DIRS}"
)



# Optional: Convenience variable for all l61 libs
set(L61_LIBRARIES l61::core l61::lex61::runtime)

# Provide include dirs variable for legacy usage
set(L61_STANDARD_INCLUDE_DIRS "${L61_STANDARD_INCLUDE_DIRS}" CACHE STRING "l61 include directories")


add_library(l61_base_interface INTERFACE)
target_compile_features(l61_base_interface INTERFACE
        c_std_99
        cxx_std_23
)

#A function to make plug insurance lex61 plugins
function(add_l61_lex61_target target_name output_filename)
    cmake_parse_arguments(ARG "" "" "SRCS" ${ARGN})
    add_library(${target_name} SHARED ${ARG_SRCS})

    set_target_properties(${target_name} PROPERTIES
            OUTPUT_NAME "${output_filename}"
            PREFIX ""
            SUFFIX ".lex61"
    )
    set_target_output(${target_name} ${BIN_DIR})
    set_target_property(${target_name} BUILD_RPATH "\$ORIGIN")
    target_include_directories(${target_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_link_libraries(${target_name} PRIVATE ${L61_LIBRARIES})
    target_link_libraries(${target_name} PRIVATE l61_base_interface)
    target_compile_options(${target_name} PRIVATE -fPIC -g)
    #set_target_properties(${target_name} PROPERTIES POSITION_INDEPENDENT_CODE ON)
endfunction()

# Provide version info if you want (optional)
# set(l61_VERSION 1.0.0 CACHE STRING "l61 version")

# Make sure this config is visible to find_package()
# (You’d install this file to something like /opt/l61/lib/cmake/l61/)
