project(myphotos_qml)

set(QML_FILES
    Main.qml
)

qt_add_library(myphotos_qml STATIC)
qt_add_qml_module(myphotos_qml
    URI MyPhotosQml
    VERSION 1.0
    QML_FILES ${QML_FILES}
)

set_target_properties(myphotos_qml PROPERTIES
    PUBLIC_HEADER "${QML_FILES}"
)
