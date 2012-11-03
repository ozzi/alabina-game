// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

ActiveScreen {
    Text {
        id: textColumn
        width: parent.width
        height: 200
        elide: Text.ElideRight
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WordWrap
        textFormat: Text.RichText
        text: cTestModel.description
        font.pointSize: 20
    }
    Component {
        id: variantsDelegate
        StartButton {
            buttonText: variantTitle
            color: "green"
            width: testVariants.width
            height: 100
            onButtonPressed: {
                cTestModel.tryVariant(index);
            }
        }
    }
    ListView {
        id: testVariants
        width: parent.width/2
        anchors.top: textColumn.bottom
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 40
        delegate: variantsDelegate
        model: cTestModel
    }

}
