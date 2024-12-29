import QtQuick
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

	StackView {
		anchors.fill: parent
		id: stack
		initialItem: homePage
	}

	HomePage {
		id: homePage
	}
}
