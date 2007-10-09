/***************************************************************************
 *   Copyright (C) 2005 by The Quassel Team                                *
 *   devel@quassel-irc.org                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef _GLOBAL_H_
#define _GLOBAL_H_

/** The protocol version we use fo the communication between core and GUI */
#define GUI_PROTOCOL 3

#define BACKLOG_FORMAT 2
#define BACKLOG_STRING "QuasselIRC Backlog File"

#define DEFAULT_PORT 4242

#include <QHash>
#include <QMutex>
#include <QString>
#include <QVariant>

/* Some global stuff */

typedef uint UserId;
typedef uint MsgId;

namespace Global {
  enum RunMode { Monolithic, ClientOnly, CoreOnly };
  extern RunMode runMode;
  extern QString quasselDir;
}

struct Exception {
    Exception(QString msg = "Unknown Exception") : _msg(msg) {};
    virtual ~Exception() {}; // make gcc happy
    virtual inline QString msg() { return _msg; }

  protected:
    QString _msg;

};

class BufferId {
public:
  BufferId();
  BufferId(uint _id, uint _networkid, uint _gid = 0, QString _net = QString(), QString _buf = QString());
  
  inline uint uid() const { return _id; }
  inline uint networkId() const { return _netid; }
  inline uint groupId() const { return _gid; }
  inline QString network() const { return _networkName; }
  QString buffer() const;
  
  void setGroupId(uint gid) { _gid = gid; }
  
  inline bool operator==(const BufferId &other) const { return _id == other._id; }

private:
  uint _id;
  uint _netid;
  uint _gid;
  QString _networkName; // WILL BE REMOVED
  QString _bufferName; // IS this actually needed?
  
  friend uint qHash(const BufferId &);
  friend QDataStream &operator<<(QDataStream &out, const BufferId &bufferId);
  friend QDataStream &operator>>(QDataStream &in, BufferId &bufferId);
};

QDataStream &operator<<(QDataStream &out, const BufferId &bufferId);
QDataStream &operator>>(QDataStream &in, BufferId &bufferId);

Q_DECLARE_METATYPE(BufferId);

uint qHash(const BufferId &);

#endif
