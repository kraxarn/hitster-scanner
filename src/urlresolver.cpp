#include "urlresolver.hpp"

#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QNetworkReply>

UrlResolver::UrlResolver(QObject *parent)
	: QObject(parent),
	http(new QNetworkAccessManager(this))
{
	connect(http, &QNetworkAccessManager::finished,
		this, &UrlResolver::onReplyFinished);
}

void UrlResolver::resolve(const QUrl &url) const
{
	const QNetworkRequest request(url);
	http->head(request);
}

void UrlResolver::onReplyFinished(QNetworkReply *reply)
{
	if (reply->error() != QNetworkReply::NoError)
	{
		qWarning() << "Reply error:" << reply->errorString();
		return;
	}

	const auto cookies = reply->header(QNetworkRequest::SetCookieHeader);
	QUrl spotifyUrl;

	for (const auto &cookie: cookies.value<QList<QNetworkCookie>>())
	{
		if (cookie.name() == QStringLiteral("sp_landing"))
		{
			spotifyUrl = QUrl::fromPercentEncoding(cookie.value());
			break;
		}
	}

	if (!spotifyUrl.isValid())
	{
		qWarning() << "URL error:" << spotifyUrl.errorString();
		return;
	}

	emit resolved(spotifyUrl);
	reply->deleteLater();
}
