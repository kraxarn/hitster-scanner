import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtMultimedia

import QrCodeScanner

ColumnLayout {
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
				text: qsTr("Scan QR code")
				font.pointSize: 24
				Layout.fillWidth: true
			}
		}
	}

	Item {
		Layout.fillWidth: true
		Layout.fillHeight: true
		Layout.margins: 8

		VideoOutput {
			id: viewfinder
			anchors.fill: parent
			fillMode: VideoOutput.PreserveAspectCrop
		}

		CaptureSession {
			videoOutput: viewfinder

			camera: Camera {
				id: camera
				active: !trackDrawer.opened
			}
		}

		QrCodeScanner {
			id: scanner
			sink: viewfinder.videoSink

			onScanned: trackDrawer.open()
			onResolved: (uri) => api.play(uri)
		}

		Timer {
			interval: 100
			running: camera.active
			repeat: true
			onTriggered: scanner.scan()
		}
	}

	RowLayout {
		Layout.fillWidth: true
		Layout.margins: 16

		DeviceButton {
		}

		Item {
			Layout.fillWidth: true
		}

		ToolButton {
			enabled: camera.isTorchModeSupported(Camera.TorchOn)

			icon.source: camera.torchMode === Camera.TorchOn
				? "qrc:/res/icon/flash.svg"
				: "qrc:/res/icon/flash-off.svg"

			onClicked: camera.torchMode = camera.torchMode === Camera.TorchOn
				? Camera.TorchOff
				: Camera.TorchOn

			Layout.alignment: Qt.AlignVCenter
		}

		Item {
			Layout.fillWidth: true
		}
	}

	Timer {
		interval: 1000
		running: trackDrawer.opened
		repeat: true
		onTriggered: api.refreshState()
	}

	TrackDrawer {
		id: trackDrawer
		albumUrl: api.state.item.album.images.length > 0
			? api.state.item.album.images.find(image => image.width === 300 && image.height === 300).url
			: ""
		trackName: api.state.item.name
		artistName: api.state.item.artists.map(artist => artist.name).join(", ")
		trackProgress: api.state.progressMs
		trackDuration: api.state.item.durationMs
	}
}
