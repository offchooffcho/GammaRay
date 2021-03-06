/*
  earlyexittest.cpp

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2016-2017 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Giulio Camuffo <giulio.camuffo@kdab.com>

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

#include <launcher/launchoptions.h>
#include <launcher/launcher.h>
#include <launcher/probefinder.h>
#include <launcher/probeabi.h>

#include <QDebug>
#include <QtTest/qtest.h>
#include <QObject>
#include <QSignalSpy>

using namespace GammaRay;

class EarlyExitTest : public QObject
{
    Q_OBJECT
private slots:
    void testNonExistingTarget()
    {
        LaunchOptions options;
        options.setUiMode(LaunchOptions::NoUi);
        options.setProbeABI(ProbeFinder::listProbeABIs().at(0));
        options.setLaunchArguments(QStringList() << QStringLiteral("I_DONT_EXIST"));
        Launcher launcher(options);
        QVERIFY(!launcher.start());
    }

    void test()
    {
        LaunchOptions options;
        options.setUiMode(LaunchOptions::NoUi);
        // setting the probe is not strictly needed but we silence a runtime warning this way
        options.setProbeABI(ProbeFinder::listProbeABIs().first());
        options.setLaunchArguments(QStringList() << "sleep" << "1");
        Launcher launcher(options);

        QSignalSpy spy(&launcher, SIGNAL(finished()));

        QVERIFY(launcher.start());

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
        spy.wait(10000);
#else
        int loops = 0;
        while (loops++ < 100) {
            if (spy.count() == 1) {
                break;
            }
            QTest::qWait(100);
        }
#endif

        QCOMPARE(spy.count(), 1);
    }
};

QTEST_MAIN(EarlyExitTest)

#include "earlyexittest.moc"
