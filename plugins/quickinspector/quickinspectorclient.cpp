/*
  quickinspectorclient.cpp

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2014-2017 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Volker Krause <volker.krause@kdab.com>

  Licensees holding valid commercial KDAB GammaRay licenses may use this file in
  accordance with GammaRay Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "quickinspectorclient.h"
#include <common/endpoint.h>

#include <QEvent>

using namespace GammaRay;

QuickInspectorClient::QuickInspectorClient(QObject *parent)
    : QuickInspectorInterface(parent)
{
}

QuickInspectorClient::~QuickInspectorClient()
{
}

void QuickInspectorClient::selectWindow(int index)
{
    Endpoint::instance()->invokeObject(objectName(), "selectWindow", QVariantList() << index);
}

void QuickInspectorClient::setCustomRenderMode(
    GammaRay::QuickInspectorInterface::RenderMode customRenderMode)
{
    Endpoint::instance()->invokeObject(objectName(),
                                       "setCustomRenderMode",
                                       QVariantList()
                                       << QVariant::fromValue(customRenderMode));
}

void QuickInspectorClient::checkFeatures()
{
    Endpoint::instance()->invokeObject(objectName(), "checkFeatures");
}

void GammaRay::QuickInspectorClient::setServerSideDecorationsEnabled(bool enabled)
{
    Endpoint::instance()->invokeObject(objectName(),
                                       "setServerSideDecorationsEnabled",
                                       QVariantList()
                                       << enabled);
}

void QuickInspectorClient::checkServerSideDecorations()
{
    Endpoint::instance()->invokeObject(objectName(), "checkServerSideDecorations");
}
