import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import HtmlInfo

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

	HtmlInfo {
		id: info
		url: page.url
	}

	BusyIndicator {
		Layout.fillHeight: true
		Layout.alignment: Qt.AlignHCenter
		visible: !info.content
	}

	ScrollView {
		Layout.fillWidth: true
		Layout.fillHeight: true

		Label {
			text: info.content
			visible: !!info.content
			textFormat: Text.StyledText
		}
	}
}
