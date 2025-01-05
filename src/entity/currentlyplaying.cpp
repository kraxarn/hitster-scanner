#include "entity/currentlyplaying.hpp"

auto CurrentlyPlaying::fromJson(const QJsonObject &json) -> CurrentlyPlaying
{
	CurrentlyPlaying currentlyPlaying;

	currentlyPlaying.progressMs = json[QStringLiteral("progress_ms")].toInt();

	const auto track = json[QStringLiteral("track")].toObject();
	currentlyPlaying.item = Track::fromJson(track);

	return currentlyPlaying;
}

auto CurrentlyPlaying::getItem() const -> const Track &
{
	return item;
}

auto CurrentlyPlaying::getProgressMs() const -> int
{
	return progressMs;
}
