#pragma once

#include "entity/track.hpp"

#include <QJsonObject>
#include <qqmlintegration.h>

class CurrentlyPlaying
{
	Q_GADGET
	QML_VALUE_TYPE(CurrentlyPlaying)

	Q_PROPERTY(Track item READ getItem)
	Q_PROPERTY(int progressMs READ getProgressMs)

public:
	static auto fromJson(const QJsonObject &json) -> CurrentlyPlaying;

	[[nodiscard]]
	auto getItem() const -> const Track &;

	[[nodiscard]]
	auto getProgressMs() const -> int;

private:
	Track item;
	int progressMs = 0;
};
