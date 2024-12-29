#pragma once

#include <QObject>
#include <qqmlintegration.h>
#include <QNetworkAccessManager>

class HtmlInfo: public QObject
{
	Q_OBJECT
	QML_ELEMENT

	Q_PROPERTY(QString content READ getContent NOTIFY contentChanged)
	Q_PROPERTY(QUrl url READ getUrl WRITE setUrl NOTIFY urlChanged)

public:
	explicit HtmlInfo(QObject *parent = nullptr);

	[[nodiscard]]
	auto getContent() -> const QString &;

	[[nodiscard]]
	auto getUrl() -> const QUrl &;

	void setUrl(const QUrl &url);

signals:
	void contentChanged();
	void urlChanged();

private:
	QNetworkAccessManager *http;
	QNetworkReply *reply = nullptr;

	QString content;
	QUrl url;

	void onReplyFinished();
};
