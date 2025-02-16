#pragma once
/*
    This header file provides client side access to the Neural Engine API. It includes core
    components of the engine such as the Application, Layer, and Log classes, which are essential
    for creating and running a Neural Engine application. The file also includes the EntryPoint
    macro that serves as the starting point for any client application built with the Neural Engine.
    The entry point may be configured or accessed in a different way for client side access in upcomming commits. 
*/

#include "NeuralEngine/Application.h"
#include "NeuralEngine/Layer.h"

#include "NeuralEngine/Input.h"
#include "NeuralEngine/KeyCodes.h"
#include "NeuralEngine/MouseCodes.h"

#include "NeuralEngine/Log.h"
#include "NeuralEngine/ImGui/ImGuiLayer.h"
//----------------Entry Point------------------------

#include "NeuralEngine/EntryPoint.h"

//---------------------------------------------------
