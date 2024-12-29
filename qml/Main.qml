import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

ApplicationWindow {
	id: root
	title: qsTr("Hitster")
	visible: true
	width: 540
	height: 960

	Material.theme: Material.Dark
	Material.primary: Material.color(Material.Grey, Material.Shade900)
	Material.background: Material.color(Material.Grey, Material.ShadeA700)
	Material.accent: "#f9ccdb"

	StackView {
		id: stack
		anchors.fill: parent
		initialItem: homePage
	}

	Component {
		id: homePage
		HomePage {
		}
	}

	Component {
		id: howToPlayPage
		HowToPlayPage {
		}
	}
}
