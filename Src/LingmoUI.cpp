/*
 * (C) Copyright 2024 Elysia. All Rights Reserved.
 * Description: LingmoUI.cpp
 * Author: Elysia <c.elysia@foxmail.com>
 * Date: 24-7-17
 * Modify Record:
 */
#include "LingmoUI.hpp"

void LingmoUI::registerTypes(QQmlEngine *engine) {
  initializeEngine(engine, _uri);
  registerTypes(_uri);
}

void LingmoUI::registerTypes(const char *uri) const {
  // Register types here
}

void LingmoUI::initializeEngine(QQmlEngine *engine,
                                [[maybe_unused]] const char *uri) {
  Q_UNUSED(engine)
}
