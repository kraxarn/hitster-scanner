#include "qml/wordscrambler.hpp"

#include <QDebug>
#include <QRandomGenerator>

WordScrambler::WordScrambler(QObject *parent)
	: QObject(parent),
	seedValue(QRandomGenerator::global()->generate())
{
}

QString WordScrambler::scramble(const QString &text)
{
	random.seed(seedValue);

	QSet characterSet(text.cbegin(), text.cend());
	characterSet.remove(QChar::Space);
	const auto characters = characterSet.values();

	QString result(text.size(), QChar::Space);
	result.reserve(text.size());

	for (qsizetype i = 0; i < text.size(); i++)
	{
		if (!text.at(i).isLetter())
		{
			continue;
		}

		const auto chr = characters.at(random.bounded(characters.size()));
		const auto after = text.at(i).isLower() ? chr.toLower() : chr.toUpper();
		result.replace(i, 1, after);
	}

	return result;
}
