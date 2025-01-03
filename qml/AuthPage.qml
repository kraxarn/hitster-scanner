import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtWebView

import SpotifyApi

ColumnLayout {
	id: page
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
				text: qsTr("Please login to continue")
				font.pointSize: 24
				Layout.fillWidth: true
			}
		}
	}

	ProgressBar {
		indeterminate: true
		visible: browser.loading

		Layout.fillWidth: true
	}

	SpotifyApi {
		id: api

		onAuthenticatedChanged: {
			stack.pop()
			stack.replace(homePage)
		}
	}

	Label {
		id: errorMessage
	}

	WebView {
		id: browser
		url: api.authUrl()

		onLoadingChanged: (request) => {
			errorMessage.text = request.errorString
			api.tryAuthenticate(request.url)
		}

		Layout.fillWidth: true
		Layout.fillHeight: true
	}
}
