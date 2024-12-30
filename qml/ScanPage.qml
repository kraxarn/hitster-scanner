import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtMultimedia

ColumnLayout {
	ToolBar {
		Layout.fillWidth: true

		RowLayout {
			anchors.fill: parent

			ToolButton {
				icon.source: "qrc:/res/icon/chevron-left.svg"
				Layout.alignment: Qt.AlignVCenter
				onClicked: stack.pop()
			}

			Label {
				text: qsTr("Scan QR code")
				font.pointSize: 24
				Layout.fillWidth: true
			}
		}
	}

	Item {
		Layout.fillWidth: true
		Layout.fillHeight: true
		Layout.margins: 8

		CaptureSession {
			videoOutput: videoOutput

			camera: Camera {
				id: camera
			}
		}

		VideoOutput {
			id: videoOutput
			anchors.fill: parent
		}
	}

	RowLayout {
		Layout.fillWidth: true
		Layout.margins: 16

		Item {
			Layout.fillWidth: true
		}

		ToolButton {
			icon.source: "qrc:/res/icon/flash-off.svg"
			Layout.alignment: Qt.AlignVCenter
		}

		Item {
			Layout.fillWidth: true
		}
	}
}
