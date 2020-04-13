#include "XP++/UI/MenuItem.hpp"

// STL includes
#include <stdexcept>

// X-Plane SDK includes
#include "XPLMMenus.h"

// XP++ includes
#include "XP++/UI/Menu.hpp"
#include "XP++/Exceptions/XPException.hpp"
//#include "XP++/Commands/Command.hpp"

std::list<std::weak_ptr<XP::MenuItem>> XP::MenuItem::m_menuItems;

XP::MenuItem::MenuItem(std::weak_ptr<Menu> menu,
					   std::string name,
					   std::function<void(MenuItem&)> onClick) :
	m_childMenu(nullptr), m_index(-1), m_isEnabled(false), 
	m_name(name), m_onClick(onClick), m_parentMenu(nullptr)
{
	// Ensure given menu isn't NULL
	if (menu.expired())
	{
		throw std::invalid_argument("menu is NULL");
	}
	m_parentMenu = menu.lock();

	// Lock given parent menu
	std::shared_ptr<Menu> lockedMenu = menu.lock();
	// Create X-Plane menu item
	m_index = XPLMAppendMenuItem(lockedMenu == nullptr ? nullptr : lockedMenu->m_id, 
								 name.c_str(), 
								 this, 
								 NULL);

	// Ensure X-Plane SDK call succeeded
	if (m_index < 0)
	{
		throw XPException("Unable to create X-Plane Menu Item");
	}
}

XP::MenuItem::~MenuItem()
{
	// Destroy child menu
	if (m_childMenu != nullptr)
	{
		m_childMenu.reset();
	}

	// Removing X-Plane internal MenuItem moves other menu items on same
	// parent up by one, and assumes we're tracking this
	XPLMRemoveMenuItem(m_parentMenu == nullptr ? nullptr : m_parentMenu->m_id, m_index);
}

std::shared_ptr<XP::Menu> XP::MenuItem::CreateChildMenu(std::string name)
{
	// Find this MenuItem's shared pointer
	auto thisMenuInList = std::find_if(m_menuItems.begin(), m_menuItems.end(),
									   [this](const std::weak_ptr<MenuItem>& menuItem)
	{
		if (menuItem.expired())
		{
			return false;
		}
		else
		{
			std::shared_ptr<MenuItem> lockedMenuItem = menuItem.lock();
			return lockedMenuItem.get() == this;
		}
	});
	// Ensure this MenuItem's shared pointer exists within list
	if (thisMenuInList == m_menuItems.end())
	{
		throw std::logic_error("Unable to find this MenuItem in list of created MenuItems");
	}

	// Create Child Menu
	m_childMenu = std::shared_ptr<Menu>(new Menu(name, (*thisMenuInList)), [](Menu* menu)
	{
		delete menu;
	});

	// Add created child menu to master list
	Menu::m_menus.push_back(m_childMenu);

	return m_childMenu;
}

void XP::MenuItem::DestroyChildMenu()
{
	// Remove child menu from master list
	auto returnVal = std::remove_if(Menu::m_menus.begin(), Menu::m_menus.end(), [&](const std::weak_ptr<Menu>& menu)
	{
		if (menu.expired())
		{
			return false;
		}
		else
		{
			std::shared_ptr<Menu> lockedMenu = menu.lock();
			return lockedMenu == m_childMenu;
		}
	});

	// Destroy child menu
	m_childMenu.reset();
}

void XP::MenuItem::SetName(std::string name)
{
	XPLMSetMenuItemName(m_parentMenu == nullptr ? nullptr : m_parentMenu->m_id, 
						m_index, 
						name.c_str(), 
						NULL);
}

void XP::MenuItem::Disable()
{
	XPLMEnableMenuItem(m_parentMenu == nullptr ? nullptr : m_parentMenu->m_id,
					   m_index,
					   TRUE);
}

void XP::MenuItem::Enable()
{
	XPLMEnableMenuItem(m_parentMenu == nullptr ? nullptr : m_parentMenu->m_id,
					   m_index,
					   FALSE);
}

XP::MenuCheck XP::MenuItem::GetCheckState() const
{
	XPLMMenuCheck state;
	XPLMCheckMenuItemState(m_parentMenu == nullptr ? nullptr : m_parentMenu->m_id,
						   m_index,
						   &state);

	return static_cast<MenuCheck>(state);
}

void XP::MenuItem::SetCheckState(MenuCheck state)
{
	XPLMCheckMenuItem(m_parentMenu == nullptr ? nullptr : m_parentMenu->m_id,
					  m_index,
					  static_cast<XPLMMenuCheck>(state));
}
