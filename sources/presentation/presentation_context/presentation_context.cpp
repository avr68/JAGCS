#include "presentation_context.h"

// Internal
#include "settings_provider.h"

#include "vehicle.h"
#include "link_description.h"
#include "mission.h"
#include "mission_assignment.h"
#include "mission_item.h"
#include "video_source.h"
#include "modes.h"
#include "command.h"
#include "log_message.h"

#include "translation_helper.h"

#include "topbar_presenter.h"
#include "location_map_presenter.h"
#include "active_video_presenter.h"
#include "dashboard_presenter.h"
#include "satellite_display_presenter.h"
#include "flight_display_presenter.h"
#include "navigation_display_presenter.h"
#include "control_display_presenter.h"
#include "link_list_presenter.h"
#include "link_presenter.h"
#include "vehicle_list_presenter.h"
#include "vehicle_presenter.h"
#include "planning_presenter.h"
#include "mission_list_presenter.h"
#include "mission_presenter.h"
#include "mission_edit_presenter.h"
#include "mission_item_list_presenter.h"
#include "mission_item_presenter.h"
#include "mission_item_edit_presenter.h"
#include "database_presenter.h"
#include "gui_settings_presenter.h"
#include "joystick_settings_presenter.h"
#include "map_settings_presenter.h"
#include "network_settings_presenter.h"
#include "video_source_list_presenter.h"
#include "video_source_presenter.h"
#include "about_presenter.h"

// Qt
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

using namespace presentation;

PresentationContext::PresentationContext()
{
    this->registerQuickTypes();

    m_engine = new QQmlApplicationEngine(qApp);

    m_engine->rootContext()->setContextProperty("translator",
                                                QVariant::fromValue(new TranslationHelper(qApp)));
    QObject::connect(m_engine, &QQmlEngine::quit, qApp, &QGuiApplication::quit);
}

PresentationContext::~PresentationContext()
{
    PresentationContext::saveWindowedGeometry();
}

PresentationContext* PresentationContext::instance()
{
    static PresentationContext context;
    return &context;
}

QObject* PresentationContext::rootView()
{
    QList<QObject*> list = instance()->m_engine->rootObjects();
    return list.isEmpty() ? nullptr : list.first();
}

QQmlContext* PresentationContext::rootContext()
{
    return instance()->m_engine->rootContext();
}

void PresentationContext::start()
{
    instance()->m_engine->load(QUrl("qrc:/Views/MainView.qml"));
}

void PresentationContext::show()
{
    if (settings::Provider::boolValue(settings::gui::fullscreen))
    {
        PresentationContext::showFullscreen();
    }
    else
    {
        PresentationContext::showWindowed();
    }
}

void PresentationContext::showFullscreen()
{
    //instance()->m_view->showFullScreen();
}

void PresentationContext::showWindowed()
{/*
    QRect rect = settings::Provider::value(settings::gui::geometry).toRect();

    if (rect.isNull())
    {
        instance()->m_view->showMaximized();
    }
    else
    {
        instance()->m_view->setGeometry(rect);
        instance()->m_view->show();
    }*/
}

void PresentationContext::saveWindowedGeometry()
{
    //if (instance()->m_view->windowState() & Qt::WindowFullScreen) return;
    //settings::Provider::setValue(settings::gui::geometry, instance()->m_view->geometry());
}

void PresentationContext::registerQuickTypes()
{
    qmlRegisterUncreatableType<dao::Vehicle>(
                "JAGCS", 1, 0, "Vehicle", "Can't create entities in QML");
    qmlRegisterUncreatableType<dao::LinkDescription>(
                "JAGCS", 1, 0, "LinkDescription", "Can't create entities in QML");
    qmlRegisterUncreatableType<dao::Mission>(
                "JAGCS", 1, 0, "Mission", "Can't create entities in QML");
    qmlRegisterUncreatableType<dao::MissionAssignment>(
                "JAGCS", 1, 0, "MissionAssignment", "Can't create entities in QML");
    qmlRegisterUncreatableType<dao::MissionItem>(
                "JAGCS", 1, 0, "MissionItem", "Can't create entities in QML");
    qmlRegisterUncreatableType<dao::VideoSource>(
                "JAGCS", 1, 0, "VideoSource", "Can't create entities in QML");
    qmlRegisterUncreatableType<domain::Command>(
                "JAGCS", 1, 0, "Command", "Can't create commands in QML");
    qmlRegisterUncreatableType<domain::LogMessage>(
                "JAGCS", 1, 0, "LogMessage", "Can't create log messages in QML");

    qmlRegisterUncreatableMetaObject(domain::staticMetaObject, "JAGCS", 1, 0, "Domain",
                                     "Can't create enums in QML");

    qmlRegisterType<TopbarPresenter>("JAGCS", 1, 0, "TopbarPresenter");
    qmlRegisterType<LocationMapPresenter>("JAGCS", 1, 0, "MapPresenter");
    qmlRegisterType<ActiveVideoPresenter>("JAGCS", 1, 0, "ActiveVideoPresenter");
    qmlRegisterType<DashboardPresenter>("JAGCS", 1, 0, "DashboardPresenter");
    qmlRegisterType<SatelliteDisplayPresenter>("JAGCS", 1, 0, "SatelliteDisplayPresenter");
    qmlRegisterType<FlightDisplayPresenter>("JAGCS", 1, 0, "FlightDisplayPresenter");
    qmlRegisterType<NavigationDisplayPresenter>("JAGCS", 1, 0, "NavigationDisplayPresenter");
    qmlRegisterType<ControlDisplayPresenter>("JAGCS", 1, 0, "ControlDisplayPresenter");
    qmlRegisterType<LinkListPresenter>("JAGCS", 1, 0, "LinkListPresenter");
    qmlRegisterType<LinkPresenter>("JAGCS", 1, 0, "LinkPresenter");
    qmlRegisterType<VehicleListPresenter>("JAGCS", 1, 0, "VehicleListPresenter");
    qmlRegisterType<VehiclePresenter>("JAGCS", 1, 0, "VehiclePresenter");
    qmlRegisterType<PlanningPresenter>("JAGCS", 1, 0, "PlanningPresenter");
    qmlRegisterType<MissionListPresenter>("JAGCS", 1, 0, "MissionListPresenter");
    qmlRegisterType<MissionPresenter>("JAGCS", 1, 0, "MissionPresenter");
    qmlRegisterType<MissionEditPresenter>("JAGCS", 1, 0, "MissionEditPresenter");
    qmlRegisterType<MissionItemListPresenter>("JAGCS", 1, 0, "MissionItemListPresenter");
    qmlRegisterType<MissionItemPresenter>("JAGCS", 1, 0, "MissionItemPresenter");
    qmlRegisterType<MissionItemEditPresenter>("JAGCS", 1, 0, "MissionItemEditPresenter");
    qmlRegisterType<DatabasePresenter>("JAGCS", 1, 0, "DatabasePresenter");
    qmlRegisterType<GuiSettingsPresenter>("JAGCS", 1, 0, "GuiSettingsPresenter");
    qmlRegisterType<JoystickSettingsPresenter>("JAGCS", 1, 0, "JoystickSettingsPresenter");
    qmlRegisterType<MapSettingsPresenter>("JAGCS", 1, 0, "MapSettingsPresenter");
    qmlRegisterType<NetworkSettingsPresenter>("JAGCS", 1, 0, "NetworkSettingsPresenter");
    qmlRegisterType<VideoSourceListPresenter>("JAGCS", 1, 0, "VideoSourceListPresenter");
    qmlRegisterType<VideoSourcePresenter>("JAGCS", 1, 0, "VideoSourcePresenter");
    qmlRegisterType<AboutPresenter>("JAGCS", 1, 0, "AboutPresenter");
}
