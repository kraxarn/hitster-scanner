#include "entity/currentlyplaying.hpp"

auto CurrentlyPlaying::fromJson(const QJsonObject &json) -> CurrentlyPlaying
{
	CurrentlyPlaying currentlyPlaying;

	currentlyPlaying.progressMs = json[QStringLiteral("progress_ms")].toInt();

	const auto item = json[QStringLiteral("item")].toObject();
	currentlyPlaying.item = Track::fromJson(item);

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
