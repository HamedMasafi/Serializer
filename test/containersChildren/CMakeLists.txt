find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

qt_add_executable(containersChildren
    foo.cpp foo.h
    tst_containers.cpp
    parent.h parent.cpp
    child.h child.cpp
)
target_include_directories(containersChildren PRIVATE
    ../../src ../../src
)

target_link_libraries(containersChildren PRIVATE
    SerializerStatic
    Qt::Core
    Qt::Gui
    Qt::Test
    Qt::Widgets
)
target_link_libraries(containersChildren PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(containersChildren PRIVATE Qt${QT_VERSION_MAJOR}::Core)

install(TARGETS containersChildren
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
