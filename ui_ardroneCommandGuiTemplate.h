/********************************************************************************
** Form generated from reading UI file 'ardroneCommandGuiTemplate.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARDRONECOMMANDGUITEMPLATE_H
#define UI_ARDRONECOMMANDGUITEMPLATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ardroneCommandGuiTemplate
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QFrame *leftFrame;
    QVBoxLayout *verticalLayout;
    QLabel *videoStreamLabel;
    QFrame *statusFrame;
    QVBoxLayout *verticalLayout_2;
    QFrame *flyingLandedNodeStatusFrame;
    QHBoxLayout *horizontalLayout_2;
    QLabel *networkConnectionStatus;
    QLabel *ROSNodesStatusLabel;
    QLabel *flyingLandedLabel;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_6;
    QLabel *currentCommandLabelStatic;
    QSpacerItem *horizontalSpacer_4;
    QLabel *currentCommandLabel;
    QFrame *speedStatusFrame;
    QHBoxLayout *horizontalLayout_3;
    QLabel *velocityLabel;
    QSpacerItem *horizontalSpacer;
    QLabel *xVelocityLabel;
    QLabel *yVelocityLabel;
    QLabel *zVelocityLabel;
    QFrame *tiltFrame;
    QHBoxLayout *horizontalLayout_5;
    QLabel *tiltXYZLabelStatic;
    QSpacerItem *horizontalSpacer_2;
    QLabel *xTiltLabel;
    QLabel *yTiltLabel;
    QLabel *zTiltLabel;
    QFrame *altitudeFrame;
    QHBoxLayout *horizontalLayout_4;
    QLabel *altitudeLabelStatic;
    QSpacerItem *horizontalSpacer_3;
    QLabel *altitudeLabel;
    QFrame *rightFrame;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label;
    QComboBox *comboBox;
    QPushButton *executeManeuverPushButton;
    QSpacerItem *verticalSpacer;
    QPushButton *takeOffPushButton;
    QPushButton *landAfterFinishingPushButton;
    QPushButton *landImmediatelyPushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ardroneCommandGuiTemplate)
    {
        if (ardroneCommandGuiTemplate->objectName().isEmpty())
            ardroneCommandGuiTemplate->setObjectName(QStringLiteral("ardroneCommandGuiTemplate"));
        ardroneCommandGuiTemplate->resize(800, 600);
        centralwidget = new QWidget(ardroneCommandGuiTemplate);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        leftFrame = new QFrame(centralwidget);
        leftFrame->setObjectName(QStringLiteral("leftFrame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(leftFrame->sizePolicy().hasHeightForWidth());
        leftFrame->setSizePolicy(sizePolicy);
        leftFrame->setFrameShape(QFrame::NoFrame);
        leftFrame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(leftFrame);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        videoStreamLabel = new QLabel(leftFrame);
        videoStreamLabel->setObjectName(QStringLiteral("videoStreamLabel"));

        verticalLayout->addWidget(videoStreamLabel);

        statusFrame = new QFrame(leftFrame);
        statusFrame->setObjectName(QStringLiteral("statusFrame"));
        statusFrame->setFrameShape(QFrame::Box);
        statusFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(statusFrame);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        flyingLandedNodeStatusFrame = new QFrame(statusFrame);
        flyingLandedNodeStatusFrame->setObjectName(QStringLiteral("flyingLandedNodeStatusFrame"));
        flyingLandedNodeStatusFrame->setFrameShape(QFrame::NoFrame);
        flyingLandedNodeStatusFrame->setFrameShadow(QFrame::Plain);
        horizontalLayout_2 = new QHBoxLayout(flyingLandedNodeStatusFrame);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        networkConnectionStatus = new QLabel(flyingLandedNodeStatusFrame);
        networkConnectionStatus->setObjectName(QStringLiteral("networkConnectionStatus"));

        horizontalLayout_2->addWidget(networkConnectionStatus);

        ROSNodesStatusLabel = new QLabel(flyingLandedNodeStatusFrame);
        ROSNodesStatusLabel->setObjectName(QStringLiteral("ROSNodesStatusLabel"));

        horizontalLayout_2->addWidget(ROSNodesStatusLabel);

        flyingLandedLabel = new QLabel(flyingLandedNodeStatusFrame);
        flyingLandedLabel->setObjectName(QStringLiteral("flyingLandedLabel"));

        horizontalLayout_2->addWidget(flyingLandedLabel);


        verticalLayout_2->addWidget(flyingLandedNodeStatusFrame);

        frame = new QFrame(statusFrame);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_6 = new QHBoxLayout(frame);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        currentCommandLabelStatic = new QLabel(frame);
        currentCommandLabelStatic->setObjectName(QStringLiteral("currentCommandLabelStatic"));

        horizontalLayout_6->addWidget(currentCommandLabelStatic);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);

        currentCommandLabel = new QLabel(frame);
        currentCommandLabel->setObjectName(QStringLiteral("currentCommandLabel"));

        horizontalLayout_6->addWidget(currentCommandLabel);


        verticalLayout_2->addWidget(frame);

        speedStatusFrame = new QFrame(statusFrame);
        speedStatusFrame->setObjectName(QStringLiteral("speedStatusFrame"));
        speedStatusFrame->setFrameShape(QFrame::NoFrame);
        speedStatusFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(speedStatusFrame);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        velocityLabel = new QLabel(speedStatusFrame);
        velocityLabel->setObjectName(QStringLiteral("velocityLabel"));

        horizontalLayout_3->addWidget(velocityLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        xVelocityLabel = new QLabel(speedStatusFrame);
        xVelocityLabel->setObjectName(QStringLiteral("xVelocityLabel"));

        horizontalLayout_3->addWidget(xVelocityLabel);

        yVelocityLabel = new QLabel(speedStatusFrame);
        yVelocityLabel->setObjectName(QStringLiteral("yVelocityLabel"));

        horizontalLayout_3->addWidget(yVelocityLabel);

        zVelocityLabel = new QLabel(speedStatusFrame);
        zVelocityLabel->setObjectName(QStringLiteral("zVelocityLabel"));

        horizontalLayout_3->addWidget(zVelocityLabel);


        verticalLayout_2->addWidget(speedStatusFrame);

        tiltFrame = new QFrame(statusFrame);
        tiltFrame->setObjectName(QStringLiteral("tiltFrame"));
        tiltFrame->setFrameShape(QFrame::NoFrame);
        tiltFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_5 = new QHBoxLayout(tiltFrame);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        tiltXYZLabelStatic = new QLabel(tiltFrame);
        tiltXYZLabelStatic->setObjectName(QStringLiteral("tiltXYZLabelStatic"));

        horizontalLayout_5->addWidget(tiltXYZLabelStatic);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        xTiltLabel = new QLabel(tiltFrame);
        xTiltLabel->setObjectName(QStringLiteral("xTiltLabel"));

        horizontalLayout_5->addWidget(xTiltLabel);

        yTiltLabel = new QLabel(tiltFrame);
        yTiltLabel->setObjectName(QStringLiteral("yTiltLabel"));

        horizontalLayout_5->addWidget(yTiltLabel);

        zTiltLabel = new QLabel(tiltFrame);
        zTiltLabel->setObjectName(QStringLiteral("zTiltLabel"));

        horizontalLayout_5->addWidget(zTiltLabel);


        verticalLayout_2->addWidget(tiltFrame);

        altitudeFrame = new QFrame(statusFrame);
        altitudeFrame->setObjectName(QStringLiteral("altitudeFrame"));
        altitudeFrame->setFrameShape(QFrame::NoFrame);
        altitudeFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(altitudeFrame);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        altitudeLabelStatic = new QLabel(altitudeFrame);
        altitudeLabelStatic->setObjectName(QStringLiteral("altitudeLabelStatic"));

        horizontalLayout_4->addWidget(altitudeLabelStatic);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        altitudeLabel = new QLabel(altitudeFrame);
        altitudeLabel->setObjectName(QStringLiteral("altitudeLabel"));

        horizontalLayout_4->addWidget(altitudeLabel);


        verticalLayout_2->addWidget(altitudeFrame);


        verticalLayout->addWidget(statusFrame);


        horizontalLayout->addWidget(leftFrame);

        rightFrame = new QFrame(centralwidget);
        rightFrame->setObjectName(QStringLiteral("rightFrame"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(rightFrame->sizePolicy().hasHeightForWidth());
        rightFrame->setSizePolicy(sizePolicy1);
        rightFrame->setFrameShape(QFrame::NoFrame);
        rightFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(rightFrame);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        frame_2 = new QFrame(rightFrame);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_7 = new QHBoxLayout(frame_2);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label = new QLabel(frame_2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_7->addWidget(label);

        comboBox = new QComboBox(frame_2);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_7->addWidget(comboBox);


        verticalLayout_3->addWidget(frame_2);

        executeManeuverPushButton = new QPushButton(rightFrame);
        executeManeuverPushButton->setObjectName(QStringLiteral("executeManeuverPushButton"));

        verticalLayout_3->addWidget(executeManeuverPushButton);

        verticalSpacer = new QSpacerItem(20, 354, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        takeOffPushButton = new QPushButton(rightFrame);
        takeOffPushButton->setObjectName(QStringLiteral("takeOffPushButton"));

        verticalLayout_3->addWidget(takeOffPushButton);

        landAfterFinishingPushButton = new QPushButton(rightFrame);
        landAfterFinishingPushButton->setObjectName(QStringLiteral("landAfterFinishingPushButton"));

        verticalLayout_3->addWidget(landAfterFinishingPushButton);

        landImmediatelyPushButton = new QPushButton(rightFrame);
        landImmediatelyPushButton->setObjectName(QStringLiteral("landImmediatelyPushButton"));

        verticalLayout_3->addWidget(landImmediatelyPushButton);


        horizontalLayout->addWidget(rightFrame);

        ardroneCommandGuiTemplate->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ardroneCommandGuiTemplate);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 20));
        ardroneCommandGuiTemplate->setMenuBar(menubar);
        statusbar = new QStatusBar(ardroneCommandGuiTemplate);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        ardroneCommandGuiTemplate->setStatusBar(statusbar);

        retranslateUi(ardroneCommandGuiTemplate);

        QMetaObject::connectSlotsByName(ardroneCommandGuiTemplate);
    } // setupUi

    void retranslateUi(QMainWindow *ardroneCommandGuiTemplate)
    {
        ardroneCommandGuiTemplate->setWindowTitle(QApplication::translate("ardroneCommandGuiTemplate", "AR Drone Command GUI", 0));
        videoStreamLabel->setText(QApplication::translate("ardroneCommandGuiTemplate", "Video Stream", 0));
        networkConnectionStatus->setText(QApplication::translate("ardroneCommandGuiTemplate", "networkStatus", 0));
        ROSNodesStatusLabel->setText(QApplication::translate("ardroneCommandGuiTemplate", "ROSNodeStatus", 0));
        flyingLandedLabel->setText(QApplication::translate("ardroneCommandGuiTemplate", "flying/landed", 0));
        currentCommandLabelStatic->setText(QApplication::translate("ardroneCommandGuiTemplate", "Current Command:", 0));
        currentCommandLabel->setText(QApplication::translate("ardroneCommandGuiTemplate", "currentCommandType", 0));
        velocityLabel->setText(QApplication::translate("ardroneCommandGuiTemplate", "Velocity (xyz):", 0));
        xVelocityLabel->setText(QApplication::translate("ardroneCommandGuiTemplate", "xVelocity", 0));
        yVelocityLabel->setText(QApplication::translate("ardroneCommandGuiTemplate", "yVelocity", 0));
        zVelocityLabel->setText(QApplication::translate("ardroneCommandGuiTemplate", "zVelocity", 0));
        tiltXYZLabelStatic->setText(QApplication::translate("ardroneCommandGuiTemplate", "Tilt (xyz):", 0));
        xTiltLabel->setText(QApplication::translate("ardroneCommandGuiTemplate", "xTilt", 0));
        yTiltLabel->setText(QApplication::translate("ardroneCommandGuiTemplate", "yTilt", 0));
        zTiltLabel->setText(QApplication::translate("ardroneCommandGuiTemplate", "zTilt", 0));
        altitudeLabelStatic->setText(QApplication::translate("ardroneCommandGuiTemplate", "Altitude:", 0));
        altitudeLabel->setText(QApplication::translate("ardroneCommandGuiTemplate", "altitude", 0));
        label->setText(QApplication::translate("ardroneCommandGuiTemplate", "Maneuver Type:", 0));
        executeManeuverPushButton->setText(QApplication::translate("ardroneCommandGuiTemplate", "Execute", 0));
        takeOffPushButton->setText(QApplication::translate("ardroneCommandGuiTemplate", "Take Off", 0));
        landAfterFinishingPushButton->setText(QApplication::translate("ardroneCommandGuiTemplate", "Land After Finishing", 0));
        landImmediatelyPushButton->setText(QApplication::translate("ardroneCommandGuiTemplate", "Land Immediately", 0));
    } // retranslateUi

};

namespace Ui {
    class ardroneCommandGuiTemplate: public Ui_ardroneCommandGuiTemplate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARDRONECOMMANDGUITEMPLATE_H
