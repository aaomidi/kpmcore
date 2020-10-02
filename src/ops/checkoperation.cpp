/*
    SPDX-FileCopyrightText: 2008-2010 Volker Lanz <vl@fidra.de>
    SPDX-FileCopyrightText: 2012-2016 Andrius Štikonas <andrius@stikonas.eu>
    SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "ops/checkoperation.h"

#include "core/partition.h"
#include "core/device.h"

#include "jobs/checkfilesystemjob.h"
#include "jobs/resizefilesystemjob.h"

#include "util/capacity.h"

#include <QString>

#include <KLocalizedString>

/** Creates a new CheckOperation.
    @param d the Device where the Partition to check is on.
    @param p the Partition to check
*/
CheckOperation::CheckOperation(Device& d, Partition& p) :
    Operation(),
    m_TargetDevice(d),
    m_CheckedPartition(p),
    m_CheckJob(new CheckFileSystemJob(checkedPartition())),
    m_MaximizeJob(new ResizeFileSystemJob(targetDevice(), checkedPartition()))
{
    addJob(checkJob());
    addJob(maximizeJob());
}

bool CheckOperation::targets(const Device& d) const
{
    return d == targetDevice();
}

bool CheckOperation::targets(const Partition& p) const
{
    return p == checkedPartition();
}

QString CheckOperation::description() const
{
    return xi18nc("@info:status", "Check and repair partition <filename>%1</filename> (%2, %3)", checkedPartition().deviceNode(), Capacity::formatByteSize(checkedPartition().capacity()), checkedPartition().fileSystem().name());
}

/** Can a Partition be checked?
    @param p the Partition in question, may be nullptr.
    @return true if @p p can be checked.
*/
bool CheckOperation::canCheck(const Partition* p)
{
    if (p == nullptr)
        return false;

    if (p->isMounted())
        return p->fileSystem().supportCheckOnline() != FileSystem::cmdSupportNone;

    return p->fileSystem().supportCheck() != FileSystem::cmdSupportNone;
}

