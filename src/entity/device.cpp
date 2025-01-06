#include "entity/device.hpp"

auto Device::fromJson(const QJsonObject &json) -> Device
{
	Device device;

	device.id = json[QStringLiteral("id")].toString();
	device.name = json[QStringLiteral("name")].toString();

	return device;
}

auto Device::getId() const -> const QString &
{
	return id;
}

auto Device::getName() const -> const QString &
{
	return name;
}
