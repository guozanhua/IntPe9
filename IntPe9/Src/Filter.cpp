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
#include "Filter.h"

Filter::Filter(QString name, SearchMode mode, QByteArray *search)
{
	_name = name;
	_mode = mode;
	_search = search; //Implicit copy, so we should take care of deleting the object
	_isEnabled = true;
}

Filter::~Filter()
{
	delete _search;
}

bool Filter::isEnabled()
{
	return _isEnabled;
}

void Filter::setEnabled(bool state)
{
	_isEnabled = state;
}

QVariant Filter::getField(int column)
{
	switch(column)
	{
		case 0:
			return _name;
		case 1:
			return getMode();
		case 2:
			return Packet::toHexString(_search);
		default:
			return QVariant();
	}

}

QString Filter::getMode()
{
	switch(_mode)
	{
		case FRONT:
			return "Starts with";
		case ANYWHERE:
			return "Anywhere";
		case END:
			return "Ends with";
		default:
			return "Unknown";
	}
}

bool Filter::isHit(QByteArray *packet)
{
	switch(_mode)
	{
		case FRONT:
			return packet->startsWith(*_search);
		case ANYWHERE:
			return packet->contains(*_search);
		case END:
			return packet->endsWith(*_search);
		default:
			return false;
	}
}