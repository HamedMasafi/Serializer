qt_add_executable(enums
    ../../src/abstractserializer.cpp ../../src/abstractserializer.h
    ../../src/binaryserializer.cpp ../../src/binaryserializer.h
    ../../src/jsonserializer.cpp ../../src/jsonserializer.h
    ../../src/serializer_global.h
    ../../src/sqlserializer.cpp ../../src/sqlserializer.h
    ../../src/stringserializer.cpp ../../src/stringserializer.h
    foo.cpp foo.h
    tst_enums.cpp
)
target_include_directories(enums PRIVATE
    ../../src ../../src
)

target_link_libraries(enums PRIVATE
    Qt::Core
    Qt::Gui
    Qt::Test
    Qt::Widgets
)

install(TARGETS enums
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Consider using qt_generate_deploy_app_script() for app deployment if
# the project can use Qt 6.3. In that case rerun qmake2cmake with
# --min-qt-version=6.3.
