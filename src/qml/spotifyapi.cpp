#include "qml/spotifyapi.hpp"

#include <QDesktopServices>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>

#define ACCESS_TOKEN_KEY QStringLiteral("spotify/accessToken")
#define REFRESH_TOKEN_KEY QStringLiteral("spotify/refreshToken")
#define REDIRECT_URL QStringLiteral("https://localhost/auth")

SpotifyApi::SpotifyApi(QObject *parent)
	: QObject(parent),
	settings(new QSettings(this)),
	http(new QNetworkAccessManager(this))
{
}

auto SpotifyApi::getAccessToken() const -> QString
{
	return settings->value(ACCESS_TOKEN_KEY).toString();
}

auto SpotifyApi::getRefreshToken() const -> QString
{
	return settings->value(REFRESH_TOKEN_KEY).toString();
}

auto SpotifyApi::require(const QString &path) const -> QNetworkRequest
{
	QNetworkRequest request;

	request.setUrl(QUrl(QStringLiteral("https://api.spotify.com/v1") + path));

	const auto token = QStringLiteral("Bearer %1").arg(getAccessToken());
	request.setRawHeader(QStringLiteral("Authorization").toUtf8(), token.toUtf8());

	return request;
}

auto SpotifyApi::authUrl() -> QUrl
{
	const QStringList scopes{
		QStringLiteral("user-modify-playback-state"),
		QStringLiteral("streaming"),
		QStringLiteral("user-read-currently-playing"),
	};

	const auto url = QStringLiteral(
		"https://accounts.spotify.com/authorize"
		"?client_id=%1"
		"&response_type=code"
		"&redirect_uri=%2"
		"&scope=%3"
	).arg(QStringLiteral(SPOTIFY_CLIENT_ID), REDIRECT_URL, scopes.join(QStringLiteral("%20")));

	return {url};
}

auto SpotifyApi::getAuthenticated() const -> bool
{
	return !getAccessToken().isEmpty()
		&& !getRefreshToken().isEmpty();
}

auto SpotifyApi::getCurrentlyPlaying() const -> const CurrentlyPlaying &
{
	return currentlyPlaying;
}

auto SpotifyApi::tryAuthenticate(const QUrl &url) -> bool
{
	const QUrlQuery query(url);

	for (const auto &pair: query.queryItems())
	{
		if (pair.first == QStringLiteral("code"))
		{
			authenticate(pair.second);
			return true;
		}
	}

	return false;
}

void SpotifyApi::token(const QString &data)
{
	const QString token = QString("%1:%2")
		.arg(QStringLiteral(SPOTIFY_CLIENT_ID), QStringLiteral(SPOTIFY_CLIENT_SECRET))
		.toUtf8()
		.toBase64();

	const auto auth = QStringLiteral("Basic %1").arg(token);

	QNetworkRequest request;
	request.setUrl(QStringLiteral("https://accounts.spotify.com/api/token"));
	request.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/x-www-form-urlencoded"));
	request.setRawHeader(QStringLiteral("Authorization").toUtf8(), auth.toUtf8());

	auto *reply = http->post(request, data.toUtf8());
	connect(reply, &QNetworkReply::finished, [this, reply]
	{
		authenticate(reply);
	});
}

void SpotifyApi::authenticate(const QString &code)
{
	const auto data = QStringLiteral("grant_type=authorization_code&code=%1&redirect_uri=%2")
		.arg(code, REDIRECT_URL);

	token(data);
}

void SpotifyApi::authenticate(QNetworkReply *reply)
{
	const auto json = QJsonDocument::fromJson(reply->readAll()).object();

	if (json.contains(QStringLiteral("error_description")))
	{
		qWarning() << json["error_description"].toString();
	}
	else if (json.contains(QStringLiteral("access_token")))
	{
		settings->setValue(ACCESS_TOKEN_KEY, json[QStringLiteral("access_token")]);
		settings->setValue(REFRESH_TOKEN_KEY, json[QStringLiteral("refresh_token")]);

		emit authenticatedChanged();
	}
	else
	{
		qFatal() << reply->errorString();
	}

	reply->deleteLater();
}

void SpotifyApi::refresh()
{
	const auto request = require(QStringLiteral("/me/player/currently-playing"));

	auto *reply = http->get(request);
	connect(reply, &QNetworkReply::finished, [this, reply]
	{
		refresh(reply);
	});
}

void SpotifyApi::refresh(QNetworkReply *reply)
{
	if (reply->error() != QNetworkReply::NoError)
	{
		reply->deleteLater();
		return;
	}

	const auto json = QJsonDocument::fromJson(reply->readAll()).object();
	currentlyPlaying = CurrentlyPlaying::fromJson(json);

	emit currentlyPlayingChanged();
	reply->deleteLater();
}
