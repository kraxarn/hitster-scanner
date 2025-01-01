#pragma once

#include <QObject>
#include <QNetworkAccessManager>

class UrlResolver: public QObject
{
	Q_OBJECT

public:
	explicit UrlResolver(QObject *parent);

	void resolve(const QUrl &url) const;

signals:
	void resolved(const QUrl &url);

private:
	QNetworkAccessManager *http;

	void onReplyFinished(QNetworkReply *reply);
};
