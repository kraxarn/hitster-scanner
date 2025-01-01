import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

RowLayout {
	Layout.alignment: Qt.AlignHCenter
	Layout.fillWidth: true

	Icon {
		source: "qrc:/res/icon/speaker.svg"
		size: 128
	}

	Label {
		text: qsTr("Hitster")
		style: Text.Raised
		styleColor: Material.accent
		font.bold: true
		font.pointSize: 54
	}
}
