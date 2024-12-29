#include "qml/howtoplay.hpp"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTextDocument>

HowToPlay::HowToPlay(QObject *parent)
	: QObject(parent),
	http(new QNetworkAccessManager(this))
{
}

auto HowToPlay::getContent() -> const QString &
{
	if (!content.isNull() || reply != nullptr)
	{
		return content;
	}

	QNetworkRequest request;
	request.setUrl(QStringLiteral("https://nordics.hitstergame.com/how-to-play"));

	reply = http->get(request);

	connect(reply, &QNetworkReply::finished,
		this, &HowToPlay::onReplyFinished);

	return content;
}

void HowToPlay::onReplyFinished()
{
	const auto body = reply->readAll();

	QTextDocument doc;
	doc.setHtml(QString::fromUtf8(body));
	content = doc.toHtml();
	emit contentChanged();

	reply->deleteLater();
	reply = nullptr;
}
