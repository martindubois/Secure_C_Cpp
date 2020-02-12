
	Author         Martin Dubois, P.Eng.
	Learning path  Secure C/C++
	File           README.cpp

	===== Configuring a Windows devlopment computer =========================

	[ ] Download and install Visual Studio 2019 Community.
		- Select the "Desktop development with C++" workload.

	===== Configuring a Linux development computer ==========================
	The procedure is tested on Ubuntu 18.04.

	[ ] Execute the following commands to install C++ compiler and tools
		sudo apt install g++
		sudo apt install make
		sudo atp install xutils-dev
	[ ] Execut the following commands to install Visual Studio Code
		sudo apt update
		sudo apt install software-properties-common apt-transport-https wget
		wget -q https://packages.microsoft.com/keys/microsoft.asc -O- | sudo apt-key add -
		sudo add-apt-repository "deb [arch=amd64] https://packages/microsoft.com/repos/vscode stable main"
		sudo apt install code
