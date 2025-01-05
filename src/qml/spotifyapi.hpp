#pragma once

#include "entity/currentlyplaying.hpp"

#include <QNetworkAccessManager>
#include <qqmlintegration.h>
#include <QSettings>

class SpotifyApi: public QObject
{
	Q_OBJECT
	QML_ELEMENT

	Q_PROPERTY(bool authenticated READ getAuthenticated NOTIFY authenticatedChanged)
	Q_PROPERTY(CurrentlyPlaying currentlyPlaying READ getCurrentlyPlaying NOTIFY currentlyPlayingChanged)

public:
	explicit SpotifyApi(QObject *parent = nullptr);

	Q_INVOKABLE static QUrl authUrl();

	[[nodiscard]]
	auto getAuthenticated() const -> bool;

	[[nodiscard]]
	auto getCurrentlyPlaying() const -> const CurrentlyPlaying &;

	Q_INVOKABLE bool tryAuthenticate(const QUrl &url);

	Q_INVOKABLE void refresh();

signals:
	void authenticatedChanged();
	void currentlyPlayingChanged();

private:
	QSettings *settings;
	QNetworkAccessManager *http;

	CurrentlyPlaying currentlyPlaying;

	[[nodiscard]]
	auto require(const QString &path) const -> QNetworkRequest;

	[[nodiscard]]
	auto getAccessToken() const -> QString;

	[[nodiscard]]
	auto getRefreshToken() const -> QString;

	void authenticate(const QString &code);
	void authenticate(QNetworkReply *reply);

	void refresh(QNetworkReply *reply);
};
