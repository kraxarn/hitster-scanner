import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtQuick.Controls

import DeviceListModel

Button {
	flat: true
	icon.source: "qrc:/res/icon/speaker.svg"
	text: deviceName || qsTr("<i>(no device)</i>")
	onClicked: {
		deviceModel.loadItems()
		drawer.open()
	}

	property string deviceName

	Drawer {
		id: drawer
		dragMargin: 0
		edge: Qt.BottomEdge
		width: parent.width
		height: root.height * 0.4

		ColumnLayout {
			anchors.fill: parent

			Label {
				text: qsTr("Select device")
				leftPadding: 24
				font.pointSize: 24
			}

			ListView {
				id: deviceList

				Layout.fillHeight: true
				Layout.fillWidth: true

				model: DeviceListModel {
					id: deviceModel
				}

				delegate: ItemDelegate {
					id: row
					width: deviceList.width
					onClicked: console.log(model.id)

					required property var model

					RowLayout {
						anchors.fill: parent

						Icon {
							width: 64
							height: 64
							source: "qrc:/res/icon/speaker.svg"

							Layout.fillHeight: true
						}

						Label {
							text: model.name || "UnknownDevice"
							verticalAlignment: Text.AlignVCenter

							Layout.fillWidth: true
							Layout.fillHeight: true
						}
					}
				}

				ScrollBar.vertical: ScrollBar {
				}
			}
		}
	}
}
