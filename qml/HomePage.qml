import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

ColumnLayout {
	spacing: 16

	anchors {
		fill: parent
		margins: 32
	}

	Item {
		Layout.fillHeight: true
	}

	RowLayout {
		Layout.alignment: Qt.AlignHCenter
		Layout.fillWidth: true

		Icon {
			source: "qrc:/res/icon/speaker.svg"
			size: 128
		}

		Label {
			text: qsTr("Hitster")
			style: Text.Raised
			styleColor: Material.accent
			font.bold: true
			font.pointSize: 54
		}
	}

	Item {
		Layout.fillHeight: true
	}

	MenuButton {
		text: qsTr("Start new game")
		Layout.fillWidth: true
	}

	MenuButton {
		text: qsTr("How to play")
		Layout.fillWidth: true
		onClicked: stack.push(howToPlayPage)
	}

	MenuButton {
		text: qsTr("FAQ")
		Layout.fillWidth: true
		onClicked: Qt.openUrlExternally("https://nordics.hitstergame.com/faq")
	}

	Item {
		Layout.fillHeight: true
	}
}
