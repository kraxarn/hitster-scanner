#pragma once

#include "entity/album.hpp"
#include "entity/artist.hpp"

#include <qqmlintegration.h>

class Track
{
	Q_GADGET
	QML_VALUE_TYPE(Track)

	Q_PROPERTY(Album album READ getAlbum)
	Q_PROPERTY(QList<Artist> artists READ getArtists)
	Q_PROPERTY(QString name READ getName)
	Q_PROPERTY(int durationMs READ getDurationMs)

public:
	static auto fromJson(const QJsonObject &json) -> Track;

	[[nodiscard]]
	auto getAlbum() const -> const Album &;

	[[nodiscard]]
	auto getArtists() const -> const QList<Artist> &;

	[[nodiscard]]
	auto getName() const -> const QString &;

	[[nodiscard]]
	auto getDurationMs() const -> int;

private:
	Album album;
	QList<Artist> artists;
	QString name;
	int durationMs = 0;
};
