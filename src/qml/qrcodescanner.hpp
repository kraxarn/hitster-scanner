#pragma once

#include "urlresolver.hpp"

#include <QObject>
#include <qqmlintegration.h>
#include <QVideoSink>

class QrCodeScanner: public QObject
{
	Q_OBJECT
	QML_ELEMENT

	Q_PROPERTY(QVideoSink* sink READ getSink WRITE setSink NOTIFY sinkChanged)

public:
	explicit QrCodeScanner(QObject *parent = nullptr);

	[[nodiscard]]
	auto getSink() const -> QVideoSink *;

	void setSink(QVideoSink *sink);

	Q_INVOKABLE void scan() const;

signals:
	void sinkChanged();

private:
	QVideoSink *sink = nullptr;
	UrlResolver *urlResolver;

	void onUrlResolved(const QUrl &url);
};
