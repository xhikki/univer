enum lamp {on, off};
enum door {open, close};
enum power {yes, no};
class stove
{	lamp curr_lamp;
	door curr_door;
	power curr_power;
	int time;
	char* take_door(void);
	char* push_button(void);
	char* ready(void);
public:
	stove();
	void Run();
};
