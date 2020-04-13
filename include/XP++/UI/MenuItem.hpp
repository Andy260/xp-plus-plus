#pragma once

// STL includes
#include <functional>
#include <memory>
#include <string>
#include <list>

namespace XP
{
	// Pre-declarations
	class Menu;

	/// <summary>
	/// Represents the various 'check' states for an X-Plane Menu Item
	/// </summary>
	/// <remarks>
	/// ‘checking’ in X-Plane actually appears as a light which may 
	/// or may not be lit. So there are three possible states.
	/// </remarks>
	enum class MenuCheck : int
	{
		/// <summary>
		/// No symbol to the left of the menu item
		/// </summary>
		NoCheck		= 0,
		/// <summary>
		/// The menu item has a mark next to it 
		/// that is unmarked (not lit).
		/// </summary>
		UnChecked	= 1,
		/// <summary>
		/// The menu item has a mark next to 
		/// it that is checked (lit).
		/// </summary>
		Checked		= 2
	};

	/// <summary>
	/// Represents a click-able item within a <see cref="Menu"/>
	/// </summary>
	class MenuItem final
	{
	public:
		friend Menu;

		/// <summary>
		/// Appends a new MenuItem to the menu bar of X-Plane
		/// </summary>
		/// <param name="name">Name of this MenuItem</param>
		/// <param name="onClick">Function to execute upon clicking this MenuItem</param>
		/// <returns>Created MenuItem</returns>
		inline static std::shared_ptr<MenuItem> AppendToMenubar(std::string name, 
																std::function<void(MenuItem&)> onClick)
		{
			std::shared_ptr<MenuItem> menuItem(new MenuItem(std::weak_ptr<Menu>(), name, onClick), [](MenuItem* menuItem)
			{
				delete menuItem;
			});
			m_menuItems.push_back(menuItem);

			return menuItem;
		}

		/// <summary>
		/// Returns a reference to the parent <see cref="Menu"/> 
		/// of this menu item
		/// </summary>
		/// <returns>Reference to the parent <see cref="Menu"/></returns>
		inline std::weak_ptr<Menu> GetParentMenu() const
		{
			return m_parentMenu;
		}

		/// <summary>
		/// Does this menu item have a child <see cref="Menu"/>?
		/// </summary>
		/// <returns>True if this menu item has a child menu, false if not</returns>
		inline bool HasChildMenu() const
		{
			return m_childMenu != nullptr;
		}
		/// <summary>
		/// Returns a reference to the child <see cref="Menu"/> of this menu item (if any)
		/// </summary>
		/// <returns>Returns a reference to the child menu, or null if none exist</returns>
		inline std::weak_ptr<Menu> GetChildMenu() const
		{
			return m_childMenu;
		}
		/// <summary>
		/// Creates a <see cref="Menu"/> as a child of this menu item
		/// </summary>
		/// <returns>
		/// Reference to the created child <see cref="Menu"/>.
		/// If a child menu already exists, a reference to it 
		/// will be returned
		/// </returns>
		std::shared_ptr<Menu> CreateChildMenu(std::string name);
		/// <summary>
		/// Destroys the child menu of this menu item 
		/// and associated menu item children of the child <see cref="Menu"/>
		/// </summary>
		void DestroyChildMenu();

		/// <summary>
		/// Gets the current name of this menu item
		/// </summary>
		/// <returns>String representing the current name</returns>
		inline std::string GetName() const
		{
			return m_name;
		}
		/// <summary>
		/// Sets the name of this menu item
		/// </summary>
		/// <param name="name">String to set the name to</param>
		void SetName(std::string name);

		/// <summary>
		/// Is this menu item currently enabled?
		/// </summary>
		/// <returns>True if enabled, false if not</returns>
		inline bool IsEnbled() const
		{
			return m_isEnabled;
		}
		/// <summary>
		/// Disabled this menu item
		/// </summary>
		void Disable();
		/// <summary>
		/// Enabled this menu item
		/// </summary>
		void Enable();

		/// <summary>
		/// Gets whether the menu item is currently checked or not
		/// </summary>
		/// <returns>Current check state</returns>
		MenuCheck GetCheckState() const;
		/// <summary>
		/// Sets this menu item's check state
		/// </summary>
		/// <param name="state">State to set to</param>
		void SetCheckState(MenuCheck state);

		/// <summary>
		/// Gets the function which will be invoked 
		/// upon clicking this menu item
		/// </summary>
		/// <returns>Returns the function pointer to be executed 
		/// on click, or NULL if none was assigned</returns>
		inline std::function<void(MenuItem&)> GetOnClick() const
		{
			return m_onClick;
		}
		/// <summary>
		/// Sets the function which will be invoked 
		/// upon clicking this menu item
		/// </summary>
		/// <param name="value">Function to set OnClick to</param>
		inline void SetOnClick(std::function<void(MenuItem&)> value)
		{
			m_onClick = value;
		}

		/// <summary>
		/// Gets the index of this menu item within its parent <see cref="Menu"/>
		/// </summary>
		/// <returns>Index of this menu item</returns>
		inline int GetIndex() const
		{
			return m_index;
		}

	private:
		MenuItem(std::weak_ptr<Menu> menu,
				 std::string name,
				 std::function<void(MenuItem&)> onClick);
		~MenuItem();

		MenuItem(const MenuItem&)						= delete;
		MenuItem& MenuItem::operator=(const MenuItem&)	= delete;

		// Index of this menu item within the parent menu
		// (refers to the plug-in relative index, if in a menu 
		// with menu items from other plug-ins and/or X-Plane)
		int m_index;
		// Is this menu item currently enabled?
		bool m_isEnabled;
		// Name of thus menu-item
		std::string m_name;

		// Parent menu of this menu item
		std::shared_ptr<Menu> m_parentMenu;
		// Child menu of this menu item
		std::shared_ptr<Menu> m_childMenu;
		// Event function for when this menu item is clicked
		std::function<void(MenuItem&)> m_onClick;

		// Created MenuItems
		static std::list<std::weak_ptr<MenuItem>> m_menuItems;
	};
}
