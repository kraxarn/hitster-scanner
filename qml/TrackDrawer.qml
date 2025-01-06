import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtQuick.Controls
import QtQuick.Effects

import WordScrambler

Drawer {
	dragMargin: 0
	edge: Qt.BottomEdge
	width: parent.width
	padding: 0

	property string albumUrl
	property string trackName
	property string artistName

	property real trackProgress
	property real trackDuration

	property bool scrambled: true
	property int randomSeed: 0

	WordScrambler {
		id: scrambler
		seed: randomSeed
	}

	RowLayout {
		anchors.fill: parent

		Image {
			id: album
			source: albumUrl
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
				text: scrambled ? scrambler.scramble(trackName) : trackName
				font.pointSize: 18
			}

			Label {
				text: scrambled ? scrambler.scramble(artistName) : artistName
				font.pointSize: 16
			}

			ProgressBar {
				value: trackProgress
				to: trackDuration

				Layout.topMargin: 16
				Layout.rightMargin: 16
				Layout.fillWidth: true
			}
		}

		Button {
			flat: true
			icon.source: `qrc:/res/icon/${scrambled ? "eye-off" : "eye"}.svg`
			onPressed: scrambled = false
			onReleased: scrambled = true

			Layout.rightMargin: 16
		}
	}
}
