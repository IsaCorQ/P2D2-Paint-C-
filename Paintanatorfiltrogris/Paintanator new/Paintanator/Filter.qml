
import QtQuick 2.12
import QtGraphicalEffects 1.12

Item {
    width: 300
    height: 300

    Image {
        id: bug
        source:
        sourceSize: Qt.size(parent.width, parent.height);
        smooth: true
        visible: false
    }

    ColorOverlay {
        anchors.fill: bug
        source: bug
        color: "#80800000"
    }
}
