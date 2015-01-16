include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(
    NetworkScannerbackend_SRCS
    modules/NetworkScanner/backend.cpp
    modules/NetworkScanner/pingprocess.cpp
    modules/NetworkScanner/pingscanner.cpp
    modules/NetworkScanner/networkinfo.cpp
    modules/NetworkScanner/networkaddress.cpp
)

add_library(NetworkScannerbackend MODULE
    ${NetworkScannerbackend_SRCS}
)

set_target_properties(NetworkScannerbackend PROPERTIES
         LIBRARY_OUTPUT_DIRECTORY NetworkScanner)

qt5_use_modules(NetworkScannerbackend Gui Qml Quick)

# Copy qmldir file to build dir for running in QtCreator
add_custom_target(NetworkScannerbackend-qmldir ALL
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/modules/NetworkScanner/qmldir ${CMAKE_CURRENT_BINARY_DIR}/NetworkScanner
    DEPENDS ${QMLFILES}
)

# Install plugin file
install(TARGETS NetworkScannerbackend DESTINATION ${QT_IMPORTS_DIR}/NetworkScanner/)
install(FILES   modules/NetworkScanner/qmldir DESTINATION ${QT_IMPORTS_DIR}/NetworkScanner/)

