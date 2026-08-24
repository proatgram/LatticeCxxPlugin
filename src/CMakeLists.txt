add_library(LatticeCxxPlugin MODULE)

target_sources(LatticeCxxPlugin
    PRIVATE
        "${CMAKE_SOURCE_DIR}/src/Plugin.cpp"
        "${CMAKE_SOURCE_DIR}/src/CxxToolchain.cpp"
        "${CMAKE_SOURCE_DIR}/src/CxxLibrary.cpp"
        "${CMAKE_SOURCE_DIR}/src/CxxBinary.cpp"
    PUBLIC FILE_SET CXX_MODULES
        BASE_DIRS "${CMAKE_SOURCE_DIR}/modules"
        FILES
            "${CMAKE_SOURCE_DIR}/modules/Plugin.cppm"
            "${CMAKE_SOURCE_DIR}/modules/CxxToolchain.cppm"
            "${CMAKE_SOURCE_DIR}/modules/CxxLibrary.cppm"
            "${CMAKE_SOURCE_DIR}/modules/CxxBinary.cppm"
)

target_link_libraries(LatticeCxxPlugin
    PUBLIC
        lattice::Plugins
        lattice::Registry
    PRIVATE
        lattice::Object
)
