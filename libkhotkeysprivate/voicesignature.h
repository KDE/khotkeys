/*
 *   SPDX-FileCopyrightText: 2005 Olivier Goffart <ogoffart@kde.org>
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */
#ifndef SIGNATURE_H
#define SIGNATURE_H


#include <QVector>
#include <QMap>
#include <KConfig>

class Sound;


#define WINDOW_MINIMUM 0.10
#define WINDOW_MINIMUM_ECART 200
#define WINDOW_NUMBER 7
#define WINDOW_SUPER 0.43
#define WINDOW_UNIT sound.fs()/4
#define FOUR_NUMBER 7
#define FOUR_SUPER 0


#define FFT_RANGE_INF 370
#define FFT_RANGE_SUP 2000
// #define FFT_PONDERATION(f) ((double)log(1+(f))/log(10))
#define FFT_PONDERATION(f) 1


// theses settings are better in a 8000Hz fs
/*#define FFT_RANGE_INF 300
#define FFT_RANGE_SUP 1500*/


//#define REJECT_FACTOR_ECART_REL 0.5
#define REJECT_FACTOR_DIFF 0.0018



#define HAMMING false




namespace KHotKeys
{


/**
@author Olivier Goffart
*/
class Q_DECL_EXPORT VoiceSignature{
public:
    explicit VoiceSignature(const Sound& s);

	VoiceSignature(){}
	~VoiceSignature();

	QMap<int, QMap<int, double> > data;
	
	static QMap<int, QMap<int, double> > pond;

	static float diff(const VoiceSignature &s1, const VoiceSignature &s2);


	static int size1();
	static int size2();


	static QVector<double> fft(const Sound& sound, unsigned int start, unsigned int stop);
	static bool window(const Sound& sound, unsigned int *start, unsigned int *stop);

	void write(KConfigGroup& cfg, const QString &key) const;
	void read(KConfigGroup& cfg, const QString &key);
	
	inline bool isNull() const
	{
		return data.isEmpty();
	}
};

}

#endif
