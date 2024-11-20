#ifndef menu_h
#define menu_h

// Enum to represent the different menu choices in the Address Book Program
enum class MenuChoice{
    AddContactMenu = 1,
    DisplayContactMenu,
    SearchContactMenu,
    DeleteContactMenu,
    EditContactMenu,
    SaveToFileMenu,
    LoadFromFileMenu,
    SortContactByNameMenu,
    Exit
};
#endif
