import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import MyPhotos.Core
import MyPhotos.Manager

Window {
    width: 640
    height: 480
    visible: true
    title: mpApp.appName

    FileDialog {
        id: file_selector
        fileMode: FileDialog.OpenFiles
        nameFilters: [
            "Image files (*.jpg *.jpeg *.png *.bmp)",
            "Other files (*.*)",
        ]
        onAccepted: {
            if (selectedFiles.length > 0) {
                FileManager.importFiles(selectedFiles)
            }
        }
    }

    Button {
        text: "Import"
        onClicked: {
            file_selector.open()
        }
    }
}
