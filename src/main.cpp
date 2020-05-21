#include <iostream>
#include <ncurses.h>

void demo1();

int main() {
	std::cout << "hello world";

	demo1();
	return 0;
}

void demo1() {
	initscr(); // start curses mode
	raw(); // line buffering disabled
	keypad(stdscr, TRUE); // we get F1 F2 etc
	noecho(); // dont echo() while we do getch

	printw("Type any character to see it in bold\n"); // print hello world
	int ch = getch();
	if (ch == KEY_F(1))
		printw("F1 key pressed");
	else
	{
		printw("The pressed key is ");
		attron(A_BOLD);
		printw("%c", ch);
		attroff(A_BOLD);
	}

	refresh(); //print it on to the real screen
	getch(); //wait for user input
	endwin(); //end curses mode
}

