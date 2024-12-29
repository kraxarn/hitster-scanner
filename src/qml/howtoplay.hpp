#pragma once

#include <QObject>
#include <qqmlintegration.h>
#include <QNetworkAccessManager>

class HowToPlay: public QObject
{
	Q_OBJECT
	QML_ELEMENT

	Q_PROPERTY(QString content READ getContent NOTIFY contentChanged)

public:
	explicit HowToPlay(QObject *parent = nullptr);

	[[nodiscard]]
	auto getContent() -> const QString &;

signals:
	void contentChanged();

private:
	QNetworkAccessManager *http;
	QNetworkReply *reply = nullptr;
	QString content;

	void onReplyFinished();
};
