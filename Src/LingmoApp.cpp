/*
 * (C) Copyright 2024 Elysia. All Rights Reserved.
 * Description: LingmoApp.cpp
 * Author: Elysia <c.elysia@foxmail.com>
 * Date: 24-7-18
 * Modify Record:
 */
#include "LingmoApp.hpp"

LingmoApp::LingmoApp(QObject *parent)
    : QObject{parent}, _useSystemAppBar{false} {}

LingmoApp::~LingmoApp() = default;

void LingmoApp::init(QObject *launcher, QLocale locale) {
  this->launcher(launcher);

  _locale = std::move(locale);
  _engine = qmlEngine(launcher);
  _translator = new QTranslator(this);
  // ToDo: Write translation here
}
