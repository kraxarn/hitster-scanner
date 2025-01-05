#include "entity/track.hpp"

#include <QJsonArray>

auto Track::fromJson(const QJsonObject &json) -> Track
{
	Track track;

	track.album = Album::fromJson(json[QStringLiteral("album")].toObject());
	track.name = json[QStringLiteral("name")].toString();
	track.durationMs = json[QStringLiteral("duration_ms")].toInt();

	const auto artists = json[QStringLiteral("artists")].toArray();
	track.artists.reserve(artists.size());

	for (const auto artist: artists)
	{
		track.artists.push_back(Artist::fromJson(artist.toObject()));
	}

	return track;
}

auto Track::getAlbum() const -> const Album &
{
	return album;
}

auto Track::getArtists() const -> const QList<Artist> &
{
	return artists;
}

auto Track::getName() const -> const QString &
{
	return name;
}

auto Track::getDurationMs() const -> int
{
	return durationMs;
}
