#pragma once

// STL includes
#include <list>
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace XP
{
	// Pre-declarations
	class Command;
	class MenuItem;

	/// <summary>
	/// Menu containing menu items
	/// </summary>
	class Menu final
	{
	public:
		friend MenuItem;

		/// <summary>
		/// Gets the name of this menu
		/// </summary>
		/// <returns>String representing the name of this menu</returns>
		inline std::string GetName() const
		{
			return m_name;
		}

		/// <summary>
		/// Gets the parent <see cref="MenuItem"/> of this Menu
		/// </summary>
		/// <returns>Reference to the parent <see cref="MenuItem"/></returns>
		inline std::weak_ptr<MenuItem> GetParentMenuItem() const
		{
			return m_parentMenuItem;
		}

		/// <summary>
		/// Returns the plug-ins menu
		/// </summary>
		/// <returns>The plug-in menu</returns>
		static std::weak_ptr<Menu> FindPluginsMenu();
		/// <summary>
		/// Returns the menu for the currently-loaded aircraft,
		/// used for showing specific commands.
		/// </summary>
		/// <remarks>
		/// <para>
		/// The aircraft menu is created by X-Plane at start-up, but it 
		/// remains hidden until it is populated via 
		/// <see cref="AppendMenuItem(std::string, std::function<void()>, std::weak_ptr<Command>)"/>
		/// or <see cref="ApparentMenuItemWithCommand()"/>.
		/// </para>
		/// <para>
		/// Only plugins loaded with 
		/// the user’s current aircraft are allowed to access the aircraft 
		/// menu. For all other plugins, this will return NULL.
		/// </para>
		/// </remarks>
		/// <returns></returns>
		static std::weak_ptr<Menu> FindAircraftMenu();

		/// <summary>
		/// Appends a new <see cref="MenuItem"/> to the bottom of the menu
		/// </summary>
		/// <param name="name">Name of the menu item</param>
		/// <returns>Returns the appended <see cref="MenuItem"/>, or null if failed</returns>
		inline std::shared_ptr<MenuItem> AppendMenuItem(std::string name)
		{
			return AppendMenuItem(name, std::function<void(MenuItem&)>());
		}
		/// <summary>
		/// Appends a new <see cref="MenuItem"/> to the bottom of the menu
		/// </summary>
		/// <param name="name">Name of the menu item</param>
		/// <param name="onClick">Function to execute when the user clicks this menu item</param>
		/// <returns>Returns the appended <see cref="MenuItem"/>, or null if failed</returns>
		std::shared_ptr<MenuItem> AppendMenuItem(std::string name, 
											   std::function<void(MenuItem&)> onClick);

		/// <summary>
		/// Similar to <see cref="AppendMenuItem(std::string, std::function<void()>)"/>, 
		/// but instead of the menu item executing the onClick function, it will simply 
		/// execute the command passed in. Using a command for your menu item allows
		/// the user to bind a keyboard shortcut to the command and see that shortcut
		/// represented in the menu.
		/// </summary>
		/// <param name="name">Name of the menu item</param>
		/// <param name="command">Command to execute</param>
		/// <returns>Returns the appended <see cref="MenuItem"/>, or null if failed</returns>
		std::weak_ptr<MenuItem> AppendMenuItemWithCommand(std::string name,
														  std::weak_ptr<Command> command);

		/// <summary>
		/// Adds a separator to the end of this menu
		/// </summary>
		void AppendMenuSeparator();

		/// <summary>
		/// Does this menu contain a given <see cref="MenuItem"/>?
		/// </summary>
		/// <param name="menuItem">Menu item to check</param>
		/// <returns>True if the given menu item is apart of this menu</returns>
		bool HasMenuItem(std::weak_ptr<MenuItem> menuItem);
		/// <summary>
		/// Removes the given menu item from this menu
		/// </summary>
		/// <param name="menuItem">Menu item to remove</param>
		void RemoveMenuItem(std::weak_ptr<MenuItem> menuItem);
		/// <summary>
		/// Removes all <see cref="MenuItem"/>s from this menu, allowing you to rebuild it.
		/// </summary>
		/// <remarks>
		/// Use this function if you need to change the number of items on a menu.
		/// </remarks>
		void ClearAllMenuItems();

	private:
		Menu(std::string name,
			 std::weak_ptr<MenuItem> parentMenuItem);
		Menu(std::string name,
			 std::weak_ptr<MenuItem> parentMenuItem,
			 void* id);
		~Menu();

		Menu(const Menu&)					= delete;
		Menu& Menu::operator=(const Menu&)	= delete;

		// Internal X-Plane ID
		void* m_id;
		// Child parent menu items
		std::vector<std::shared_ptr<MenuItem>> m_menuItems;
		// MenuItem that this menu is a child of
		std::shared_ptr<MenuItem> m_parentMenuItem;
		// Name of the menu
		std::string m_name;

		// All created menus
		static std::list<std::weak_ptr<Menu>> m_menus;

		// Finds the shared pointer to this menu
		std::shared_ptr<Menu> GetPtrToThisMenu() const;
		// Creates the aircraft menu object
		static std::shared_ptr<Menu> CreateAircraftMenu();
		// Creates the plug-in menu object
		static std::shared_ptr<Menu> CreatePluginsMenu();
		// X-Plane UI Handler for this menu
		static void MenuHandler(void* inMenuRef, void* inItemRef);
	};
}
