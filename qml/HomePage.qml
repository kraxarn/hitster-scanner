import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import PermissionManager

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

	PermissionManager {
		id: permissions
	}

	MenuButton {
		text: qsTr("Start new game")
		Layout.fillWidth: true
		onClicked: {
			if (permissions.granted) {
				stack.push(scanPage)
			} else {
				permissions.request()
			}
		}
	}

	MenuButton {
		text: qsTr("How to play")
		Layout.fillWidth: true
		onClicked: stack.push(howToPlayPage)
	}

	MenuButton {
		text: qsTr("FAQ")
		Layout.fillWidth: true
		onClicked: stack.push(faqPage)
	}

	MenuButton {
		text: qsTr("Change account")
		Layout.fillWidth: true
		onClicked: stack.push(authPage)
	}

	Item {
		Layout.fillHeight: true
	}
}
