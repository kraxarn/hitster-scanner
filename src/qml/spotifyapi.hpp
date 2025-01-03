#pragma once

#include <QNetworkAccessManager>
#include <qqmlintegration.h>
#include <QSettings>

class SpotifyApi: public QObject
{
	Q_OBJECT
	QML_ELEMENT

	Q_PROPERTY(bool authenticated READ getAuthenticated WRITE setAuthenticated NOTIFY authenticatedChanged)

public:
	explicit SpotifyApi(QObject *parent = nullptr);

	Q_INVOKABLE static QUrl authUrl();

	[[nodiscard]]
	auto getAuthenticated() const -> bool;

	void setAuthenticated(bool authenticated);

	Q_INVOKABLE bool tryAuthenticate(const QUrl &url);

signals:
	void authenticatedChanged();

private:
	QSettings *settings;
	QNetworkAccessManager *http = nullptr;
	bool authenticated = false;

	[[nodiscard]]
	auto getAccessToken() const -> QString;

	[[nodiscard]]
	auto getRefreshToken() const -> QString;

	void authenticate(const QString &code);

	void onReqeustFinished(QNetworkReply *reply);
};
