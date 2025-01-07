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

	[[nodiscard]]
	Q_INVOKABLE static QString getDeviceIcon(const QString &type);

private:
	QList<Device> devices;
	SpotifyApi *api;

	void clearDevices();
	void addDevices(const QList<Device> &devices);

	enum class ItemRole: int
	{
		DeviceId = Qt::UserRole + 1,
		DeviceName,
		DeviceIcon,
	};
};
