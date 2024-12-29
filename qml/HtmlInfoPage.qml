import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import HowToPlay

ColumnLayout {
	id: page
	anchors.fill: parent

	property string title
	property url url

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
				text: page.title
				font.pointSize: 24
				Layout.fillWidth: true
			}

			ToolButton {
				icon.source: "qrc:/res/icon/web.svg"
				Layout.alignment: Qt.AlignVCenter
				onClicked: Qt.openUrlExternally(page.url)
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
