// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

ActiveScreen {
    Text {
        id: textColumn
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 50
        anchors.rightMargin: 50
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
        width: parent.width/5*2
        height: count*100 + (count-1) * spacing
        anchors.top: textColumn.bottom
        anchors.left: parent.left
        anchors.leftMargin: testHasImage() ? parent.width/20 : parent.width/10*3
        spacing: 40
        delegate: variantsDelegate
        model: cTestModel
    }
    GameImage {
        id: testImage
        anchors.right: parent.right
        anchors.rightMargin: parent.width/20
        anchors.top: textColumn.bottom
        anchors.bottom: testVariants.bottom
        width: parent.width/5*2
        opacity: testHasImage() ? 1 : 0
        source: cTestModel.imagepath
    }
    function testHasImage()
    {
        return cTestModel.imagepath.length > 0;
    }
}
