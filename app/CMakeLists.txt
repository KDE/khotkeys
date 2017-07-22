########### next target ###############

set(dbus_interface_name org.kde.khotkeys.xml)
set(kded_khotkeys_PART_SRCS 
        kded.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/${dbus_interface_name})

qt5_generate_dbus_interface(kded.h ${dbus_interface_name})
set(dbus_interface_xml ${CMAKE_CURRENT_BINARY_DIR}/${dbus_interface_name})

add_custom_target(khotkeysdbusinterface ALL DEPENDS ${dbus_interface_name})

add_library(kded_khotkeys MODULE ${kded_khotkeys_PART_SRCS})
set_target_properties(kded_khotkeys PROPERTIES OUTPUT_NAME khotkeys)
kcoreaddons_desktop_to_json(kded_khotkeys khotkeys.desktop)

target_link_libraries(kded_khotkeys
    khotkeysprivate
    PW::KWorkspace
    KF5::DBusAddons
    KF5::KDELibs4Support)

# I'm not sure if this is needed anymore. Check it
if(X11_XTest_FOUND)
    target_link_libraries(kded_khotkeys ${X11_XTest_LIB})
endif()

set(CMAKECONFIG_INSTALL_DIR "${CMAKECONFIG_INSTALL_PREFIX}/KHotKeysDBusInterface")

ecm_configure_package_config_file(KHotKeysDBusInterfaceConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/KHotKeysDBusInterfaceConfig.cmake
    PATH_VARS KDE_INSTALL_DBUSINTERFACEDIR
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR})

########### install files ###############
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/KHotKeysDBusInterfaceConfig.cmake
    DESTINATION ${CMAKECONFIG_INSTALL_DIR})

install(TARGETS kded_khotkeys DESTINATION ${PLUGIN_INSTALL_DIR}/kf5/kded)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/org.kde.khotkeys.xml
        DESTINATION ${KDE_INSTALL_DBUSINTERFACEDIR})


