########### next target ###############

include_directories(../app)

set(khotkeys_standalone_PART_SRCS
        main.cpp
        ../app/kded.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/../app/org.kde.khotkeys.xml)

# qt5_generate_dbus_interface(../app/kded.h ../app/org.kde.khotkeys.xml )

add_executable(khotkeys_standalone ${khotkeys_standalone_PART_SRCS})
target_link_libraries(khotkeys_standalone
    khotkeysprivate
    PW::KWorkspace
    KF5::DBusAddons
    KF5::KDELibs4Support)

# I'm not sure if this is needed anymore. Check it
if(X11_XTest_FOUND)
    target_link_libraries(khotkeys_standalone ${X11_XTest_LIB})
endif()


# Don't install anything, this is just for debugging

