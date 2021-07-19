########### next target ###############

include_directories(../app
                    ${CMAKE_CURRENT_BINARY_DIR}/../app)

set(khotkeys_standalone_PART_SRCS
        main.cpp
        ../app/kded.cpp)

add_executable(khotkeys_standalone ${khotkeys_standalone_PART_SRCS})
add_dependencies(khotkeys_standalone kded_khotkeys)
target_link_libraries(khotkeys_standalone
    khotkeysprivate
    PW::KWorkspace
    KF5::DBusAddons)

# Don't install anything, this is just for debugging
