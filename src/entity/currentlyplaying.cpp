#include "entity/currentlyplaying.hpp"

auto CurrentlyPlaying::fromJson(const QJsonObject &json) -> CurrentlyPlaying
{
	CurrentlyPlaying currentlyPlaying;

	currentlyPlaying.progressMs = json[QStringLiteral("progress_ms")].toInt();
	currentlyPlaying.timestamp = json[QStringLiteral("timestamp")].toInteger();

	const auto item = json[QStringLiteral("item")].toObject();
	currentlyPlaying.item = Track::fromJson(item);

	return currentlyPlaying;
}

auto CurrentlyPlaying::getItem() const -> const Track &
{
	return item;
}

auto CurrentlyPlaying::getProgressMs() const -> qint32
{
	return progressMs;
}

auto CurrentlyPlaying::getTimestamp() const -> qint64
{
	return timestamp;
}
