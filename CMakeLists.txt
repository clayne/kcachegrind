cmake_minimum_required (VERSION 3.16)

# KDE Application Version, managed by release script
set(RELEASE_SERVICE_VERSION_MAJOR "25")
set(RELEASE_SERVICE_VERSION_MINOR "11")
set(RELEASE_SERVICE_VERSION_MICRO "70")
set(KCACHEGRIND_VERSION ${RELEASE_SERVICE_VERSION_MAJOR}.${RELEASE_SERVICE_VERSION_MINOR}.${RELEASE_SERVICE_VERSION_MICRO})

project(kcachegrind VERSION ${KCACHEGRIND_VERSION})

# minimal requirements
set (QT_MIN_VERSION "6.5.0")
set (KF_MIN_VERSION "6.0.0")
# TODO move the code to work on newer compiler settings
set (KDE_COMPILERSETTINGS_LEVEL "5.84.0")

find_package(ECM ${KF_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMInstallIcons)
include(FeatureSummary)
include(ECMAddAppIcon)
include(ECMPoQmTools)

find_package(Qt6 ${QT_MIN_VERSION} CONFIG REQUIRED Core DBus Gui Widgets)

find_package(KF6 ${KF_MIN_VERSION} REQUIRED
    Archive
    CoreAddons
    WidgetsAddons
    XmlGui
    I18n
    Config
    KIO
    DBusAddons
)

find_package(KF6DocTools ${KF_MIN_VERSION})
set_package_properties(KF6DocTools PROPERTIES DESCRIPTION
    "Tools to generate documentation"
    TYPE OPTIONAL
)

add_definitions(
    -DQT_DEPRECATED_WARNINGS
    -DQT_USE_QSTRINGBUILDER
    -DQT_NO_CAST_TO_ASCII
#     -DQT_NO_CAST_FROM_ASCII
#     -DQT_NO_CAST_FROM_BYTEARRAY
    -DQT_NO_URL_CAST_FROM_STRING
    -DQT_NO_SIGNALS_SLOTS_KEYWORDS
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/version.h.in ${CMAKE_CURRENT_BINARY_DIR}/version.h )

IF(NOT WIN32)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/kcachegrind.spec.in ${CMAKE_CURRENT_BINARY_DIR}/kcachegrind.spec )
ENDIF(NOT WIN32)

add_subdirectory( libcore )
add_subdirectory( cgview )
add_subdirectory( libviews )
add_subdirectory( kcachegrind )
add_subdirectory( qcachegrind )
add_subdirectory( pics )
add_subdirectory( converters )

if(KF6DocTools_FOUND)
    add_subdirectory( doc )
    kdoctools_install(po)
endif()
ki18n_install(po)
ecm_install_po_files_as_qm(poqm)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
