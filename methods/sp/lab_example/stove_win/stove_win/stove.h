enum lamp {on, off};
enum door {open, close};
enum power {yes, no};
class stove
{	lamp curr_lamp;
	door curr_door;
	power curr_power;
public:
	int time;
	int take_door();
	int push_button();
	void ready();
	int GetTime();
	void SubTime();
	lamp GetLamp();
	door GetDoor();
	power GetPower();
	stove();
};
