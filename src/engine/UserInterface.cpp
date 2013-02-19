/******************************************************************************
 *
 *	ShadowFox Engine Source
 *	Copyright (C) 2012-2013 by ShadowFox Studios
 *	Created: 2013-02-13 by Taylor Snead
 *
 *	Licensed under the Apache License, Version 2.0 (the "License");
 *	you may not use this file except in compliance with the License.
 *	You may obtain a copy of the License at
 *
 *	http://www.apache.org/licenses/LICENSE-2.0
 *
 *	Unless required by applicable law or agreed to in writing, software
 *	distributed under the License is distributed on an "AS IS" BASIS,
 *	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *	See the License for the specific language governing permissions and
 *	limitations under the License.
 *
 ******************************************************************************/

// External
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL3/Renderer.h>
#include <CEGUI/SchemeManager.h>
#include <CEGUI/DefaultResourceProvider.h>
#include <CEGUI/ImageManager.h>
#include <CEGUI/XMLParserModules/Xerces/XMLParser.h>

// Internal
#include "UserInterface.hpp"
#include "Thread.hpp"
#include "Engine.hpp"
#include "FileManager.hpp"
#include "Console.hpp"
#include "Input.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Settings.hpp"
#include "Time.hpp"

namespace sfs
{

UserInterface::UserInterface()
{
}

UserInterface::~UserInterface()
{
}

void UserInterface::Init()
{
	Log("UserInterface::Init: Begin");
	CEGUI::Logger::getSingletonPtr();
	Log("Got log single");
	renderer = &CEGUI::OpenGL3Renderer::bootstrapSystem();
	windowManager = CEGUI::WindowManager::getSingletonPtr();
	system = CEGUI::System::getSingletonPtr();
	context = &system->getDefaultGUIContext();
	renderer->enableExtraStateSettings(true);
	Log("UserInterface::Init: Spawned renderer");

	CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
	rp->setResourceGroupDirectory("imagesets", game->fileManager->GetGameFile("gui/imagesets").string());
	Log("UserInterface::Init: Set a resource dir");
	rp->setResourceGroupDirectory("schemes", game->fileManager->GetGameFile("gui/schemes").string());
	rp->setResourceGroupDirectory("xml_schemas", game->fileManager->GetGameFile("gui/xml_schemas").string());
	rp->setResourceGroupDirectory("styles", game->fileManager->GetGameFile("gui/styles").string());
	rp->setResourceGroupDirectory("layouts", game->fileManager->GetGameFile("gui/layouts").string());
	rp->setResourceGroupDirectory("fonts", game->fileManager->GetGameFile("gui/fonts").string());
	rp->setResourceGroupDirectory("looknfeel", game->fileManager->GetGameFile("gui/looks").string());
	rp->setDefaultResourceGroup("looknfeel");

	CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
	CEGUI::Scheme::setDefaultResourceGroup("schemes");
	CEGUI::Font::setDefaultResourceGroup("fonts");
	CEGUI::XercesParser::setSchemaDefaultResourceGroup("xml_schemas");
	CEGUI::WindowManager::setDefaultResourceGroup("layouts");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeel");

	CEGUI::SchemeManager::getSingleton().createFromFile("Generic.scheme", "schemes");
	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme", "schemes");
	CEGUI::SchemeManager::getSingleton().createFromFile("VanillaSkin.scheme", "schemes");
	CEGUI::SchemeManager::getSingleton().createFromFile("SampleBrowser.scheme", "schemes");
	CEGUI::SchemeManager::getSingleton().createFromFile("GameMenu.scheme", "schemes");
	context->getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
	context->getMouseCursor().setInitialMousePosition(vec2_cast<CEGUI::Vector2f>(game->input->GetMousePos()));
	context->setDefaultTooltipType("TaharezLook/Tooltip");
	Log("UserInterface::Init: Created scheme!");

	rootWindow = windowManager->createWindow("DefaultWindow", "Root");
	Log("UserInterface::Init: Root window");

	//CEGUI::Font& font = CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-12.font");
	//context->setDefaultFont(&font);

	context->setRootWindow(rootWindow);
	rootWindow->setMouseInputPropagationEnabled(true);
	rootWindow->setRiseOnClickEnabled(true);
	rootWindow->setZOrderingEnabled(true);
	//rootWindow->setSize(CEGUI::USize(cegui_reldim(1.0f), cegui_reldim( 1.0f)));
	//rootWindow->setAspectRatio(game->scene->mainCamera->aspectRatio);
	//rootWindow->setAutoWindow(true);

	CreateWindow(game->settings->GetValue("gui.windowLayout").s());

	//auto tex = renderer->createTextureTarget();
	//context->setRenderTarget(*tex);

}

void UserInterface::Update()
{
	//	CEGUI::System::getSingleton().renderGUI();
	system->injectTimePulse(game->time->deltaTime);
	context->injectTimePulse(game->time->deltaTime);

	if(resized)
	{
		system->notifyDisplaySizeChanged(CEGUI::Sizef((float)size.x, (float)size.y));
		resized = false;
	}

	renderer->beginRendering();
	context->draw();
	renderer->endRendering();
	windowManager->cleanDeadPool();
	//rootWindow->render();
}

void UserInterface::OnDestroy()
{
}

void UserInterface::CreateWindow(string layout)
{
	auto win = windowManager->loadLayoutFromFile(layout);
	if(win)
	{
		win->setRiseOnClickEnabled(true);
		win->setZOrderingEnabled(true);
		if(CEGUI::FrameWindow* fwin = dynamic_cast<CEGUI::FrameWindow*>(win))
		{
			fwin->setCloseButtonEnabled(true);
		}
		rootWindow->addChild(win);
	}
	else
	{
		Log("UserInterface::CreateWindow: Unable to create window.");
	}
}

void UserInterface::OnKey(uint16_t key, bool pressed)
{
	CEGUI::Key::Scan newKey = CEGUI::Key::Unknown;

	if(key == (uint16_t)Key::Esc) { newKey = CEGUI::Key::Escape; }
	else if(key == (uint16_t)Key::F1) { newKey = CEGUI::Key::F1; }
	else if(key == (uint16_t)Key::F2) { newKey = CEGUI::Key::F2; }
	else if(key == (uint16_t)Key::F3) { newKey = CEGUI::Key::F3; }
	else if(key == (uint16_t)Key::F4) { newKey = CEGUI::Key::F4; }
	else if(key == (uint16_t)Key::F5) { newKey = CEGUI::Key::F5; }
	else if(key == (uint16_t)Key::F6) { newKey = CEGUI::Key::F6; }
	else if(key == (uint16_t)Key::F7) { newKey = CEGUI::Key::F7; }
	else if(key == (uint16_t)Key::F8) { newKey = CEGUI::Key::F8; }
	else if(key == (uint16_t)Key::F9) { newKey = CEGUI::Key::F9; }
	else if(key == (uint16_t)Key::F10) { newKey = CEGUI::Key::F10; }
	else if(key == (uint16_t)Key::F11) { newKey = CEGUI::Key::F11; }
	else if(key == (uint16_t)Key::F12) { newKey = CEGUI::Key::F12; }
	else if(key == (uint16_t)Key::Up) { newKey = CEGUI::Key::ArrowUp; }
	else if(key == (uint16_t)Key::Down) { newKey = CEGUI::Key::ArrowDown; }
	else if(key == (uint16_t)Key::Left) { newKey = CEGUI::Key::ArrowLeft; }
	else if(key == (uint16_t)Key::Right) { newKey = CEGUI::Key::ArrowRight; }
	else if(key == (uint16_t)Key::LShift) { newKey = CEGUI::Key::LeftShift; }
	else if(key == (uint16_t)Key::RShift) { newKey = CEGUI::Key::RightShift; }
	else if(key == (uint16_t)Key::LCtrl) { newKey = CEGUI::Key::LeftControl; }
	else if(key == (uint16_t)Key::RCtrl) { newKey = CEGUI::Key::RightControl; }
	else if(key == (uint16_t)Key::LAlt) { newKey = CEGUI::Key::LeftAlt; }
	else if(key == (uint16_t)Key::RAlt) { newKey = CEGUI::Key::RightAlt; }
	else if(key == (uint16_t)Key::Tab) { newKey = CEGUI::Key::Tab; }
	else if(key == (uint16_t)Key::Enter) { newKey = CEGUI::Key::Return; }
	else if(key == (uint16_t)Key::Backspace) { newKey = CEGUI::Key::Backspace; }
	else if(key == (uint16_t)Key::Insert) { newKey = CEGUI::Key::Insert; }
	else if(key == (uint16_t)Key::Delete) { newKey = CEGUI::Key::Delete; }
	else if(key == (uint16_t)Key::PageUp) { newKey = CEGUI::Key::PageUp; }
	else if(key == (uint16_t)Key::PageDown) { newKey = CEGUI::Key::PageDown; }
	else if(key == (uint16_t)Key::Home) { newKey = CEGUI::Key::Home; }
	else if(key == (uint16_t)Key::End) { newKey = CEGUI::Key::End; }
	else if(key == (uint16_t)Key::NumEnter) { newKey = CEGUI::Key::NumpadEnter; }

	if(pressed)
	{
		if(newKey != CEGUI::Key::Unknown)
		{
			context->injectKeyDown(newKey);
		}
	}
	else
	{
		if(newKey != CEGUI::Key::Unknown)
		{
			context->injectKeyUp(newKey);
		}
	}
}

void UserInterface::OnChar(char key)
{
	context->injectChar(key);
}

void UserInterface::OnMouseButton(uint16_t btn, bool pressed)
{
	CEGUI::MouseButton newBtn = CEGUI::NoButton;
	if(btn == (uint16_t)Key::MouseLeft)
	{
		newBtn = CEGUI::LeftButton;
	}
	else if(btn == (uint16_t)Key::MouseRight)
	{
		newBtn = CEGUI::RightButton;
	}
	else if(btn == (uint16_t)Key::MouseMiddle)
	{
		newBtn = CEGUI::MiddleButton;
	}

	if(pressed)
	{
		if(newBtn != CEGUI::NoButton)
		{
			context->injectMouseButtonDown(newBtn);
		}
	}
	else
	{
		if(newBtn != CEGUI::NoButton)
		{
			context->injectMouseButtonUp(newBtn);
		}
	}
}

void UserInterface::OnMouseMove(float x, float y)
{
	context->injectMousePosition(x, y);
	//context->getMouseCursor().setPosition(vec2_cast<CEGUI::Vector2f>(vec2(x,y)));
}

void UserInterface::OnWindowResize(uint width, uint height)
{
	if(system)
	{
		resized = true;
		size = uvec2(width, height);
		//	rootWindow->setMaxSize(CEGUI::USize(cegui_reldim(1.0f), cegui_reldim( 1.0f)));
	}
}

}