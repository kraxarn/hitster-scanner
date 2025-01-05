#pragma once

#include <QObject>
#include <qqmlintegration.h>

class WordScrambler: public QObject
{
	Q_OBJECT
	QML_ELEMENT
	QML_SINGLETON

public:
	explicit WordScrambler(QObject *parent = nullptr);

	Q_INVOKABLE static QString scramble(const QString &text);
};
