#ifndef _MENU_
#define _MENU_

#include <stdint.h>

struct Item{
	void (*init)(void);
	void (*main)(void);
	void (*sub)(void);
	void (*timer)(void);
	Item* next;
	Item* previous;
};

class Menu
{
	private:
		Item* m_head;
		Item* m_tail;
		Item* m_current;
		
	public:
		Menu(void);
		void insert(Item* element);
		void next(void);
		void previous(void);
		void current(Item** element);
};

#endif
