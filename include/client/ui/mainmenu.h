#pragma once
#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <cstdio>

#include "client/ui/uipage.h"
#include "client/ui/serverlist.h"
#include "client/game.h"
#include "client/context.h"

#ifdef _WIN32
#define snprintf sprintf_s
#endif

class MainMenu : public UIPage
{
    public:
        MainMenu(Context *context);
        void ItemSelected(std::string Label);
};

#endif

