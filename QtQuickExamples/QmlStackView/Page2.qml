﻿/*!
 *@file Page2.qml
 *@brief Page2
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
import QtQuick 2.8
import QtQuick.Controls 2.1

Page {
    id: frmWindow
    title: qsTr("个人设置")
    visible: true

    property StackView stack: null

    Button {
        height: 32
        width: 120
        text: "<-"
        anchors.left: parent.left
        anchors.top: parent.top
        onClicked: stack.pop()
    }

    Label{
        id: label
        text: qsTr("个人设置")
        height: 80
        width: 240
        anchors.centerIn: parent
        font.pixelSize: 20
    }

    Button {
        height: 32
        width: 120
        text: qsTr("帐号")
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        onClicked: {
            page3.visible = true;
            page3.stack = stack;
            stack.push(page3);
        }
    }

    Page3 {
        id: page3
        visible: false
        stack: stack
    }
}
