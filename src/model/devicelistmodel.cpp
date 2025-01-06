#include "model/devicelistmodel.hpp"

DeviceListModel::DeviceListModel(QObject *parent)
	: QAbstractListModel(parent),
	api(new SpotifyApi(this))
{
	connect(api, &SpotifyApi::devicesFetched,
		this, &DeviceListModel::addDevices);
}

auto DeviceListModel::rowCount(const QModelIndex &parent) const -> int
{
	return static_cast<int>(devices.size());
}

auto DeviceListModel::data(const QModelIndex &index, int role) const -> QVariant
{
	const auto &device = devices.at(index.row());

	switch (static_cast<ItemRole>(role))
	{
		case ItemRole::DeviceId:
			return device.getId();

		case ItemRole::DeviceName:
			return device.getName();

		default:
			return {};
	}
}

auto DeviceListModel::roleNames() const -> QHash<int, QByteArray>
{
	return {
		{static_cast<int>(ItemRole::DeviceId), "id"},
		{static_cast<int>(ItemRole::DeviceName), "name"},
	};
}

void DeviceListModel::loadItems() const
{
	api->fetchDevices();
}

void DeviceListModel::clearDevices()
{
	beginRemoveRows({}, 0,
		static_cast<int>(devices.size())
	);

	devices.clear();

	endRemoveRows();
}

void DeviceListModel::addDevices(const QList<Device> &devices)
{
	clearDevices();

	beginInsertRows({},
		static_cast<int>(this->devices.size()),
		static_cast<int>(this->devices.size() + devices.size() - 1)
	);

	this->devices.append(devices);

	endInsertRows();
}
