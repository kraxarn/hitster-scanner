#pragma once

#include "entity/device.hpp"
#include "entity/track.hpp"

#include <QJsonObject>
#include <qqmlintegration.h>

class PlaybackState
{
	Q_GADGET
	QML_VALUE_TYPE(PlaybackState)

	Q_PROPERTY(Track item READ getItem)
	Q_PROPERTY(qint32 progressMs READ getProgressMs)
	Q_PROPERTY(qint64 timestamp READ getTimestamp)
	Q_PROPERTY(Device device READ getDevice)

public:
	static auto fromJson(const QJsonObject &json) -> PlaybackState;

	[[nodiscard]]
	auto getItem() const -> const Track &;

	[[nodiscard]]
	auto getProgressMs() const -> qint32;

	[[nodiscard]]
	auto getTimestamp() const -> qint64;

	[[nodiscard]]
	auto getDevice() const -> const Device &;

private:
	Track item;
	qint32 progressMs = 0;
	qint64 timestamp = 0;
	Device device;
};
