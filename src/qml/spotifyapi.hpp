#pragma once

#include "entity/device.hpp"
#include "entity/playbackstate.hpp"

#include <QNetworkAccessManager>
#include <qqmlintegration.h>
#include <QSettings>

class SpotifyApi: public QObject
{
	Q_OBJECT
	QML_ELEMENT

	Q_PROPERTY(bool authenticated READ getAuthenticated NOTIFY authenticatedChanged)
	Q_PROPERTY(PlaybackState state READ getState NOTIFY stateChanged)

public:
	explicit SpotifyApi(QObject *parent = nullptr);

	Q_INVOKABLE static QUrl authUrl();

	[[nodiscard]]
	auto getAuthenticated() const -> bool;

	[[nodiscard]]
	auto getState() const -> const PlaybackState &;

	Q_INVOKABLE bool tryAuthenticate(const QUrl &url);

	Q_INVOKABLE void refreshState();

	Q_INVOKABLE void refreshToken();

	Q_INVOKABLE void play(const QString &uri) const;

	Q_INVOKABLE void fetchDevices();

	Q_INVOKABLE void transfer(const QString &deviceId) const;

signals:
	void authenticatedChanged();
	void stateChanged();
	void devicesFetched(const QList<Device> &devices);

private:
	QSettings *settings;
	QNetworkAccessManager *http;

	PlaybackState playbackState;

	[[nodiscard]]
	auto require(const QString &path) const -> QNetworkRequest;

	[[nodiscard]]
	auto getAccessToken() const -> QString;

	[[nodiscard]]
	auto getRefreshToken() const -> QString;

	void token(const QString &data);

	void authenticate(const QString &code);
	void authenticate(QNetworkReply *reply);

	void refreshState(QNetworkReply *reply);
	void fetchDevices(QNetworkReply *reply);
};
