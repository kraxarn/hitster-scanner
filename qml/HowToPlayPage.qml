import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import HowToPlay

ColumnLayout {
	anchors.fill: parent

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
				text: qsTr("How to play")
				font.pointSize: 24
				Layout.fillWidth: true
			}
		}
	}

	HowToPlay {
		id: howToPlay
	}

	BusyIndicator {
		Layout.fillHeight: true
		Layout.alignment: Qt.AlignHCenter
		visible: !howToPlay.content
	}

	ScrollView {
		Layout.fillWidth: true
		Layout.fillHeight: true

		Label {
			text: howToPlay.content
			visible: !!howToPlay.content
			textFormat: Text.StyledText
		}
	}
}
