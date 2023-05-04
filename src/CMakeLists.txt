set(Serializer_Source
    abstractserializer.cpp abstractserializer.h
    binaryserializer.cpp binaryserializer.h
    jsonserializer.cpp jsonserializer.h
    serializer_global.h
    stringserializer.cpp stringserializer.h
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
)

target_link_libraries(SerializerStatic PUBLIC
    Qt::Core
    Qt::Gui
)

install(TARGETS Serializer
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
