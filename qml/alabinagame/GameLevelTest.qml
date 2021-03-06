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
            animateShow: testVariants.animateStartButton
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
        property bool animateStartButton: true
        width: parent.width/5*2
        height: count*100 + (count-1) * spacing
        anchors.top: textColumn.bottom
        anchors.bottom: parent.bottom
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
        width: parent.width/5*2
        height: parent.height - 2 * textColumn.height
        opacity: testHasImage() ? 1 : 0
        source: cTestModel.imagepath
    }
    function testHasImage()
    {
        return cTestModel.imagepath.length > 0;
    }
    function onHit ()
    {
        testVariants.animateStartButton = true;
        console.debug("HIT");
    }
    function onMiss()
    {
        testVariants.animateStartButton = false;
        console.debug("MISS");
    }

    Component.onCompleted: {
        cTestModel.hit.connect(onHit);
        cTestModel.miss.connect(onMiss);
    }
}
