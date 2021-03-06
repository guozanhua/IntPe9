/*
IntPe9 a open source multi game, general, all purpose and educational packet editor
Copyright (C) 2012  Intline9 <Intline9@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef PACKET_H
#define PACKET_H

#include <Common.h>

#include <QVariant>
#include <QPixmap>
#include <QByteArray>
#include <QStringBuilder>
#include <QTreeWidgetItem>
#include <QList>
#include "Protocol.h"

#define SUMMARY_LEN 16

class Packet : public QObject
{
	Q_OBJECT

public:
	Packet(MessagePacket *data);
	~Packet();

	//Property's
	QVariant getField(int column);
	QPixmap getIcon();
	QVariant getBody();

	uint32 getLength();
	PacketType getType();
	QByteArray *getData();

	QList<QTreeWidgetItem*> *getProtocol(Protocol *prot);
	QString toC();
	QString toPython();

	QString strInfoHeader();
	QString strFullDump();

	//Static global functions
	static QString toHexString(QByteArray *buffer, int size = 0, int start = 0);
	static QByteArray *fromHexString(QString string);

private:
	//Data
	QString _description;
	uint32 _length;
	PacketType _type;
	QByteArray *_data;

	QList<QTreeWidgetItem*> *protocol;
	//List view fields
	QString _summary;
};
Q_DECLARE_METATYPE(Packet*);
Q_DECLARE_METATYPE(QVector<Packet*>*);
#endif