import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

Button {
	flat: true
	font.pointSize: 24

	background: Item {
		Rectangle {
			anchors.fill: parent
			radius: Material.FullScale

			border {
				color: "#f9ccdb"
				width: 2
			}

			gradient: Gradient {
				orientation: Gradient.Vertical

				GradientStop {
					position: 0.90
					color: "transparent"
				}

				GradientStop {
					position: 0.95
					color: "#f9ccdb"
				}

				GradientStop {
					position: 1.00
					color: "transparent"
				}
			}
		}

		Rectangle {
			anchors.fill: parent
			radius: Material.FullScale

			gradient: Gradient {
				orientation: Gradient.Vertical

				GradientStop {
					position: 0.00
					color: "transparent"
				}

				GradientStop {
					position: 0.05
					color: "#f9ccdb"
				}

				GradientStop {
					position: 0.10
					color: "transparent"
				}
			}
		}

		Rectangle {
			width: 32
			height: 8

			anchors {
				right: parent.right
				top: parent.top
				rightMargin: 64
				topMargin: -2
			}

			gradient: Gradient {
				orientation: Gradient.Horizontal

				GradientStop {
					position: 0.0
					color: "transparent"
				}

				GradientStop {
					position: 0.1
					color: "black"
				}

				GradientStop {
					position: 0.9
					color: "black"
				}

				GradientStop {
					position: 1.0
					color: "transparent"
				}
			}
		}
	}
}
