import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

Item {
	property string source
	property int size

	width: size
	height: size

	AbstractButton {
		anchors.fill: parent
		z: 1
	}

	Button {
		anchors.fill: parent
		flat: true
		checkable: false
		padding: 0
		icon.source: parent.source
		icon.width: parent.size
		icon.height: parent.size
	}
}
