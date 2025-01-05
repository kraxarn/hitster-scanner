#pragma once

#include <QObject>
#include <qqmlintegration.h>
#include <QRandomGenerator>

class WordScrambler: public QObject
{
	Q_OBJECT
	QML_ELEMENT

	Q_PROPERTY(qint32 seed READ getSeed WRITE setSeed NOTIFY seedChanged)

public:
	explicit WordScrambler(QObject *parent = nullptr);

	Q_INVOKABLE QString scramble(const QString &text);

	[[nodiscard]]
	auto getSeed() const -> quint32;

	void setSeed(qint32 seed);

signals:
	void seedChanged();

private:
	QRandomGenerator random;
	qint32 seed = 1;
};
