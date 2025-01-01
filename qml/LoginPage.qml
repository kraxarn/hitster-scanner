import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import SpotifyApi

ColumnLayout {
	spacing: 16

	anchors {
		fill: parent
		margins: 32
	}

	Item {
		Layout.fillHeight: true
	}

	Logo {
	}

	Item {
		Layout.fillHeight: true
	}

	SpotifyApi {
		id: api
	}

	MenuButton {
		text: qsTr("Login with Spotify")
		Layout.fillWidth: true
		onClicked: stack.push(authPage)
	}

	Item {
		Layout.fillHeight: true
	}
}
