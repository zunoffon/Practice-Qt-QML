import QtQuick 2.6
import QtQuick.Window 2.2

Window {
    visible: true
    width: 500
    height: 500
    ListModel {
        id: modelProfile
        ListElement {
            varName: "Dung"
            varSkill: "Guitar"
        }
        ListElement {
            varName: "Thanh"
            varSkill: "Drive"
        }
        ListElement {
            varName: "Cuong"
            varSkill: "Spam"
        }
    }
    Component {
        id: delegateProfile
        Item {
            width: parent.width
            height: 40
            Column {
                Text {
                    font.pixelSize: 15
                    text: '<b>Name:</b> ' + varName
                }
                Text {
                    font.pixelSize: 15
                    text: '<b>Skill:</b> ' + varSkill
                }
            }
            MouseArea{
                id: itemMouseArea
                anchors.fill: parent
                onClicked: {
                    listViewProfile.currentIndex = index; //active highlight
                }
            }
        }
    }
    Component {
        id: hightLightItemSelected
        Rectangle {
            color: "lightsteelblue"
            border.color: "black"
        }
    }

    ListView {
        id: listViewProfile
        anchors.fill: parent
        width: parent.width
        height: parent.height
        spacing: 10
        model: modelProfile
        delegate: delegateProfile
        highlight: hightLightItemSelected
        onCurrentIndexChanged: {
            console.log("Item selected: ",currentIndex)
        }
    }
}
