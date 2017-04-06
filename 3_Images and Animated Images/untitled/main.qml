import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    visible: true
    width: 640
    height: 480



    Image {
        id: windowsBackground
        opacity: 10
        width: 640
        height: 480
        source: "/../images/windows.jpg"
    }

    AnimatedImage {
        id: linuxGif
        width: 150
        height: 150
        x: 50
        y: 50
        source: "/../images/linux.gif"
    }
    //Action: Rotate picture
    Button {
        property var countClicked: 0
        id: buttonToggle
        width: 100
        height: 50
        x: 500
        y: 400
        text: "ROTATE"
        onClicked: {
            console.log("countClicked = ", countClicked);
            countClicked ++;
            countClicked % 2 == 0 ? linuxGif.rotation = 0 : linuxGif.rotation = 180;
        }
    }
    //Action: Change opacity
    Slider {
        id: slideChangeOpacity
        width: 100
        maximumValue: 1
        minimumValue: 0
        value: maximumValue
        stepSize: 0.1
        x: 500
        y: 380
        onValueChanged: {
            console.log("slide value = ", slideChangeOpacity.value)
            //yellowBox.rotation = slide.value
            windowsBackground.opacity = slideChangeOpacity.value
        }
    }
}
