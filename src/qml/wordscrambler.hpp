#pragma once

#include <QObject>
#include <qqmlintegration.h>
#include <QRandomGenerator>

class WordScrambler: public QObject
{
	Q_OBJECT
	QML_ELEMENT

public:
	explicit WordScrambler(QObject *parent = nullptr);

	Q_INVOKABLE QString scramble(const QString &text);

signals:
	void seedChanged();

private:
	QRandomGenerator random;
	qint32 seedValue;
};
