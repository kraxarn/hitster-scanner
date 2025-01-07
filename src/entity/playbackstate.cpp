#include "entity/playbackstate.hpp"

auto PlaybackState::fromJson(const QJsonObject &json) -> PlaybackState
{
	PlaybackState currentlyPlaying;

	currentlyPlaying.progressMs = json[QStringLiteral("progress_ms")].toInt();
	currentlyPlaying.timestamp = json[QStringLiteral("timestamp")].toInteger();

	const auto item = json[QStringLiteral("item")].toObject();
	currentlyPlaying.item = Track::fromJson(item);

	const auto device = json[QStringLiteral("device")].toObject();
	currentlyPlaying.device = Device::fromJson(device);

	return currentlyPlaying;
}

auto PlaybackState::getItem() const -> const Track &
{
	return item;
}

auto PlaybackState::getProgressMs() const -> qint32
{
	return progressMs;
}

auto PlaybackState::getTimestamp() const -> qint64
{
	return timestamp;
}

auto PlaybackState::getDevice() const -> const Device &
{
	return device;
}
