qt_add_executable(basic
    ../../src/abstractserializer.cpp ../../src/abstractserializer.h
    ../../src/binaryserializer.cpp ../../src/binaryserializer.h
    ../../src/serializer_global.h
    ../../src/stringserializer.cpp ../../src/stringserializer.h
    ../../src/xmlserializer.cpp ../../src/xmlserializer.h
    tst_basic.cpp
)
target_include_directories(basic PRIVATE
    ../../src
)


add_test(NAME basic COMMAND basic)

target_link_libraries(basic PRIVATE
    Qt::Core
    Qt::Gui
    Qt::Test
    Qt::Widgets
    Qt::Xml
)


# Resources:
set(res_resource_files
    "icon.png"
)

qt_add_resources(basic "res"
    PREFIX
        "/"
    FILES
        ${res_resource_files}
)

install(TARGETS basic
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Consider using qt_generate_deploy_app_script() for app deployment if
# the project can use Qt 6.3. In that case rerun qmake2cmake with
# --min-qt-version=6.3.
