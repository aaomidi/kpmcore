/*
    SPDX-FileCopyrightText: 2019 Andrius Štikonas <andrius@stikonas.eu>
    SPDX-FileCopyrightText: 2020 Arnaud Ferraris <arnaud.ferraris@collabora.com>
    SPDX-FileCopyrightText: 2020 Gaël PORTAY <gael.portay@collabora.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "fs/bitlocker.h"

namespace FS
{
FileSystem::CommandSupportType bitlocker::m_Move = FileSystem::cmdSupportCore;
FileSystem::CommandSupportType bitlocker::m_Copy = FileSystem::cmdSupportCore;
FileSystem::CommandSupportType bitlocker::m_Backup = FileSystem::cmdSupportCore;

bitlocker::bitlocker(qint64 firstsector, qint64 lastsector, qint64 sectorsused, const QString& label, const QVariantMap& features) :
    FileSystem(firstsector, lastsector, sectorsused, label, features, FileSystem::Type::BitLocker)
{
}
}
