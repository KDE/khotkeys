/*
 *   SPDX-FileCopyrightText: 2005 Olivier Goffart <ogoffart@kde.org>
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef SOUND_H
#define SOUND_H

#include <QVector>
#include <QCharRef>

/**
@author Olivier Goffart
*/
class Q_DECL_EXPORT Sound{
public:
    Sound();
    ~Sound();

	void load(const QString &filename);
	void save(const QString &filename) const;

	unsigned int size() const
	{
		return data.size();
	}

	inline float at(int pos) const
	{
		return (float)(data.at(pos))/max;
	}

	inline uint fs() const
	{
		return _fs;
	}

	QVector<Q_INT32> data;
	quint32 max;
	uint _fs;
};

#endif
