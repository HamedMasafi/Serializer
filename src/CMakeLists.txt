set(Serializer_Source
    abstractserializer.cpp abstractserializer.h
    binaryserializer.cpp binaryserializer.h
    jsonserializer.cpp jsonserializer.h
    serializer_global.h
    stringserializer.cpp stringserializer.h
    xmlserializer.h xmlserializer.cpp
)

qt_add_library(
    Serializer
    ${Serializer_Source}
)

qt_add_library(
    SerializerStatic
    STATIC
    ${Serializer_Source}
)

target_compile_definitions(Serializer PUBLIC
    QT_DEPRECATED_WARNINGS
    SERIALIZER_LIBRARY
)

target_compile_definitions(SerializerStatic PUBLIC
    QT_DEPRECATED_WARNINGS
    SERIALIZER_LIBRARY
)

target_link_libraries(Serializer PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Xml
)

target_link_libraries(SerializerStatic PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Xml
)

install(TARGETS Serializer
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_include_directories(Serializer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_include_directories(SerializerStatic PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
