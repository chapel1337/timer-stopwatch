#include <iostream>
#include <conio.h>
#include <chrono>
#include <vector>
#include <thread>
#include <windows.h>
#include <string>

using std::cout, std::string, std::vector, std::cin, std::this_thread::sleep_for, std::to_string;
using namespace std::chrono;

/*
* written by chapel1337
* started on 11/29/2022
* finished on 11/30/2022
* finally got around to learning the chrono library
* i'm aware that i could've just used integers for this, but it was good practice (in my opinion)
* there's not much to say about this, it's just a timer and a stopwatch
* came back on 12/1/2022 to fix a newline mistake in help/credits
*/

seconds timeSeconds{ 0s };
minutes timeMinutes{ 0min };
hours timeHours{ 0h };

bool stopTime{};

void setTime(const int position);
void menu(const int position);

void clear()
{
	system("cls");
}

void title(const bool timerStopwatch) // true = timer, false = stopwatch
{
	if (timerStopwatch)
	{
		SetConsoleTitleA("timer");
	}
	else
	{
		SetConsoleTitleA("stopwatch");
	}
}

void title(const string& title)
{
	SetConsoleTitleA(("timer - " + title).c_str());
}

void title(const string& title, int i)
{
	SetConsoleTitleA(("timer - " + title + to_string(i)).c_str());
}

void refresh()
{
	clear();

	cout << "\n   ";
	
	if (timeHours < hours(10))
	{
		cout << '0' << timeHours.count() << ':';
	}
	else
	{
		cout << timeHours.count() << ':';
	}

	if (timeMinutes < minutes(10))
	{
		cout << '0' << timeMinutes.count() << ':';
	}
	else
	{
		cout << timeMinutes.count() << ':';
	}

	if (timeSeconds < seconds(10))
	{
		cout << '0' << timeSeconds.count();
	}
	else
	{
		cout << timeSeconds.count();
	}

	cout << "\n\n";
}

void helpCredits()
{
	clear();
	title("help/credits");

	cout << "\n   help/credits\n\n";

	cout << "   when setting the time, use the A and D keys to move left or right\n";
	cout << "   and the W and S keys to increase and decrease the time\n\n";
	
	cout << "   to pause the stopwatch, press the space or enter key\n";
	cout << "   when the time is up, press any key to stop the ringer\n";
	cout << "   press the esc to return to the menu\n\n";

	cout << "   written by chapel1337\n\n";
	cout << "   started on 11/29/2022\n";
	cout << "   finished on 11/30/2022\n\n";

	cout << "   > okay <\n";

	_getch();
	menu(1);
}

void startStopwatch()
{
	refresh();
	title(false);

	while (!stopTime)
	{
		// just in case the user is clinically insane
		if (timeHours == hours(99))
		{
			stopTime = true;

			menu(0);
		}

		if (_kbhit())
		{
			int keyInput{ _getch() };

			if (keyInput == 27)
			{
				stopTime = true;

				menu(0);
			}
			else if (keyInput == 13 || keyInput == ' ')
			{
				clear();

				cout << "\n   paused stopwatch\n";

				_getch();
			}
		}

		if (timeSeconds == seconds(60))
		{
			++timeMinutes;
			timeSeconds = 0s;
		}
		if (timeMinutes == minutes(60))
		{
			++timeHours;
			timeMinutes = 0min;
		}

		++timeSeconds;

		sleep_for(1s);
		refresh();
	}
}

void startCountdown()
{
	refresh();
	title(true);

	while (!stopTime)
	{
		if (_kbhit())
		{
			int keyInput{ _getch() };

			if (keyInput == 27)
			{
				stopTime = true;
				
				menu(0);
			}
		}

		if (timeSeconds == seconds(0) && timeMinutes != minutes(0))
		{
			--timeMinutes;
			timeSeconds = 60s;
		}
		else if (timeSeconds == seconds(0) && timeMinutes == minutes(0) && timeHours != hours(0))
		{
			--timeHours;
			timeMinutes = 59min;
			timeSeconds = 60s;
		}
		else if (timeSeconds == seconds(0) && timeMinutes == minutes(0) && timeHours == hours(0))
		{
			clear();

			cout << "\n   time's up!\n";

			while (!stopTime)
			{
				if (_kbhit())
				{
					stopTime = true;
					
					setTime(1);
				}
				else
				{
					Beep(325, 200);
					sleep_for(10ms);
				}
			}
		}

		--timeSeconds;

		sleep_for(1s);
		refresh();
	}
}

void setTime(const int position)
{
	clear();
	title("set time");

	// cout << position << '\n';

	cout << "\n   ";

	for (int i{}; i <= 7; ++i)
	{
		if (i == position)
		{
			cout << 'v';
		}
		else
		{
			cout << ' ';
		}
	}

	cout << '\n';
	cout << "   ";

	if (timeHours < hours(10))
	{
		cout << '0' << timeHours.count() << ':';
	}
	else
	{
		cout << timeHours.count() << ':';
	}

	if (timeMinutes < minutes(10))
	{
		cout << '0' << timeMinutes.count() << ':';
	}
	else
	{
		cout << timeMinutes.count() << ':';
	}

	if (timeSeconds < seconds(10))
	{
		cout << '0' << timeSeconds.count();
	}
	else
	{
		cout << timeSeconds.count();
	}

	cout << '\n';
	cout << "   ";

	for (int i{}; i <= 7; ++i)
	{
		if (i == position)
		{
			cout << '^';
		}
		else
		{
			cout << ' ';
		}
	}

	int keyInput{ _getch() };

	if (keyInput == 'A' || keyInput == 'a')
	{
		if (position == 3 || position == 6)
		{
			setTime(position - 2);
		}
		else if (position == 0)
		{
			setTime(7);
		}
		else
		{
			setTime(position - 1);
		}
	}
	else if (keyInput == 'D' || keyInput == 'd')
	{
		if (position == 1 || position == 4)
		{
			setTime(position + 2);
		}
		else if (position == 7)
		{
			setTime(0);
		}
		else
		{
			setTime(position + 1);
		}
	}

	else if (keyInput == 'W' || keyInput == 'w')
	{
		// using if statements because switch doesn't support ||
		if (position == 0 && timeHours <= hours(90))
		{
			timeHours += hours(10);
		}
		else if (position == 1 && timeHours < hours(99))
		{
			++timeHours;
		}

		else if (position == 3 && timeMinutes != minutes(60))
		{
			timeMinutes += minutes(10);
		}
		else if (position == 4 && timeMinutes != minutes(59))
		{
			++timeMinutes;
		}

		else if (position == 6 && timeSeconds <= seconds(60))
		{
			timeSeconds += seconds(10);
		}
		else if (position == 7 && timeSeconds <= seconds(59))
		{
			++timeSeconds;
		}

		if (timeSeconds >= seconds(60))
		{
			++timeMinutes;
			timeSeconds -= seconds(60);
		}
		if (timeMinutes >= minutes(60) && timeHours != hours(99))
		{
			++timeHours;
			timeMinutes -= minutes(60);
		}

		setTime(position);
	}
	else if (keyInput == 'S' || keyInput == 's')
	{
		if (position == 0 && timeHours > hours(0))
		{
			timeHours -= hours(10);
		}
		else if (position == 1 && timeHours > hours(0))
		{
			--timeHours;
		}

		else if (position == 3 && timeMinutes > minutes(0))
		{
			timeMinutes -= minutes(10);
		}
		else if (position == 4 && timeMinutes > minutes(0))
		{
			--timeMinutes;
		}

		else if (position == 6 && timeSeconds > seconds(0))
		{
			timeSeconds -= seconds(10);
		}
		else if (position == 7 && timeSeconds > seconds(0))
		{
			--timeSeconds;
		}

		setTime(position);
	}
	else if (keyInput == 13)
	{
		stopTime = false;

		startCountdown();
	}
	else if (keyInput == 27)
	{
		menu(0);
	}
	else
	{
		setTime(position);
	}
}

void quit()
{
	clear();

	for (int i{ 3 }; i > 0; --i)
	{
		title("okay, quitting in ", i);
		cout << "\n   okay, exiting in " << i;

		Sleep(1000);
		clear();
	}

	exit(1);
}

void menu(const int position)
{
	clear();
	title("menu");

	timeSeconds = 0s;
	timeMinutes = 0min;
	timeHours = 0h;

	cout << "\n   timer\n\n";

	if (position == 0)
	{
		cout << "   > start timer <\n";
	}
	else
	{
		cout << "   start timer\n";
	}

	if (position == 1)
	{
		cout << "   > start stopwatch <\n\n";
	}
	else
	{
		cout << "   start stopwatch\n\n";
	}

	if (position == 2)
	{
		cout << "   > help/credits <\n";
	}
	else
	{
		cout << "   help/credits\n";
	}

	if (position == 3)
	{
		cout << "   > quit <\n";
	}
	else
	{
		cout << "   quit\n";
	}

	int keyInput{ _getch() };

	if ((keyInput == 'W' || keyInput == 'w') && position != 0)
	{
		menu(position - 1);
	}
	else if ((keyInput == 'S' || keyInput == 's') && position != 3)
	{
		menu(position + 1);
	}
	else if (keyInput == 13)
	{
		stopTime = false;

		switch (position)
		{
		case 0:
			setTime(0);
			break;

		case 1:
			startStopwatch();
			break;

		case 2:
			helpCredits();
			break;

		case 3:
			quit();
			break;
		}
	}
	else
	{
		menu(position);
	}
}

int main()
{
	menu(0);
}
