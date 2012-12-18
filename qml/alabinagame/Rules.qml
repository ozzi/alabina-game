// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    width: 600
    height: parent.height * 0.7
    radius: 30
    color: "green"
    opacity: 0.6
    ButtonText {
        text: qsTr("Ты стал хранителем фондов. Выбирай любую коллекцию, которая для тебя интересна. Ты сможешь не только узнать что-то новое, но и ответить на вопросы игры.  Каждый раздел содержит информацию о коллекции, историю и описание музейных предметов, их изображения. Все это поможет тебе ответить на вопросы игры и набрать максимальное количество баллов. Чтобы стать настоящим хранителем коллекций, нужно правильно ответить на все вопросы.  Если ты сразу ответил верно, получай баллы и переходи к следующему заданию. Если ответ неверный, выбирай другой. И так до тех пор, пока не будет найден правильный ответ. Но помни, что с каждой попыткой количество баллов уменьшается. Победителем считается тот игрок, который ответит на все вопросы и наберет максимальное количество баллов. Удачной игры!")
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        font.pointSize: 18
    }

    MouseArea {
        anchors.fill: parent
        onClicked: mainWindow.menuSelector = "mainMenu"
    }
}
