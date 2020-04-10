#include "XP++/UI/Menu.hpp"

// STL includes
#include <algorithm>

// XP++ includes
#include "XP++/UI/MenuItem.hpp"
#include "XP++/Exceptions/NotImplementedException.hpp"
#include "XP++/Exceptions/XPException.hpp"

// X-Plane SDK includes
#include "XPLMMenus.h"

std::list<std::shared_ptr<XP::Menu>> XP::Menu::m_menus;

XP::Menu::Menu(std::string name, std::weak_ptr<MenuItem> parentMenuItem) :
	m_menuItems(), m_id(nullptr), m_parentMenuItem(parentMenuItem.lock()), m_name(name)
{
	// Ensure arguments are valid
	if (parentMenuItem.expired())
	{
		// Given parent menu item is NULL
		throw std::invalid_argument("parentMenuItem is NULL");
	}

	// Get parent menu item and parent menu references
	std::shared_ptr<MenuItem> lockedParentItem	= parentMenuItem.lock();
	std::shared_ptr<Menu> parentMenu			= lockedParentItem->GetParentMenu().lock();

	// Create X-Plane Menu
	m_id = XPLMCreateMenu(m_name.c_str(), parentMenu->m_id, lockedParentItem->GetIndex(), &Menu::MenuHandler, this);
	if (m_id == nullptr)
	{
		throw XP::XPException("Unable to create Menu");
	}
}

XP::Menu::Menu(std::string name, std::weak_ptr<MenuItem> parentMenuItem, void* id) :
	m_menuItems(), m_id(id), m_parentMenuItem(parentMenuItem.lock()), m_name(name)
{
	// For creating Menu objects which represent X-Plane
	// already created Menus
}

XP::Menu::~Menu()
{
	ClearAllMenuItems();
	XPLMDestroyMenu(m_id);
}

std::weak_ptr<XP::Menu> XP::Menu::FindPluginsMenu()
{
	// Create XP++ object representing the menu
	static std::shared_ptr<Menu> pluginsMenu = CreatePluginsMenu();

	return pluginsMenu;
}

std::weak_ptr<XP::Menu> XP::Menu::FindAircraftMenu()
{
	// Create XP++ object representing the menu
	static std::shared_ptr<Menu> aircraftMenu = CreateAircraftMenu();

	return aircraftMenu;
}

std::shared_ptr<XP::MenuItem> XP::Menu::AppendMenuItem(std::string name, std::function<void(MenuItem&)> onClick)
{
	// Create Menu Item
	std::shared_ptr<MenuItem> menuItem(new MenuItem(GetPtrToThisMenu(), name, onClick), [](MenuItem* menuItem)
	{
		delete menuItem;
	});
	m_menuItems.push_back(menuItem);

	// Add created menu item to master list
	XP::MenuItem::m_menuItems.push_back(menuItem);

	return menuItem;
}

void XP::Menu::AppendMenuSeparator()
{
	XPLMAppendMenuSeparator(m_id);
}

bool XP::Menu::HasMenuItem(std::weak_ptr<MenuItem> menuItem)
{
	// Ensure given argument isn't NULL
	if (menuItem.expired())
	{
		return false;
	}

	// Search for given menu item
	std::shared_ptr<MenuItem> lockedMenuItem = menuItem.lock();
	return std::find(m_menuItems.begin(), m_menuItems.end(), lockedMenuItem) != m_menuItems.end();
}

void XP::Menu::RemoveMenuItem(std::weak_ptr<MenuItem> menuItem)
{
	// Ensure given argument isn't NULL
	if (!menuItem.expired())
	{
		// Remove given argument
		std::shared_ptr<MenuItem> lockedMenuItem = menuItem.lock();
		auto firstReturnVal		= std::remove(m_menuItems.begin(), m_menuItems.end(), lockedMenuItem);
		auto secondReturnVal	= std::remove(XP::MenuItem::m_menuItems.begin(), XP::MenuItem::m_menuItems.end(), lockedMenuItem);
	}
}

void XP::Menu::ClearAllMenuItems()
{
	m_menuItems.clear();
}

std::shared_ptr<XP::Menu> XP::Menu::GetPtrToThisMenu() const
{
	// Find pointer to this menu
	auto pointerItr = std::find_if(m_menus.begin(), m_menus.end(), [this](const std::shared_ptr<Menu>& menu)
	{
		return menu.get() == this;
	});
	// Ensure we found a pointer
	if (pointerItr == m_menus.end())
	{
		throw std::exception("Unable to find pointer to this menu");
	}

	return (*pointerItr);
}

std::shared_ptr<XP::Menu> XP::Menu::CreateAircraftMenu()
{
	// Get X-Plane Menu ID for the aircraft menu
	XPLMMenuID menuID = XPLMFindAircraftMenu();
	// Create XP++ object representing the menu
	std::shared_ptr<Menu>menu(new Menu("Aircraft",
										  std::weak_ptr<MenuItem>(),
									   static_cast<void*>(menuID)), [](Menu* menu)
	{
		delete menu;
	});
	// Add created menu to master list
	m_menus.push_back(menu);

	return menu;
}

std::shared_ptr<XP::Menu> XP::Menu::CreatePluginsMenu()
{
	// Get X-Plane Menu ID for the plug-ins menu
	XPLMMenuID menuID = XPLMFindPluginsMenu();

	// Create XP++ object representing the menu
	std::shared_ptr<Menu> menu(new Menu("Plugins",
										std::weak_ptr<MenuItem>(),
										static_cast<void*>(menuID)), [](Menu* menu)
	{
		delete menu;
	});
	// Add created menu to master list
	m_menus.push_back(menu);

	return menu;
}

void XP::Menu::MenuHandler(void* inMenuRef, void* inItemRef)
{
	MenuItem* menuItem	= reinterpret_cast<MenuItem*>(inItemRef);
	if (menuItem == nullptr || menuItem->GetOnClick() == nullptr)
	{
		// Ignore for null pointers, and menu items without an onClick
		// event function
		return;
	}

	// Execute onClick for given menu item
	menuItem->m_onClick((*menuItem));
}
