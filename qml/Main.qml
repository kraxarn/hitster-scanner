import QtQuick
import QtQuick.Controls.Material
import QtQuick.Controls

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
		initialItem: loginPage
	}

	Component {
		id: loginPage
		LoginPage {
		}
	}

	Component {
		id: authPage
		AuthPage {
		}
	}

	Component {
		id: homePage
		HomePage {
		}
	}

	Component {
		id: scanPage
		ScanPage {
		}
	}

	Component {
		id: howToPlayPage
		HtmlInfoPage {
			title: qsTr("How to play")
			url: "https://nordics.hitstergame.com/how-to-play"
		}
	}

	Component {
		id: faqPage
		HtmlInfoPage {
			title: qsTr("FAQ")
			url: "https://nordics.hitstergame.com/faq"
		}
	}
}
