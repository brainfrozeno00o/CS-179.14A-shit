#include <SFML/graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

Color color[6];
CircleShape circleArray[60];
RectangleShape rectangleArray[40];
int curr = 0;

void moveThem(){
	for(int i = 0; i < 60; i++) circleArray[i].move(0,0.4);
	for(int j = 0; j < 40; j++) rectangleArray[j].move(0.4,0);
}

void niceThread(RenderWindow* window){
	while(window->isOpen()){
		window->clear(Color::Black);
		for(int i = 0; i < 60; i++) window->draw(circleArray[i]);
		for(int j = 0; j < 40; j++) window->draw(rectangleArray[j]);
		window->display();
		moveThem();
	}
}

int main(){
	ContextSettings settings;
	settings.antialiasingLevel = 16;
	RenderWindow window(VideoMode(1920,1080), "My Vectors and Circles", Style::Default, settings);
	window.setFramerateLimit(144);
	window.setActive(false);
	srand(time(NULL));
	color[0] = Color::Magenta;
	color[1] = Color::Cyan;
	color[2] = Color::Blue;
	color[3] = Color::Yellow;
	color[4] = Color::Green;
	color[5] = Color::Red;
	for(int i = 0; i < 60; i++){
		circleArray[i].setPosition(rand() % 1919, rand() % 1079);
		circleArray[i].setRadius(30.0f);
		circleArray[i].setFillColor(color[curr]);
		curr++;
		if(curr > 5) curr = 0;
	}
	for(int j = 0; j < 40; j++){
		rectangleArray[j].setPosition(rand() % 1919, rand() % 1079);
		rectangleArray[j].setSize(Vector2f(50.0f, 50.0f));
		rectangleArray[j].setFillColor(color[curr]);
		curr++;
		if(curr > 5) curr = 0;
	}
	Thread thread(&niceThread, &window);
	thread.launch();
	while(window.isOpen()){
		Event event;
		while(window.pollEvent(event)){
			if(event.type==Event::Closed) window.close();
		}
	}
	return 0;
}
