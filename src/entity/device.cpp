#include "entity/device.hpp"

auto Device::fromJson(const QJsonObject &json) -> Device
{
	Device device;

	device.id = json[QStringLiteral("id")].toString();
	device.name = json[QStringLiteral("name")].toString();

	return device;
}

auto Device::getId() -> const QString &
{
	return id;
}

auto Device::getName() -> const QString &
{
	return name;
}
