#include "qml/htmlinfo.hpp"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTextDocument>

HtmlInfo::HtmlInfo(QObject *parent)
	: QObject(parent),
	http(new QNetworkAccessManager(this))
{
}

auto HtmlInfo::getContent() -> const QString &
{
	if (!url.isValid() || !content.isNull() || reply != nullptr)
	{
		return content;
	}

	QNetworkRequest request;
	request.setUrl(url);

	reply = http->get(request);

	connect(reply, &QNetworkReply::finished,
		this, &HtmlInfo::onReplyFinished);

	return content;
}

void HtmlInfo::onReplyFinished()
{
	const auto body = reply->readAll();

	QTextDocument doc;
	doc.setHtml(QString::fromUtf8(body));
	content = doc.toHtml();
	emit contentChanged();

	reply->deleteLater();
	reply = nullptr;
}

auto HtmlInfo::getUrl() -> const QUrl &
{
	return url;
}

void HtmlInfo::setUrl(const QUrl &url)
{
	this->url = url;
	Q_UNUSED(getContent());
}
