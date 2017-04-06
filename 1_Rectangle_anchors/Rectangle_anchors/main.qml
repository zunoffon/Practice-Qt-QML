import QtQuick 2.6
import QtQuick.Window 2.2

Window {
    visible: true
    width: 500
    height: 500
    //color: "red"
    title: qsTr("Practice Rectangle & anchors")

    Rectangle {
        id: yellowBox
        width: parent.width / 2
        height: parent.height / 2
        color: "yellow"
        anchors {
            centerIn: parent
        }
    }
    //deploy: recTopCenter, recBottomCenter, recLeft, recRight,
    //        recTopLeft, recTopRight, recBottomLeft, recBottomRight
    RecRedBox {
        id: recTopCenter
        anchors {
            horizontalCenter: yellowBox.horizontalCenter
            bottom: yellowBox.top
        }
    }
    RecRedBox {
        id: recBottomCenter
        anchors {
            horizontalCenter: yellowBox.horizontalCenter
            top: yellowBox.bottom
        }
    }
    RecRedBox {
        id: recLeft
        anchors {
            verticalCenter: yellowBox.verticalCenter
            right: yellowBox.left
        }
    }
    RecRedBox {
        id: recRight
        anchors {
            verticalCenter: yellowBox.verticalCenter
            left: yellowBox.right
        }
    }
    RecRedBox {
        id: recTopLeft
        anchors {
            bottom: yellowBox.top
            right: yellowBox.left
        }
    }
    RecRedBox {
        id: recTopRight
        anchors {
            bottom: yellowBox.top
            left: yellowBox.right
        }
    }
    RecRedBox {
        id: recBottomLeft
        anchors {
            top: yellowBox.bottom
            right: yellowBox.left
        }
    }
    RecRedBox {
        id: recBottomRight
        anchors {
            top: yellowBox.bottom
            left: yellowBox.right
        }
    }
}
