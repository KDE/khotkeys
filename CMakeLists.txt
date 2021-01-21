project(khotkeys)
set(PROJECT_VERSION "5.20.90")
set(PROJECT_VERSION_MAJOR 5)

cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
set(QT_MIN_VERSION "5.15.0")
set(KF5_MIN_VERSION "5.74")



include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/libkhotkeysprivate
    ${CMAKE_CURRENT_BINARY_DIR}/libkhotkeysprivate
    ${CMAKE_CURRENT_BINARY_DIR}
)

find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} )

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(ECMPackageConfigHelpers)
include(ECMOptionalAddSubdirectory)
include(KDEClangFormat)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    GlobalAccel
    I18n
    KIO
    XmlGui
    KDELibs4Support
    DBusAddons
    KCMUtils
)

find_package(X11 REQUIRED OPTIONAL_COMPONENTS Xtst)
find_package(LibKWorkspace CONFIG REQUIRED)

if(X11_FOUND)
    find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS X11Extras )
    set(HAVE_XTEST ${X11_XTest_FOUND})
    set(HAVE_X11 1)
endif()

configure_file(config-X11.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-X11.h)


# Set KI18n translation domain
add_definitions(-DTRANSLATION_DOMAIN=\"khotkeys\")

# Convenience library
add_subdirectory( libkhotkeysprivate )
# has to be before kcm_hotkeys
add_subdirectory( app )
# kcm module to configure hotkeys
add_subdirectory( kcm_hotkeys )
# kdedmodule and standalone demon for hotkeys
add_subdirectory( data )
add_subdirectory( test )
add_subdirectory( doc )

# add clang-format target for all our real source files
file(GLOB_RECURSE ALL_CLANG_FORMAT_SOURCE_FILES *.cpp *.h)
kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
