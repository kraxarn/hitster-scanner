#pragma once

#include "entity/device.hpp"
#include "qml/spotifyapi.hpp"

#include <QAbstractListModel>
#include <qqmlintegration.h>

class DeviceListModel: public QAbstractListModel
{
	Q_OBJECT
	QML_ELEMENT

public:
	explicit DeviceListModel(QObject *parent = nullptr);

	[[nodiscard]]
	auto rowCount(const QModelIndex &parent) const -> int override;

	[[nodiscard]]
	auto data(const QModelIndex &index, int role) const -> QVariant override;

	[[nodiscard]]
	auto roleNames() const -> QHash<int, QByteArray> override;

	Q_INVOKABLE void loadItems() const;

private:
	QList<Device> devices;
	SpotifyApi *api;

	void clearDevices();
	void addDevices(const QList<Device> &devices);

	[[nodiscard]]
	static auto getDeviceIcon(const QString &type) -> QString;

	enum class ItemRole: int
	{
		DeviceId = Qt::UserRole + 1,
		DeviceName,
		DeviceIcon,
	};
};
