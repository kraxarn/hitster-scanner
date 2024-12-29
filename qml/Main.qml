import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

ApplicationWindow {
	id: root
	title: qsTr("Hitster")
	visible: true
	width: 540
	height: 960

	Material.theme: Material.Dark
	Material.primary: "#000000"
	Material.background: "#000000"
	Material.accent: "#f9ccdb"

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
		}

		MenuButton {
			text: qsTr("FAQ")
			Layout.fillWidth: true
		}

		Item {
			Layout.fillHeight: true
		}
	}
}
