import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtQuick.Controls
import QtQuick.Effects

Drawer {
	id: drawer
	dragMargin: 0
	edge: Qt.BottomEdge
	width: parent.width
	padding: 0

	property string albumUrl
	property string trackName
	property string artistName

	property real trackProgress
	property real trackDuration

	RowLayout {
		anchors.fill: parent

		Image {
			id: album
			source: drawer.albumUrl
			fillMode: Image.PreserveAspectFit
			asynchronous: true

			Layout.preferredWidth: 150
			Layout.preferredHeight: 150
			Layout.leftMargin: 32
			Layout.bottomMargin: 32
			Layout.topMargin: 16
		}

		ColumnLayout {
			spacing: 0

			Layout.fillWidth: true
			Layout.leftMargin: 16

			Label {
				text: drawer.trackName
				font.pointSize: 18
			}

			Label {
				text: drawer.artistName
				font.pointSize: 16
			}

			ProgressBar {
				value: drawer.trackProgress
				to: drawer.trackDuration

				Layout.topMargin: 16
				Layout.rightMargin: 32
				Layout.fillWidth: true
			}
		}
	}
}
