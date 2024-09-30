#include "MainWindow.hpp"

int main(int argc, char** argv)
{
	MainWindow window;
	window.initialize(960, 540, "CLogicSim");
	window.enableResizable(true);
	while (window.isRunning())
	{
		window.update();
	}	
	return 0;
}
