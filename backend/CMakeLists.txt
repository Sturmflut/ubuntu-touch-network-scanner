include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(
    Networkscannerbackend_SRCS
    modules/Networkscanner/backend.cpp
    modules/Networkscanner/pingprocess.cpp
    modules/Networkscanner/pingscanner.cpp
    modules/Networkscanner/networkinfo.cpp
    modules/Networkscanner/networkaddress.cpp
)

add_library(Networkscannerbackend MODULE
    ${Networkscannerbackend_SRCS}
)

set_target_properties(Networkscannerbackend PROPERTIES
         LIBRARY_OUTPUT_DIRECTORY Networkscanner)

qt5_use_modules(Networkscannerbackend Gui Qml Quick)

# Copy qmldir file to build dir for running in QtCreator
add_custom_target(Networkscannerbackend-qmldir ALL
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/modules/Networkscanner/qmldir ${CMAKE_CURRENT_BINARY_DIR}/Networkscanner
    DEPENDS ${QMLFILES}
)

# Install plugin file
install(TARGETS Networkscannerbackend DESTINATION ${QT_IMPORTS_DIR}/Networkscanner/)
install(FILES   modules/Networkscanner/qmldir DESTINATION ${QT_IMPORTS_DIR}/Networkscanner/)

